#include "../include/biggish.h"

#define HEXSTR32BIT     8                       // e.g. ffffffff
#define HEXSTR64BIT     (2 * HEXSTR32BIT)       // e.g. ffffffffffffffff
#define U256MAXSTR      (4 * HEXSTR64BIT) + 1   // include NULL
#define U512MAXSTR      (8 * HEXSTR64BIT) + 1

struct __u256
{
    LIMB_TYPE   limbs[(256 / LIMB_SIZE)];
};

struct __u512
{
    LIMB_TYPE   limbs[(512 / LIMB_SIZE)];
};
