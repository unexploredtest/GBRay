#include "miscellaneous.hpp"

u16 reverse2Bytes(u16 data) {
    u16 high = data & 0xFF;
    high = high << 8;
    data = data >> 8;
    u16 low = data & 0xFF;

    return high + low;
}