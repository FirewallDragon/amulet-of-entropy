/*
=======================================================================================
    AMULET OF ENTROPY

    Please see the /docs directory for full info.
=======================================================================================
*/

#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <LittleFS.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "utils.h"
#include "button.h"
#include "statemachine.h"
#include "fsmlist.hpp"
#include "entropypool.h"
#include "roundlcd.h"
#include "ledstrip.h"

using namespace std;

// ------------------------------------------------
//   VERSION
const string version = "data collector v0.1";
// ------------------------------------------------


// Sensor input pins
const int MPU_SDA = 14;
const int MPU_SCL = 15;
const int LDR_pin = 27;
const int Shot_pin = 28;
const int TMP_pin = 29;

// MPU-6050 (GY-25 module) 3-axis MEMS gyro + 3-axis MEMS accelerometer
const int MPUadr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; // MPU Values
int LDR_val, TMP_val;
int Shot_val;

// Sensors to pull data from
enum SENSOR {sensor_motion, sensor_accel, sensor_temp, sensor_light, sensor_shot};
int sensor_index = 0;
int SENSOR_COUNT = 5;

const char* get_sensor_name(int index)
{
    switch(index)
    {
        case 0: return "motion"; break;
        case 1: return "accel"; break;
        case 2: return "temp"; break;
        case 3: return "light"; break;
        case 4: return "shot"; break;
        default: return "UNKNOWN";
    }
}

SENSOR get_sensor(int index)
{
    switch(index)
    {
        case 0: return sensor_motion;
        case 1: return sensor_accel;
        case 2: return sensor_temp;
        case 3: return sensor_light;
        case 4: return sensor_shot;
    }
    log("ERROR! bad sensor index: %d", index);
    return sensor_temp;
}


// Notions of button events should be here, not in the button itself
// We're looking for events caused by changes in button state here.
struct ButtonWatcher
{
    ButtonWatcher(Button b)
    : _b(b), _last_state(NOT_PRESSED) { };

    Button _b;
    bool _last_state;

    bool just_pressed()
    {
        bool _just_pressed = false;
        bool current_state = _b.read_button();
        if (_last_state == NOT_PRESSED && current_state == PRESSED) {
            _just_pressed = true;
        }
        _last_state = current_state;
        return _just_pressed;
    }

    bool is_pressed() {
        return _b.read_button() == PRESSED;
    }
};

// Create the buttons
ButtonWatcher button_back   = ButtonWatcher(Button(B1_pin, "back"));
ButtonWatcher button_minus  = ButtonWatcher(Button(B2_pin, "minus"));
ButtonWatcher button_plus   = ButtonWatcher(Button(B3_pin, "plus"));
ButtonWatcher button_select = ButtonWatcher(Button(B4_pin, "select"));


/*
==================================================================================
    SETUP
==================================================================================
*/

void setup(void)
{
    // Handles to the singleton objects
    EntropyPool& pool = EntropyPool::get_instance();
    LEDStrip& strip = LEDStrip::get_instance();
    RoundLCD& lcd = RoundLCD::get_instance();

    lcd.set_bg_color(BLACK);
    lcd.set_text_props(3, YELLOW, BLACK);
    lcd.centered_text_multi({"Serial", "starting..."});

    Serial.begin(115200);
    while (!Serial) {
        // wait
    }

    log("====================================================");
    log("   Amulet of Entropy: DATA CAPTURE MODE");
    log("====================================================\n");

    // Set default text properties
    lcd.set_bg_color(BLACK);
    lcd.centered_text_multi({"DATA", "COLLECTION", "MODE"});
    strip.off();

    // Set up the sensors
    analogReadResolution(12); // increase analog input resolution to 12 bits  [0..4095]
    StartMPU();
    pinMode(LDR_pin, INPUT);
    pinMode(Shot_pin, INPUT);
    pinMode(TMP_pin, INPUT);

    // I think the MPU needs time to start
    delay(500);

    lcd.centered_text(get_sensor_name(sensor_index));
}


/*
==================================================================================
  MAIN LOOP

  User selects the sensor using Plus/Minus.
  Then start collecting by hitting Select.
  "Back" will interrupt collection.
==================================================================================
*/

const int SAMPLES = 10000;
int sample_count = 0;
bool collecting = false;

unsigned long before = 0;
unsigned long after = 0;

char valbuf[20];
char lcdbuf[20];



void loop()
{
    LEDStrip& strip = LEDStrip::get_instance();
    RoundLCD& lcd = RoundLCD::get_instance();

    // Check for user input
    check_for_button_events();

    if (collecting)
    {
        unsigned long val = get_sensor_value(sensor_index);
        sample_count = sample_count + 1;

        int percent_done = (float(sample_count) / SAMPLES) * 100;
        strip.set_sample_meter(percent_done);

        sprintf(valbuf, "%hX,", val);
        Serial.print(valbuf);
        if ( (sample_count % 100) == 0) {
            Serial.print("\n");
        }

        if (sample_count >= SAMPLES)
        {
            after = millis();
            collecting = false;
            float secs = (after - before) / 1000.0;
            log("\nDONE! Collected %d samples from %s in %.2f seconds\n", SAMPLES, get_sensor_name(sensor_index), secs);
            lcd.centered_text_multi({"Data", "collection", "DONE!!"});
            strip.sparkle(led_arrows);
            lcd.centered_text(get_sensor_name(sensor_index));
        }
    }
}


/*
---------------------------------------------------
    Helper functions for main loop
---------------------------------------------------
*/

void gather_entropy()
{
    EntropyPool& pool = EntropyPool::get_instance();

    ReadNoise();
}

void countdown()
{
    RoundLCD& lcd = RoundLCD::get_instance();
    char buff1[20];
    char buff2[20];
    for (int i=5 ; i>0 ; i--) {
        sprintf(buff1, "%d seconds", i);
        lcd.centered_text_multi({"starting in", buff1});
        delay(1000);
    }
    sprintf(buff1, "%d samples", SAMPLES);
    sprintf(buff2, "from %s", get_sensor_name(sensor_index));
    lcd.centered_text_multi({"Collecting", buff1, buff2});
}

void check_for_button_events(void)
{
    RoundLCD& lcd = RoundLCD::get_instance();
    LEDStrip& strip = LEDStrip::get_instance();

    if (button_back.just_pressed())
    {
        after = millis();
        strip.button_feedback(W, rgb_blue);

        if (collecting)
        {
            log("\nINTERRUPTED!!\n");
            lcd.centered_text("INTERRUPTED");
            delay(500);
            strip.off();
            lcd.centered_text(get_sensor_name(sensor_index));
        }
        collecting = false;
        sample_count = 0;
    }
    if (button_select.just_pressed()) {
        strip.button_feedback(E, rgb_blue);

        log("Collecting %d samples from %s\n", SAMPLES, get_sensor_name(sensor_index));
        sample_count = 0;
        collecting = true;
        countdown();

        before = millis();
    }
    if (button_minus.just_pressed()) {
        strip.button_feedback(S, rgb_blue);
        sensor_index = (sensor_index - 1) % SENSOR_COUNT;
        lcd.centered_text(get_sensor_name(sensor_index));
    }
    if (button_plus.just_pressed()) {
        strip.button_feedback(N, rgb_blue);
        sensor_index = (sensor_index + 1) % SENSOR_COUNT;
        lcd.centered_text(get_sensor_name(sensor_index));
   }
}


/*
---------------------------------------------------
    Routines to read the various sensors
---------------------------------------------------
*/

unsigned long get_sensor_value(int si)
{
    unsigned long sensor_val = 0;
    SENSOR s = get_sensor(si);
    switch(s)
    {
        case sensor_motion:
            ReadMPU();
            sensor_val = GyX;
            break;
        case sensor_accel:
            ReadMPU();
            sensor_val = AcX;
            break;
        case sensor_temp:
            sensor_val = analogRead(TMP_pin);
            break;
        case sensor_light:
            sensor_val = analogRead(LDR_pin);
            break;
        case sensor_shot:
            sensor_val = analogRead(Shot_pin);
            break;
        default:
            log("Unknown sensor index: %d", si);
    }
    return sensor_val;
}


void ReadNoise(void)
{
    ReadMPU();
    LDR_val = analogRead(LDR_pin);
    Shot_val = analogRead(Shot_pin);
    TMP_val = ReadTemp();
}

void StartMPU()
{
    Wire1.setSDA(MPU_SDA);
    Wire1.setSCL(MPU_SCL);
    Wire1.begin();

    Wire1.beginTransmission(MPUadr); // Begins a transmission to GY-521 board
    Wire1.write(0x6B); // PWR_MGMT_1 register
    Wire1.write(0); // set to zero (wakes up the MPU-6050)
    Wire1.endTransmission(true);
}

void ReadMPU()
{
    /*
    From: https://mschoeffler.com/2017/10/05/tutorial-how-to-use-the-gy-521-module-mpu-6050-breakout-board-with-the-arduino-uno/
    Each sensor value has a size of 2 bytes. As each register has a size of one byte, a
    single sensor value must be retrieved by accessing two registers. The first register
    contains the so-called “high byte” and the second register contains the “low byte”.
    */

    Wire1.beginTransmission(MPUadr);
    Wire1.write(0x3B);
    Wire1.endTransmission(false);
    Wire1.requestFrom(MPUadr, 14, true);  // request a total of 14 registers
    AcX=Wire1.read()<<8|Wire1.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY=Wire1.read()<<8|Wire1.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ=Wire1.read()<<8|Wire1.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp=Wire1.read()<<8|Wire1.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX=Wire1.read()<<8|Wire1.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY=Wire1.read()<<8|Wire1.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ=Wire1.read()<<8|Wire1.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

int ReadTemp()
{
    int analogValue = analogRead(TMP_pin);
    return analogValue;
}
