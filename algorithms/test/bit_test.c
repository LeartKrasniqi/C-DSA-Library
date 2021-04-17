/* Testing Bit Operations */
#include <stdio.h>
#include <stdlib.h>

#include "bit.h"

void print_bits(unsigned char *buf, int num_bits);
unsigned char * invert_bits(unsigned char *bug, int num_bits);

int main()
{
    /* Create some bit buffers */
    unsigned char buf0[3] = {0x29, 0x4A, 0xF0};     /* 20 bits --> 00101001 01001010 1111 |-> ignored 0000 */
    unsigned char buf1[2] = {0x78, 0xBA};           /* 16 bits --> 01111000 10111010 */
    unsigned char buf2[1] = {0xCE};                 /* 5 bits  --> 11001 |-> ignored 110 */

    /* Print out the buffers */
    printf("---------- Buffers ----------\n");
    printf("buf0:  "); print_bits(buf0, 20); printf("\n");
    printf("buf1:  "); print_bits(buf1, 16); printf("\n");
    printf("buf2:  "); print_bits(buf2, 5); printf("\n");

    /* Set a few bits in the buffers */
    printf("\n---------- Set Bits ----------\n");
    printf("Old buf0:  "); print_bits(buf0, 20); printf("\n");
    bit_set(buf0, 8, 1);
    printf("New buf0:  "); print_bits(buf0, 20); printf(" (Changed pos 8)\n");
    printf("Old buf1:  "); print_bits(buf1, 16); printf("\n");
    bit_set(buf1, 1, 0);
    printf("New buf1:  "); print_bits(buf1, 16); printf(" (Changed pos 1)\n");
    printf("Old buf2:  "); print_bits(buf2, 5); printf("\n");
    bit_set(buf2, 4, 0);
    printf("New buf2:  "); print_bits(buf2, 5); printf(" (Changed pos 4)\n");

    /* Perform bitwise AND, OR, and XOR */
    unsigned char bufo[3] = {0};
    unsigned char zeros[3] = {0};
    unsigned char ones[3] = {0xFF, 0xFF, 0xFF};
    unsigned char *buf0_invert = invert_bits(buf0, 20);
    printf("\n---------- Bit Operations ----------\n");
    printf("buf0 :  "); print_bits(buf0, 20); printf("\n");
    printf("~buf0:  "); print_bits(buf0_invert, 20); printf("\n");
    printf("buf0 AND 0:  "); bit_and(buf0, zeros, bufo, 20); print_bits(bufo, 20); printf("\n");
    printf("buf0 OR  0:  "); bit_or(buf0, zeros, bufo, 20); print_bits(bufo, 20); printf("\n");
    printf("buf0 XOR 0:  "); bit_xor(buf0, zeros, bufo, 20); print_bits(bufo, 20); printf("\n"); 
    printf("buf0 AND 1:  "); bit_and(buf0, ones, bufo, 20); print_bits(bufo, 20); printf("\n");
    printf("buf0 OR  1:  "); bit_or(buf0, ones, bufo, 20); print_bits(bufo, 20); printf("\n");
    printf("buf0 XOR 1:  "); bit_xor(buf0, ones, bufo, 20); print_bits(bufo, 20); printf("\n");
    printf("buf0 AND ~buf0:  "); bit_and(buf0, buf0_invert, bufo, 20); print_bits(bufo, 20); printf("\n");
    printf("buf0 OR  ~buf0:  "); bit_or(buf0, buf0_invert, bufo, 20); print_bits(bufo, 20); printf("\n");
    printf("buf0 XOR ~buf0:  "); bit_xor(buf0, buf0_invert, bufo, 20); print_bits(bufo, 20); printf("\n");
    
    /* Rotating bits */
    printf("\n---------- Bit Rotate Left ----------\n");
    printf("buf0:  "); print_bits(buf0, 20); printf("\n");
    printf("buf1:  "); print_bits(buf1, 16); printf("\n");
    printf("buf2:  "); print_bits(buf2, 5); printf("\n");
    printf("Rotate buf0 by 19:  "); bit_rotate_left(buf0, 20, 19); print_bits(buf0, 20); printf("\n");
    printf("Rotate buf1 by  8:  "); bit_rotate_left(buf1, 16,  8); print_bits(buf1, 16); printf("\n");
    printf("Rotate buf1 by  8:  "); bit_rotate_left(buf1, 16,  8); print_bits(buf1, 16); printf("\n");
    printf("Rotate buf2 by  1:  "); bit_rotate_left(buf2,  5,  1); print_bits(buf2,  5); printf("\n"); 
    printf("Rotate buf2 by 25:  "); bit_rotate_left(buf2,  5, 25); print_bits(buf2,  5); printf("\n");
}

void print_bits(unsigned char *buf, int num_bits)
{
    for(int i = 0; i < num_bits; i++)
        printf("%d", bit_get(buf, i));
}

unsigned char * invert_bits(unsigned char *buf, int num_bits)
{
    unsigned char *inverted = malloc(((int)(num_bits/8)+1) * sizeof(*inverted));
    for(int i = 0; i < num_bits; i++)
    {
        int invert = bit_get(buf, i) ? 0 : 1;
        bit_set(inverted, i, invert);
    }
    return inverted;
}

