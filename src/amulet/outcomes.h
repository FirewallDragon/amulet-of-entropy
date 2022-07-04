#ifndef OUTCOMES_HPP
#define OUTCOMES_HPP

/*
=======================================================================================
    This data structure describes the possible outcomes for any given mode.
    Originally, I displayed test instead of images, which is why there's a lot of
    strings here. They're not really used anymore.
=======================================================================================
*/

#include <string>
#include <map>

using std::string;


// Color definitions (stolen from Arduino_GFX.h)
#define BLACK 0x0000       ///<   0,   0,   0
#define NAVY 0x000F        ///<   0,   0, 123
#define DARKGREEN 0x03E0   ///<   0, 125,   0
#define DARKCYAN 0x03EF    ///<   0, 125, 123
#define MAROON 0x7800      ///< 123,   0,   0
#define PURPLE 0x780F      ///< 123,   0, 123
#define OLIVE 0x7BE0       ///< 123, 125,   0
#define LIGHTGREY 0xC618   ///< 198, 195, 198
#define DARKGREY 0x7BEF    ///< 123, 125, 123
#define BLUE 0x001F        ///<   0,   0, 255
#define GREEN 0x07E0       ///<   0, 255,   0
#define CYAN 0x07FF        ///<   0, 255, 255
#define RED 0xF800         ///< 255,   0,   0
#define MAGENTA 0xF81F     ///< 255,   0, 255
#define YELLOW 0xFFE0      ///< 255, 255,   0
#define WHITE 0xFFFF       ///< 255, 255, 255
#define ORANGE 0xFD20      ///< 255, 165,   0
#define GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define PINK 0xFC18        ///< 255, 130, 198


struct Outcome
{
    Outcome() :
            _name("def_name"),
            _jpeg_filename("def_jpeg") {};

    Outcome(const string & outcome_name,
            const string & jpeg_filename,
            unsigned int name_text_size = 3,
            unsigned int name_fg = WHITE,
            unsigned int name_bg = BLACK,
            unsigned int jpeg_bg = BLACK) :
            _name(outcome_name),
            _jpeg_filename(jpeg_filename),
            _name_text_size(name_text_size),
            _name_fg(name_fg),
            _name_bg(name_bg),
            _jpeg_bg(jpeg_bg) { };

    Outcome(const string & outcome_name,
            unsigned int name_text_size = 3,
            unsigned int name_fg = WHITE,
            unsigned int name_bg = BLACK) :
            _name(outcome_name),
            _name_text_size(name_text_size),
            _name_fg(name_fg),
            _name_bg(name_bg) { };

    const string _name;
    unsigned int _name_text_size;
    unsigned int _name_fg;
    unsigned int _name_bg;

    const string _jpeg_filename = "";
    unsigned int _jpeg_bg;

    const char * name() const { return _name.c_str(); }
};

typedef std::map<int, Outcome> OutcomeMap;


/*
----------------------------------------------------------------------
    If you want to add your own modes, this is one place you need to
    add them. Search on one of these items to find the other places.
----------------------------------------------------------------------
*/
extern OutcomeMap coinFlipOutcomes;
extern OutcomeMap pickCardOutcomes;
extern OutcomeMap eightBallOutcomes;
extern OutcomeMap d6Outcomes;
extern OutcomeMap tarotOutcomes;

#endif // OUTCOMES_HPP