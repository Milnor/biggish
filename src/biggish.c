#include <inttypes.h> 
#include <stdio.h>
#include <stdlib.h>

#include "../include/biggish.h"

#define HEXSTR32BIT     8                       // e.g. ffffffff
#define HEXSTR64BIT     (2 * HEXSTR32BIT)       // e.g. ffffffffffffffff
#define U256MAXSTR      (4 * HEXSTR64BIT) + 1   // include NULL
#define U512MAXSTR      (8 * HEXSTR64BIT) + 1

struct __u256
{
    LIMB_TYPE   limbs[U256LIMBS];
};

struct __u512
{
    LIMB_TYPE   limbs[U512LIMBS];
};

int biggish_limb_size()
{
    return sizeof(LIMB_TYPE);
}

uint256_t * biggish_u256_init0()
{
    uint256_t * number = calloc(1, sizeof(uint256_t));
    if (NULL == number)
    {
        perror("calloc failed");
    }

    return number;
}

uint256_t * biggish_u256_init(const LIMB_TYPE array[U256LIMBS])
{
    uint256_t * number = biggish_u256_init0();
    if (NULL == number)
    {
        // biggish_u256_init0() already reported the error via perror()
        return NULL;
    }

    for (size_t i = 0; i < U256LIMBS; i++)
    {
        number->limbs[i] = array[i];
    }

    return number;
}

char * biggish_u256_hex_str(uint256_t * number)
{
    if (NULL == number)
    {
        return NULL;
    }

    char * hex = malloc(U256MAXSTR);
    if (NULL == hex)
    {
        perror("malloc failed");
        return NULL;
    }

#if LIMB_SIZE == 32    
    snprintf(hex, U256MAXSTR,
        "%08" PRIX32 "%08" PRIX32 "%08" PRIX32 "%08" PRIX32
        "%08" PRIX32 "%08" PRIX32 "%08" PRIX32 "%08" PRIX32,
        number->limbs[7], number->limbs[6], number->limbs[5], number->limbs[4],
        number->limbs[3], number->limbs[2], number->limbs[1], number->limbs[0]);
#elif LIMB_SIZE == 64
    snprintf(hex, U256MAXSTR,
        "%016" PRIX64 "%016" PRIX64 "%016" PRIX64 "%016" PRIX64,
        number->limbs[3], number->limbs[2], number->limbs[1], number->limbs[0]);
#endif
    return hex;
}