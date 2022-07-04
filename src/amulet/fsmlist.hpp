#ifndef FSMLIST_HPP_INCLUDED
#define FSMLIST_HPP_INCLUDED

#include "tinyfsm.hpp"
#include "statemachine.h"
#include "utils.h"

using fsm_list = Amulet;

template<typename E>
void send_event(E const & event)
{
    fsm_list::template dispatch<E>(event);
}


#endif
