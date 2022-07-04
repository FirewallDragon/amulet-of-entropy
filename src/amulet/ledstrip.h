#ifndef LEDSTRIP_H
#define LEDSTRIP_H

/*
=======================================================================================
    Singleton object that represents the NeoPixels (RGB LEDs).
=======================================================================================
*/

#include <vector>
#include <Adafruit_NeoPixel.h>

using namespace std;


// Common RGB colors
using RGBColor = uint32_t;
const RGBColor rgb_red =    Adafruit_NeoPixel::Color(255, 0, 0);
const RGBColor rgb_orange = Adafruit_NeoPixel::Color(255, 60, 0);
const RGBColor rgb_yellow = Adafruit_NeoPixel::Color(255, 150, 0);
const RGBColor rgb_green =  Adafruit_NeoPixel::Color(0, 255, 0);
const RGBColor rgb_blue =   Adafruit_NeoPixel::Color(0, 0, 255);
const RGBColor rgb_indigo = Adafruit_NeoPixel::Color(75, 0, 130);
const RGBColor rgb_violet = Adafruit_NeoPixel::Color(138, 43, 226);
const RGBColor rgb_white =  Adafruit_NeoPixel::Color(255, 255, 255);
const RGBColor rgb_black =  Adafruit_NeoPixel::Color(0, 0, 0);


// Brightness levels (0-255)
const int rgb_max = 255;
const int rgb_bright = 200;
const int rgb_medium = 100;
const int rgb_dim = 50;

// LED array elements
extern vector<int> led_arrows;
extern vector<int> led_eyes;
enum led_locations {NW=0, N=1, NE=2, E=3, SE=4, S=5, SW=6, W=7};


class LEDStrip
{
    public:
        static LEDStrip& get_instance()
        {
            static LEDStrip instance;
            instance.initialize();
            return instance;
        }

        void initialize();
        void off();

        void button_feedback(led_locations loc, RGBColor c, unsigned int percent = 100);

        void cycle();
        void sparkle_color(vector<int>);
        void sparkle(vector<int>);
        void color_wipe(uint32_t color, int wait);

        void set_pool_meter(unsigned int percent);

        void set_eyes(RGBColor c, unsigned int percent = 100);
        void set_arrows(RGBColor c, unsigned int percent = 100);

    private:
        LEDStrip() {};
        LEDStrip(LEDStrip const&);
        void operator=(LEDStrip const&);

        bool initialized = false;
};

#endif // LEDSTRIP_H
