#include "gv_lfsr.h"
#include <errno.h>

int lfsr_init(lfsr_t *lfsr, uint32_t seed, uint32_t feedback)
{
    if (lfsr == NULL)
    {
        return -EINVAL;
    }
    lfsr->seed = seed;
    lfsr->feedback = feedback;
}

uint32_t lfsr_next(lfsr_t *lfsr)
{
    // Extract the bits to XOR using the feedback mask
    uint32_t bits_to_xor = lfsr->seed & lfsr->feedback;

    // Compute the XOR of the extracted bits
    uint32_t xor_result = 0;
    while (bits_to_xor)
    {
        xor_result ^= (bits_to_xor & 1); // XOR the least significant bit
        bits_to_xor >>= 1;               // Shift to process the next bit
    }

    // Shift the seed and insert the XOR result into the MSB
    lfsr->seed = (lfsr->seed >> 1) | (xor_result << 31);

    // Return the new value of the seed
    return lfsr->seed;

}

uint32_t lfsr_next_n(lfsr_t *lfsr, uint32_t n)
{
    int val;
    for (uint32_t i = 0; i <= n; i++)
    {
        val = lfsr_next(lfsr);
    }

    return 0;
}
