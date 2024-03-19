#ifndef CONSTANTS_HH
#define CONSTANTS_HH

#include <cstdint>
#include <bitset>

typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t U8;

template<typename T>
inline bool get_bit(T b, U8 i) {
    return b & (static_cast<T>(1) << i);
}

// Define each bit in the "gene" (i.e. 64-bit integer) as either present (1) or not present (0)
enum class Trait {
    SlowMetabolism,
    BetterVision,
    // TODO: Define more traits here (up to 64)
};

#endif