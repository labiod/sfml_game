#include "Log.hpp"

#ifndef NDEBUG
/**
 * START DEBUG SECTION
 */
#include <stdio.h>
#include <stdarg.h>
#include <iostream>

#define LOG_BUFFER_SIZE 1024

void Log::d(const char* tag, const char* msg, ...) {

    // debug mode
    va_list args;
    va_start(args, msg);
    char buffer[LOG_BUFFER_SIZE];
    vsnprintf(buffer, LOG_BUFFER_SIZE, msg, args);
    std::string msg_str(buffer);
    std::cout << tag << ": " << msg_str << std::endl;
}

void Log::e(const char* tag, const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    char buffer[LOG_BUFFER_SIZE];
    vsnprintf(buffer, LOG_BUFFER_SIZE, msg, args);
    std::cerr << tag << ": " << buffer << std::endl;
}
/**
 * END DEBUG section
 */
#else
void Log::d(const char* tag, const char* msg, ...) {}

void Log::e(const char* tag, const char* msg, ...) {}
#endif