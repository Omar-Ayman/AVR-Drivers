#include "math.h"

u8 int_log_2(u64 n) {
    u8 res = 0;
    while (n >>= 1) ++res;
    return res;
}