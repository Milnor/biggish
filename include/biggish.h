#ifndef _BIGGISH_H
#define _BIGGISH_H

#include <stdint.h>

    #ifndef LIMB_SIZE
        #define LIMB_SIZE   32          // default to 32
        #define LIMB_TYPE   uint32_t
    #elif LIMB_SIZE == 32               // explicit 32
        #define LIMB_TYPE   uint32_t
    #elif LIMB_SIZE == 64
        #define LIMB_TYPE   uint64_t
    #else
        #error
    #endif  // LIMB_SIZE

#define U256LIMBS       (256 / LIMB_SIZE)
#define U512LIMBS       (512 / LIMB_SIZE)

typedef struct __u256 uint256_t;
typedef struct __u512 uint512_t;

/**
 * @brief Return the size of a limb (depends on build settings).
 * @return Size of a single limb in bytes.
 */
int biggish_limb_size();

/**
 * @brief Create a uint256_t object initialized to 0.
 * @return Pointer to the uint256_t object or NULL on failure.
 */
uint256_t * biggish_u256_init0();

/**
 * @brief Create a uint256_t object initialized to an arbitary value.
 * @param array Fixed-length array of limbs, ordered least significant to most.
 * @return Pointer to the uint256_t object or NULL on failure.
 */
uint256_t * biggish_u256_init(const LIMB_TYPE array[U256LIMBS]);

/**
 * @brief Allocate a string containing the number in hexadecimal.
 * @param number Pointer to the uint256_t object.
 * @return Pointer to a NULL-terminated string or NULL on failure.
 * @note Caller is responsible for freeing the returned string.
 */
char * biggish_u256_hex_str(uint256_t * number);

//char * biggish_u512_hex_str(uint512_t * number);

#endif  // _BIGGISH_H
