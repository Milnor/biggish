#include <stdio.h>
#include <stdlib.h>

#include "../include/biggish.h"

int main(int argc, char * argv[])
{
    uint256_t big = {0};
    uint512_t bigger = {0};

    char * big_str = biggish_256_hex_str(big);
    char * bigger_str = biggish_512_hex_str(bigger);

    printf("big =    0x%s\n", big_str);
    printf("bigger = 0x%s\n", bigger_str);

    free(big_str);
    free(bigger_str);

    return EXIT_SUCCESS;
}
