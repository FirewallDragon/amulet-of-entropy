#ifndef UTILS_H
#define UTILS_H

/*
=======================================================================================
    Just a place to keep common routines. It also isolates all the serial monitor
    writing code in one place.
=======================================================================================
*/


#include <stdio.h>
#include <stdarg.h>


// Set this to 'true' for verbose logging
const bool DEBUG_ON = false;

extern void log(const char *format, ...);
extern void debug(const char *format, ...);

#endif // UTILS_H