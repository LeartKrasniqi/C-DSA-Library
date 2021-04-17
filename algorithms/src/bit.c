/* Implementation of Bit Operations */
#include "bit.h"

/* Get a bit at a certain position */
int bit_get(const unsigned char *buf, int pos)
{
    /* Create mask for the bit to obtain -- Binary = 10000000  */
    unsigned char mask = 0x80;
    
    /* Set the bit in the mask to the proper position 
         - Since buf is a char array, need to set proper bit within byte
         - Ex: To extract bit at pos 14 of   11111000 00111110 11101110
             Total Size = 24 bits = 3 bytes
             bit 14 is within 2nd byte
             bit 14 is at pos 6 of 2nd byte
             Need to set bit at pos 6 of mask  
               ==> mask = 00000010
    */
    for(int i = 0; i < (pos % 8); i++)
       mask >>= 1; 

    /* Perform bitwise AND of mask and byte containing desired bit
         - Bitwise AND with mask will return 0 if desired bit is 0 (since all other bits in mask are 0)
         - Ex: To extract bit at pos 14 of   11111000 00111110 11101110
             mask = 00000010
             desired_byte = 00111110
             bitwise AND = 00000010 & 00111110 = 00000010 > 0  
               ==> Desired bit was a 1
    */ 
    int val = (mask & buf[(int)(pos/8)]) ? 1 : 0;

    return val;
}


/* Set the bit at a certain position */
void bit_set(unsigned char *buf, int pos, int state)
{
    /* Create a mask for the but to set -- Binary = 10000000 */
    unsigned char mask = 0x80;

    /* Set the bit in the mask to the proper position 
         - Since buf is a char array, need to set proper bit within byte
         - Ex: To set bit at pos 14 of   11111000 00111110 11101110
             Total Size = 24 bits = 3 bytes
             bit 14 is within 2nd byte
             bit 14 is at pos 6 of 2nd byte
             Need to set bit at pos 6 of mask  
               ==> mask = 00000010
    */
    for(int i = 0; i < (pos % 8); i++)
       mask >>= 1;

    /* Set the bit according to the state
         - To set a bit to 1, perform bitwise OR with mask (since this will return 1 in that pos)
         - To set a but to 0, perform bitwise AND with ~mask (since ~mask has a 0 in the proper pos)
         - Ex: Setting bit at pos 14 of 11111000 00111110 11101110
             - Setting to 1:
                 mask = 00000010
                 desired_byte = 00111110  (Desired bit is at pos 6)
                 bitwise OR = 00111110
                   ==> Desired bit is a 1
             - Setting to 0:
                 ~mask = 11111101
                 desired_byte = 00111110  (Desired bit is at pos 6)
                 bitwise AND = 00111100
                   ==> Desired bit is a 0
    */
    if(state)
        buf[(int)(pos/8)] |= mask;
    else
        buf[(int)(pos/8)] &= (~mask);
}


/* Perform bitwise AND */
void bit_and(const unsigned char *buf1, const unsigned char *buf2, unsigned char *bufo, int num_bits)
{
    for(int i = 0; i < num_bits; i++)
    {
        int bit1 = bit_get(buf1, i);
        int bit2 = bit_get(buf2, i);
        int bito = bit1 ? bit2 : 0;
        bit_set(bufo, i, bito);
    }
}


/* Perform bitwise OR */
void bit_or(const unsigned char *buf1, const unsigned char *buf2, unsigned char *bufo, int num_bits)
{
    for(int i = 0; i < num_bits; i++)
    {
        int bit1 = bit_get(buf1, i);
        int bit2 = bit_get(buf2, i);
        int bito = bit1 ? 1 : bit2;
        bit_set(bufo, i, bito);
    }
}


/* Perform bitwise XOR */
void bit_xor(const unsigned char *buf1, const unsigned char *buf2, unsigned char *bufo, int num_bits)
{
    for(int i = 0; i < num_bits; i++)
    {
        int bit1 = bit_get(buf1, i);
        int bit2 = bit_get(buf2, i);
        int bito = (bit1==bit2) ? 0 : 1;
        bit_set(bufo, i, bito);
    }
}


/* Rotate bits leftward (with wrap-around) */
void bit_rotate_left(unsigned char *buf, int num_bits, int count)
{
    /* Ensure buffer is non-empty */
    if(num_bits <= 0)
        return;

    /* Perform the body once per rotation */
    for(int i = 0; i < count; i++)
    {
        /* This will hold the bit that must be wrapped around to right-end of buf */
        int wrap_around_bit;
        
        /* Loop through each byte */
        for(int j = 0; j <= (int)((num_bits-1)/8); j++)
        {
            /* Save the bit to be shifted (i.e., the left-most bit of this byte) */ 
            int bit_to_be_shifted = bit_get(&buf[j], 0);
            
            /* If this is the first byte, need to handle wrap-around so save this bit */
            if(j == 0)
                wrap_around_bit = bit_to_be_shifted;
            /* Otherwise, set the right-most bit of previous byte to the bit to be shifted */
            else
                bit_set(&buf[j-1], 7, bit_to_be_shifted);

            /* Shift the current byte to the left */
            buf[j] <<= 1;
        }

        /* Now, set the right-most bit of the buffer to the bit shifted off the first byte (i.e., the wrap-around bit) */
        bit_set(buf, num_bits - 1, wrap_around_bit);
    }
}

