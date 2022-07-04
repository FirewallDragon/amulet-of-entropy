#include "button.h"
#include "utils.h"

// debug log convenience mathod
const char * is_pressed(bool reading) {
    return (reading ? "PRESSED" : "not pressed");
}


bool Button::read_button()
{
    bool reading = !(digitalRead(_pin));

    if (reading != _previous_reading)
    {
        // record the time of the state change
        _last_reading_change = millis();
    }

    if ((millis() - _last_reading_change) > _debounce_delay_millis)
    {
        if (reading == PRESSED) {
            debug("BUTTON[%s]: is down", name());
        }
        // the value has been stable long enough to pay attention to changes
        if (reading != _state)
        {
            debug("BUTTON[%s]: state change: %s --> %s", name(), is_pressed(_state), is_pressed(reading));
            _state = reading;
            if (_state)
                debug("BUTTON[%s]: pressed!", name());
        }
    }

    _previous_reading = reading;
    return _state;
}
