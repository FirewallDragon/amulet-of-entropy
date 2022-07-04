#include <math.h>
#include <LittleFS.h>
#include <stdio.h>


#include "roundlcd.h"
#include "utils.h"

using namespace std;

static JpegClass jpegClass;


const int SPI_SCK = 0;
const int SPI_MOSI = 1;
const int SPI_RESET = 2;
const int SPI_DC = 3;
const int SPI_CS = 4;
const int SPI_MISO = -1; // not used
const int ROTATION = 0;

const int SCREEN_WIDTH = 240;
const int SCREEN_HEIGHT = 240;


void RoundLCD::initialize()
{
    if (! _gfx)
    {
        log("Initializing LCD display");
        Arduino_DataBus *bus = new Arduino_SWSPI(SPI_DC, SPI_CS, SPI_SCK, SPI_MOSI, SPI_MISO);
        _gfx = new Arduino_GC9A01(bus, SPI_RESET, ROTATION, true); // IPS=true
        _gfx->begin();
        _gfx->fillScreen(BLACK);
    }
}

Arduino_GFX* RoundLCD::get_gfx()
{
    initialize();
    return _gfx;
}

void RoundLCD::set_bg_color(int color) {
    _gfx->fillScreen(color);
}

void RoundLCD::set_text_props(int size, int fg, int bg)
{
    _gfx->setTextSize(size);
    _gfx->setTextColor(fg, bg);
}

void RoundLCD::centered_text_multi(vector<string> lines, bool clear_first) const
{
    int16_t x1;
    int16_t y1;
    uint16_t width;
    uint16_t height;
    uint16_t line_spacing; // space between lines

    if (clear_first) {
        _gfx->fillScreen(BLACK);
    }

    // Get the height one line, assume it's the same for all
    const char * first_line = lines[0].c_str();
    _gfx->getTextBounds(first_line, 0, 0, &x1, &y1, &width, &height);
    line_spacing = height / 6;

    uint16_t block_height = (height + line_spacing) * lines.size();
    uint16_t block_start_y = (SCREEN_HEIGHT - block_height) / 2;

   for (int i = 0 ; i < lines.size() ; i++ )
    {
        const char * line = lines[i].c_str();
        uint16_t line_y = block_start_y + (i * (height + line_spacing));

        _gfx->getTextBounds(line, 0, 0, &x1, &y1, &width, &height);
        _gfx->setCursor((SCREEN_WIDTH - width) / 2, line_y);
        _gfx->println(line); // text to display
    }
}

void RoundLCD::centered_text(const string & text, bool clear_first) const
{
    int16_t x1;
    int16_t y1;
    uint16_t width;
    uint16_t height;

    if (clear_first) {
       _gfx->fillScreen(BLACK);
    }

    _gfx->getTextBounds(text.c_str(), 0, 0, &x1, &y1, &width, &height);

    // display on horizontal and vertical center
    _gfx->setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
    _gfx->println(text.c_str()); // text to display
}

int RoundLCD::jpegDrawCallback(JPEGDRAW *pDraw)
{
    RoundLCD& lcd = get_instance();
    lcd.get_gfx()->draw16bitBeRGBBitmap(pDraw->x, pDraw->y, pDraw->pPixels, pDraw->iWidth, pDraw->iHeight);
    return 1;
}

void RoundLCD::drawJpeg(const string & jpegFileName)
{
    unsigned long start = millis();

    // read JPEG file header
    jpegClass.draw(&LittleFS, (char *) jpegFileName.c_str(), jpegDrawCallback,
                   true, // useBigEndian
                   0, // X
                   0, // Y
                   _gfx->width(), // widthLimit
                   _gfx->height() // heightLimit
    );

    debug("Time to draw %s: %lu millis\n", jpegFileName.c_str(), millis() - start);
}
