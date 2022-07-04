#include "ledstrip.h"
#include "utils.h"

using namespace std;

const int LED_PIN = 26;
const int LED_COUNT = 8;
Adafruit_NeoPixel _strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


// LED array assignments (compass rose notation, up == North)
vector<int> led_arrows = {1, 3, 5, 7};  // N, E, S, W
vector<int> led_eyes =   {0, 2, 4, 6};  // NW, NE, SE, SW

// ROYGBIV!!
vector<RGBColor> rainbow {rgb_red, rgb_orange, rgb_yellow, rgb_green, rgb_blue, rgb_indigo, rgb_violet};



// ---------------------------------------------------------
// Utility methods

RGBColor adjust_brightness(RGBColor c, unsigned int percent_of_max)
{
    float ratio = percent_of_max/100.0;

    int b = c & 0xFF;
    int g = (c >> 8) & 0xFF;
    int r = (c >> 16) & 0xFF;

    return Adafruit_NeoPixel::Color(r * ratio, g * ratio, b * ratio);
}


// ---------------------------------------------------------
// LEDStrip implementations

void LEDStrip::initialize()
{
    if (! initialized)
    {
        log("Initializing LED strip");
        _strip.begin();
        _strip.setBrightness(rgb_dim);
        _strip.show(); // start "off"
        initialized = true;
    }
}

void LEDStrip::off()
{
    debug("LEDStrip::off");
    _strip.fill();
    _strip.show();
}

// We represent the depth of the entropy pool with dragon eyes color.
void LEDStrip::set_pool_meter(unsigned int percent)
{
    if (percent >= 0 && percent <= 5) {
        set_eyes(rgb_red, 50);
    }
    else if (percent > 5 && percent <= 50) {
        set_eyes(rgb_orange, 50);
    }
    else if (percent > 50 && percent < 100) {
        set_eyes(rgb_yellow, 50);
    }
    else if (percent == 100) {
        set_eyes(rgb_green, 50);
    }
    else {
        set_eyes(rgb_black); // off
    }
}


void LEDStrip::set_eyes(RGBColor c, unsigned int percent)
{
    debug("set_eyes, color: 0x%06X", c);
    for (int x : led_eyes) {
        _strip.setPixelColor(x, adjust_brightness(c, percent));
    }
    _strip.show();
}

void LEDStrip::set_arrows(RGBColor c, unsigned int percent)
{
    debug("set_arrows, color: 0x%06X", adjust_brightness(c, percent));
    for (int x : led_arrows) {
        _strip.setPixelColor(x, adjust_brightness(c, percent));
    }
    _strip.show();
}

void LEDStrip::button_feedback(led_locations loc, RGBColor c, unsigned int percent)
{
    _strip.setPixelColor(loc, adjust_brightness(c, percent));
    _strip.show();
    delay(50);
    _strip.fill();
}

void LEDStrip::cycle()
{
    for (int c : rainbow) {
        color_wipe(c, 25);
    }
}

void LEDStrip::sparkle_color(vector<int> led_list)
{
    int led_index;
    int rainbow_index;

    for (int i=0 ; i<100 ; i++)
    {
        led_index = (random() % led_list.size());
        rainbow_index = (random() % rainbow.size());
        _strip.setPixelColor(led_list[led_index], rainbow[rainbow_index]);
        _strip.show();
        delay(10);
    }

    _strip.fill();
    _strip.show();
}

void LEDStrip::sparkle(vector<int> led_list)
{
    int led_index;

    for (int i=0 ; i<100 ; i++)
    {
        led_index = (random() % led_list.size());
        _strip.setPixelColor(led_list[led_index], rgb_white);
        _strip.show();
        delay(10);
        _strip.fill();
        _strip.show();
    }

    _strip.fill();
    _strip.show();
}

void LEDStrip::color_wipe(RGBColor color, int wait)
{
    for (int i = 0; i < _strip.numPixels(); i++)
    {                                  // For each pixel in _strip...
        _strip.setPixelColor(i, color); //  Set pixel's color (in RAM)
        _strip.show();                  //  Update _strip to match
        delay(wait);                   //  Pause for a moment
    }
}
