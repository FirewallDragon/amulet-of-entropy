#include <vector>

#include "statemachine.h"
#include "utils.h"
#include "entropypool.h"
#include "outcomes.h"
#include "roundlcd.h"
#include "ledstrip.h"

using std::vector;
using std::string;


// Handles to the various singleton objects
static RoundLCD& lcd = RoundLCD::get_instance();
static LEDStrip& strip = LEDStrip::get_instance();
static EntropyPool& pool = EntropyPool::get_instance();


// Utility debug logging functions
void debug_event(const char * event_name) {
    debug("EVENT: %s", event_name);
};
void debug_transition(const char * event_name, const char * curr_state, const char * next_state) {
    debug("TRANSITION: [%s] --- (%s) ---> [%s]",
        curr_state, event_name, next_state);
};


/*
==================================================================================
    Simple data structure for each possible amulet mode. Give it a name and
    list of possible outcomes.
==================================================================================
*/

struct AmuletMode
{
    AmuletMode(const string & name, OutcomeMap& omap) :
    _name(name), _omap(omap) { };

    const string _name;
    const char * name() const { return _name.c_str(); }

    OutcomeMap _omap;
};

static int mode_index = 0;

static const vector<AmuletMode> modes = {
    AmuletMode("Coin Flip", coinFlipOutcomes),
    AmuletMode("Roll Die", d6Outcomes),
    AmuletMode("Pick Card", pickCardOutcomes),
    AmuletMode("Tarot Card", tarotOutcomes),
    AmuletMode("Magic 8 Ball", eightBallOutcomes),
};



/*
==================================================================================
    STATES. See docs/Contrib for more info.
==================================================================================
*/


/*
------------------------------------------------------------------
    Initializing. Used when the emtropy pool is filling up.
------------------------------------------------------------------
*/

void Initializing::entry()
{
    log("Initializing system");
}

void Initializing::exit()
{
    log("Done initializing");
}

void Initializing::react(PoolFull const & e)
{
    debug_event("PoolFull");

    auto action = [] {
        //
    };
    debug_transition(e.name(), name(), "ChooseMode");
    transit<ChooseMode>(action);
}



/*
------------------------------------------------------------------
    ChooseMode. Once pool is full, this is the state where the
    user has to choose a mode. Options:
    - Plus/Minus: cycle through options
    - Select: choose the offered mode (go to ExecuteMode). Also
        executes the first random choice (why wait?).
    - PoolEmpty: if the pool runs dry, go back to Initializing.
------------------------------------------------------------------
*/

void ChooseMode::entry()
{
    log("Use Plus/Minus to find mode, Select to choose");

    lcd.set_bg_color(BLACK);
    lcd.set_text_props(3, YELLOW, BLACK);

    lcd.centered_text(modes[mode_index].name());
}

void ChooseMode::react(Plus const & e) {
    mode_index = (mode_index + 1) % modes.size();
    lcd.centered_text(modes[mode_index].name());
    debug("ChooseMode[%s]: current option = %s", e.name(), modes[mode_index].name());
}

void ChooseMode::react(Minus const & e) {
    mode_index = (mode_index - 1) % modes.size();
    lcd.centered_text(modes[mode_index].name());
    debug("ChooseMode[%s]: current option = %s", e.name(), modes[mode_index].name());
}

void ChooseMode::react(Select const & e) {
    AmuletMode next_mode = modes[mode_index];
    log("ChooseMode[%s]: selected mode = %s", e.name(), next_mode.name());

    auto action = [] {
        //
    };

    debug_transition(e.name(), name(), next_mode.name());
    transit<ExecuteMode>(action);
}


/*
------------------------------------------------------------------
    ExecuteMode. This is where the magic happens! Randomly select
    an outcome and display the results on the LCD and/or LED strip.
    - Select: do it again (choose_outcome) - drains entropy pool
    - Back: return to ChooseMode
------------------------------------------------------------------
*/

void ExecuteMode::choose_outcome()
{
    EntropyPool& pool = EntropyPool::get_instance();

    AmuletMode myMode = modes[mode_index];

    int possibilities = myMode._omap.size();
    int choice = pool.random_int(possibilities);

    if ( choice == 0 )
    {
        log("choose_outcome failed, pool empty");
        lcd.set_text_props(3, RED, BLACK);
        lcd.centered_text_multi({"ERROR", "Pool empty"});
    }
    else
    {
        Outcome o = myMode._omap[choice];
        log("Mode[%s]: outcome(%d) = '%s'", myMode.name(), choice, o.name());
        lcd.drawJpeg(o._jpeg_filename);
    }
}

void ExecuteMode::entry()
{
    debug_event("entry");
    choose_outcome();
}

void ExecuteMode::react(Select const & e) {
    debug_event("select");
    choose_outcome();
}

void ExecuteMode::react(Back const & e) {
    debug_event("back");

    auto action = [] {
        //
    };
    debug_transition(e.name(), name(), "ChooseMode");
    transit<ChooseMode>(action);
}

void ExecuteMode::react(PoolEmpty const & e) {
    debug_event("PoolEmpty");

    auto action = [] {
        //
    };
    debug_transition(e.name(), name(), "Initializing");
    transit<Initializing>(action);
}
