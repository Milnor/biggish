#include <stdio.h>
#include <stdlib.h>

#include "../include/biggish.h"

int main(int argc, char * argv[])
{
#if LIMB_SIZE == 32
    uint32_t big_number[8] = {1, 2, 3, 4, 5, 6, 7, 8};
#elif LIMB_SIZE == 64
    uint64_t big_number[4] = {1, 2, 3, 4};
#endif
    uint256_t * big = biggish_u256_init(big_number);

    //uint512_t * bigger;

    char * big_str = biggish_u256_hex_str(big);
    //char * bigger_str = biggish_u512_hex_str(bigger);

    printf("Limb size of this build: %d bytes\n", biggish_limb_size());

    printf("big =    0x%s\n", big_str);
    //printf("bigger = 0x%s\n", bigger_str);

    free(big);
    free(big_str);
    //free(bigger_str);

    return EXIT_SUCCESS;
}
