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
const string version = "1.2 2022-07-29";
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

// Finite state machine (FSM) setup
using fsm_handle = Amulet;
FSM_INITIAL_STATE(Amulet, Initializing)

// Demo mode will just cycle through all the choices forever
// Enable by holding Select and Back at the same time. That will
// set this
bool DEMO_MODE = false;
const int DEMO_DELAY = 1000;
int demo_loop_index = 0;
// This is dumb, but the proper C++ code for this is uglier.
enum DemoEvent {de_back, de_select, de_plus};
static const vector<DemoEvent> DEMO_LOOP_EVENTS = {de_back, de_plus, de_select, de_select, de_select};

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

    // Make sure you've properly partitioned the flash memory!
    // See docs/Setup.md
    if (!LittleFS.begin())
    {
        log("ERROR: File System Mount Failed!");
        lcd.centered_text_multi({"ERROR:", "FS mount", "failed"});
        delay(1000 * 60 * 60); // just wait forever, do nothing
    }

    lcd.drawJpeg("splash-screen.jpg");
    strip.cycle();

    delay(2000);

    log("====================================================");
    log("   Amulet of Entropy: %s", version.c_str());
    log("====================================================\n");

    // Set default text properties
    lcd.set_text_props(3, YELLOW, BLACK);

    lcd.set_bg_color(BLACK);
    strip.off();

    // Set up the sensors
    analogReadResolution(12); // increase analog input resolution to 12 bits  [0..4095]
    StartMPU();
    pinMode(LDR_pin, INPUT);
    pinMode(Shot_pin, INPUT);
    pinMode(TMP_pin, INPUT);

    // Initialize the state machine
    fsm_handle::start();
}


/*
==================================================================================
  MAIN LOOP

  Loop forever, gathering noise and user inputs, and sending events to the
  finite state machine. All state machine events should be driven from here.

  The basic flow here is:
  - Fill the entropy pool by gathering noise from the sensors
  - Let the user deplete the pool by using up the stored entropy
  - When the pool is completely empty, stop and refill it.
  - Rinse, repeat.
==================================================================================
*/

void loop()
{
    // Handles to the singleton objects
    EntropyPool& pool = EntropyPool::get_instance();
    LEDStrip& strip = LEDStrip::get_instance();
    RoundLCD& lcd = RoundLCD::get_instance();

    // Check if pool is full when we start this loop
    int pool_was_full = pool.is_full();

    // See if any buttons are currently pressed.
    // Note that 'Select' in any given mode will pull from the entropy pool.
    check_for_button_events();

    // When enabled, we just cycle through the modes
    if (DEMO_MODE && !pool.accepting_data()) {
        next_demo_event();
    }

    // If the user just depleted the entropy pool, it's time to refill it.
    if ( pool.is_empty() )
    {
        lcd.centered_text_multi({"Entropy pool", "is", "EMPTY"});
        delay(1000);
        lcd.set_bg_color(BLACK);

        // Stop what you're doing and refill the entropy pool.
        send_event(PoolEmpty());
    }

    // Keep the user apprised of the pool level
    strip.set_pool_meter(pool.percent_full());

    // If the pool is dry, fill it up again.
    if (pool.accepting_data())
    {
        char buff[10];
        sprintf(buff, "%d%%", pool.percent_full());
        lcd.centered_text_multi({"Gathering", "entropy", buff});

        gather_entropy();
        delay(100); // let's slow down a bit for visual effect
    }

    // If the pool became full on this pass, send the PoolFull event.
    if ( !pool_was_full && pool.is_full() )
    {
        lcd.set_bg_color(BLACK);
        lcd.centered_text_multi({"Entropy pool", "is", "FULL"});
        strip.sparkle(led_arrows);
        lcd.set_bg_color(BLACK);

        send_event(PoolFull());
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
    pool.harvest_entropy(GyX);
    pool.harvest_entropy(GyY);
    pool.harvest_entropy(GyZ);
    pool.harvest_entropy(LDR_val);
    pool.harvest_entropy(TMP_val);
    pool.harvest_entropy(Shot_val);
}

void check_for_button_events(void)
{
    RoundLCD& lcd = RoundLCD::get_instance();
    LEDStrip& strip = LEDStrip::get_instance();

    if (button_select.is_pressed() && button_back.is_pressed())
    {
        if (!DEMO_MODE) {
            log("**** DEMO MODE: START ****");
            lcd.centered_text_multi({"DEMO MODE", "Hold Back", "to exit"});
            delay(1000);
           DEMO_MODE = true;
        }
        return;
    }

    if (button_back.just_pressed())
    {
        strip.button_feedback(W, rgb_blue);
        send_event(Back());
        if (DEMO_MODE) {
            log("**** DEMO MODE: STOP ****");
            lcd.centered_text_multi({"Exiting", "demo mode"});
            delay(1000);
            DEMO_MODE = false;

            // Recover from wherever we were interrupted
            send_event(Back()); // if ExecuteMode, back up
            send_event(Plus()); // if ChooseMode, move to next option
        }
    }
    if (button_select.just_pressed()) {
        strip.button_feedback(E, rgb_blue);
        send_event(Select());
    }
    if (button_minus.just_pressed()) {
        strip.button_feedback(S, rgb_blue);
        send_event(Minus());
    }
    if (button_plus.just_pressed()) {
        strip.button_feedback(N, rgb_blue);
        send_event(Plus());
    }

}

void next_demo_event()
{
    switch(DEMO_LOOP_EVENTS[demo_loop_index])
    {
        case de_back:
            send_event(Back());
            break;
        case de_plus:
            send_event(Plus());
            break;
        case de_select:
            send_event(Select());
            break;
    }
    demo_loop_index = (demo_loop_index + 1) % DEMO_LOOP_EVENTS.size();
    delay(DEMO_DELAY);
}


/*
---------------------------------------------------
    Routines to read the various sensors
---------------------------------------------------
*/


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

    Wire1.beginTransmission(MPUadr);
    Wire1.write(0x6B);
    Wire1.write(0);
    Wire1.endTransmission(true);
}

void ReadMPU()
{
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
