#ifndef _BIGGISH_H
#define _BIGGISH_H

#include <stdint.h>

    #ifndef LIMB_SIZE
        #define LIMB_SIZE   32
        #define LIMB_TYPE   uint32_t
    #else
        #define LIMB_TYPE   uint64_t
    #endif  // LIMB_SIZE

typedef struct __u256 uint256_t;
typedef struct __u512 uint512_t;

char * biggish_256_hex_str(uint256_t);
char * biggish_512_hex_str(uint512_t);

#endif  // _BIGGISH_H
