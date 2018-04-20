#pragma once

#include <cassert>

using U64 = uint64_t;
using I64 = int64_t;

using U32 = uint32_t;
using I32 = int32_t;

using U16 = uint16_t;
using I16 = int16_t;

using I8 = int8_t;
using U8 = uint8_t;

//#define LOG_LOOP

#define LOG_INFO(x) (std::cout << x << std::endl << std::flush)
#define LOG_INFO_FORMAT(...) printf(__VA_ARGS__)

#if defined(LOG_LOOP)
# define LOG_INFO_LOOP1(x) (LOG_INFO(x))
#else
# define LOG_INFO_LOOP1(x) ((void)(x))
#endif
