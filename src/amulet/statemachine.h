#ifndef STATEMACHINE_H
#define STATEMACHINE_H

/*
=======================================================================================
    This is a simple statemachine, using tinyfsm.
    See docs/Contrib.md for high level design.
=======================================================================================
*/

#include <stdio.h>

#include "tinyfsm.hpp"
#include "utils.h"


// ============ EVENTS ===========================

struct AmuletEvent
: public tinyfsm::Event {
    virtual const char * name() const { return "AmuletEvent"; }
};

// Internal events
struct PoolFull : public AmuletEvent {
    const char * name() const { return "PoolFull"; }
};
struct PoolEmpty : public AmuletEvent {
    const char * name() const { return "PoolEmpty"; }
};

// External events (buttons)
struct Select : public AmuletEvent {
    const char * name() const { return "Select"; }
};
struct Plus : public AmuletEvent {
    const char * name() const { return "Plus"; }
};
struct Minus : public AmuletEvent {
    const char * name() const { return "Minus"; }
};
struct Back : public AmuletEvent {
    const char * name() const { return "Back"; }
};



// ============ STATES ===========================

// Amulet state machine
class Amulet
: public tinyfsm::Fsm<Amulet>
{
public:
    /* default reaction for unhandled events */
    void react(AmuletEvent const & e)
    {
        log("%s: ignore event %s", name(), e.name());
    };

    virtual const char * name() { return "Amulet"; }

    // Entry/exit actions
    virtual void entry(void) { };
    virtual void exit(void)  { };

    // Button events
    virtual void react(Select const &);
    virtual void react(Plus const &);
    virtual void react(Minus const &);
    virtual void react(Back const &);

    // Internal events
    virtual void react(PoolFull const &);
    virtual void react(PoolEmpty const &);
};

// Amulet states: top level (choosing mode)
// From here you either go to the next option (Plus/Minus) or choose a mode (Select)

class Initializing
: public Amulet
{
    const char * name() { return "Initializing"; }

    void entry() override;
    void exit() override;

    // Button events
    void react(Plus const &) {}; // do nothing
    void react(Minus const &) {}; // do nothing
    void react(Select const &) {}; // do nothing
    void react(Back const &) {}; // do nothing

    // Internal events
    void react(PoolFull const &) override;
    void react(PoolEmpty const &) {}; // do nothing
};

class ChooseMode
: public Amulet
{
public:
    const char * name() { return "ChooseMode"; }

    void entry() override;

    // Button events
    void react(Plus const &) override;
    void react(Minus const &) override;
    void react(Select const &) override;
    void react(Back const &) {}; // do nothing

    // Internal events
    void react(PoolFull const &) {}; // do nothing
    void react(PoolEmpty const &) {}; // do nothing
};


class ExecuteMode
: public Amulet
{
public:
    const char * name() { return "ExecuteMode"; }

    // Entry/exit actions
    void entry(void);

    // Button events
    void react(Plus const &) {}; // do nothing
    void react(Minus const &) {}; // do nothing
    void react(Select const &);
    void react(Back const &);

    // Internal events
    void react(PoolFull const &) {}; // do nothing
    void react(PoolEmpty const &);

private:
    void choose_outcome();
};

#endif // STATEMACHINE_H