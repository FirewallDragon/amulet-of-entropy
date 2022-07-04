#ifndef ROUNDLCD_H
#define ROUNDLCD_H

/*
=======================================================================================
    A singleton object that represents the round GA9A01 LCD display.
    More info: https://github.com/PaintYourDragon/Adafruit_GC9A01A
=======================================================================================
*/


#include <Arduino_GFX_Library.h>
#include <string>
#include <vector>

#include "JpegClass.h"

using namespace std;


class RoundLCD
{
    public:
        static RoundLCD& get_instance()
        {
            static RoundLCD instance;
            instance.initialize();
            return instance;
        }

        void set_bg_color(int color);
        void set_text_props(int size, int fg, int bg);

        void centered_text(const string &, bool clear_first=true) const;
        void centered_text_multi(vector<string> str, bool clear_first=true) const;

        void drawJpeg(const string & jpegFileName);

    private:
        RoundLCD() {};
        RoundLCD(RoundLCD const&);
        void operator=(RoundLCD const&);

        void initialize();

        static int jpegDrawCallback(JPEGDRAW *pDraw);

        Arduino_GFX * _gfx;
        Arduino_GFX * get_gfx();
};

#endif // ROUNDLCD_H