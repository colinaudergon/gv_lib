#include "pico/stdlib.h"
#include "logger.h"

#include "gv_lfsr.h"

lfsr_t lfsr;

void print_bits(uint32_t value)
{
    for (int i = 31; i >= 0; i--) // Iterate from the most significant bit (MSB) to the least significant bit (LSB)
    {
        printf("%d ", (value >> i) & 1); // Extract and print each bit
    }
    printf("\n"); // Add a newline at the end
}

int main(void)
{
    stdio_init_all();

    sleep_ms(1000);

    int err = lfsr_init(&lfsr, 0x00000075, 0x00000029);
    if(err < 0)
    {
        LOG_ERROR("Failed to init lfsr");
        return 1;
    }
    uint32_t res = lfsr_next(&lfsr);
    print_bits(res);
    res = lfsr_next(&lfsr);
    print_bits(res);

    while (1)
    {
        sleep_ms(1000);
    }
    return 0;
}
