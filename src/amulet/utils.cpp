#include "utils.h"
#include <Wire.h>

void write_to_serial(const char *msg)
{
    // NOTE!! If you try to write to serial before it's ready, everything will lock up.
    if (!Serial)
    {
        return;
    }
    Serial.println(msg);
}

void log(const char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    write_to_serial(buffer);
    va_end(args);
}

void debug(const char *format, ...)
{
    if (DEBUG_ON)
    {
        char buffer[256];
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        write_to_serial(buffer);
        va_end(args);
    }
}
