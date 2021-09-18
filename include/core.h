#pragma once

#define CLOCK_SPEED 4194304

#include "logger.h"

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define IS_BIG_ENDIAN
#else
    #define IS_LITTLE_ENDIAN
#endif

#ifndef NDEBUG
    #ifndef EXE_NAME
        #define EXE_NAME "executible"
    #endif

    #define ASSERT(x, msg)  if(!x)                                                                  \
                            {                                                                       \
                                CRITICAL(EXE_NAME << ": " << __FILE__ << ":" << __LINE__ << ": "       \
                                << __PRETTY_FUNCTION__ << ": Assertion `" << #x << "' failed.");    \
                                CRITICAL(msg);                                                         \
                                std::abort();                                                       \
                            }
#else
    #define ASSERT(x, msg) ((void)0)
#endif

#define GAMEBOY_WIDTH   160
#define GAMEBOY_HEIGHT  144

#define VRAM_WIDTH      256
#define VRAM_HEIGHT     256

#define CLOCK_HZ        4194304

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;

typedef int8_t i8;
typedef int16_t i16;