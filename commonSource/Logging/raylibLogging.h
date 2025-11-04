#ifndef RAYLIB_LOGING_WAPPER_H
#define RAYLIB_LOGING_WAPPER_H

#include <stdarg.h>

// Gets passed into Raylib so it will call this instead of just printf
void raylib_logging_function(int logLevel, const char *text, va_list args);

#endif // RAYLIB_LOGING_WAPPER_H
