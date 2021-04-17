/* Header for Useful Bit Operations */
#ifndef _BIT_H
#define _BIT_H
#include <stdlib.h>
#include <string.h>

/* Purpose:
     - C has bit operators that only work with intrinsic integral operands
     - The following methods work with buffers containing an arbitrary number of bits
*/ 


/*
*********************************
        Interface Methods
*********************************
*/

/* Obtain a bit at a certain position
    @param buf  Buffer of bits
    @param pos  Desired position

    @return Value of desired bit (i.e., 1 or 0)

    Notes:
      - The left-most position in the buffer is 0
      - Complexity: O(1)
*/
int bit_get(const unsigned char *buf, int pos);


/* Set a bit at a certain position
    @param buf  Buffer of bits
    @param pos  Desired position
    @param val  Desired state of bit

    @return None

    Notes:
      - The left-most position in the buffer is 0
      - val must be 1 or 0
      - Complexity: O(1)
*/
void bit_set(unsigned char *buf, int pos, int val);


/* Perform bitwise AND, OR, and XOR of two buffers
    @param buf1      First buffer of bits
    @param buf2      Second buffer of bits
    @param bufo      Buffer to hold result 
    @param num_bits  Number of bits in each buffer

    @return None

    Notes:
      - It is the responsibility of the caller to manage the storage required by bufo
      - Complexity: O(b), where b is the number of bits in each buffer
*/
void bit_and(const unsigned char *buf1, const unsigned char *buf2, unsigned char *bufo, int num_bits);
void bit_or(const unsigned char *buf1, const unsigned char *buf2, unsigned char *bufo, int num_bits);
void bit_xor(const unsigned char *buf1, const unsigned char *buf2, unsigned char *bufo, int num_bits);


/* Rotate bits leftward (with wrap-around)
    @param buf       Buffer of bits
    @param num_bits  Number of bits in buffer
    @param count     Number of bits to be rotated

    @return None

    Notes:
      - After the operation, the left-most count bits become the the count right-most bits
      - Ex: 0111001 --> Rotate 3 --> 1001011
      - Complexity: O(nb), where n is the number of bits to be rotated and b is the number of bits in the buffer
*/
void bit_rotate_left(unsigned char *buf, int num_bits, int count);

#endif
