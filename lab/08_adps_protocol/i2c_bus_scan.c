#include <stdio.h>

#include "pico/stdlib.h"
#include "pio_i2c.h"

#define PIN_SDA 2
#define PIN_SCL 3

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main() {
    stdio_init_all();

    int addr = 0x39;

    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, PIN_SDA, PIN_SCL);


    uint8_t buf[2];

    // send register number followed by its corresponding value
    buf[0] = 0x80;
    buf[1] = 0x3;
    pio_i2c_write_blocking(pio, sm, addr, buf, 2, false);

    buf[0] = 0x81;
    buf[1] = 219;
    pio_i2c_write_blocking(pio, sm, addr, buf, 2, false);

    int r, g, b, c;

    sleep_ms(10);

    
 
    //printf("\nPIO I2C Bus Scan\n");
    //printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
    while(1)
    {
        uint8_t buf[2];
        uint8_t reg = 0x94;
        pio_i2c_write_blocking(pio, sm, addr, &reg, 1, true);  // true to keep master control of bus
        pio_i2c_read_blocking(pio, sm, addr, buf, 8);  // false - finished with bus

        c = (buf[1] << 8) | buf[0];
        r = (buf[3] << 8) | buf[2];
        g = (buf[5] << 8) | buf[4];
        b = (buf[7] << 8) | buf[6];

        printf("r:%d, g:%d, b:%d, c:%d\n", r, g, b, c);

        sleep_ms(1000);

    }
    

   /*
   while(!stdio_usb_connected());

    for (int addr = 0; addr < (1 << 7); ++addr) {
        if (addr % 16 == 0) {
            printf("%02x ", addr);
        }
        // Perform a 0-byte read from the probe address. The read function
        // returns a negative result NAK'd any time other than the last data
        // byte. Skip over reserved addresses.
        int result;
        if (reserved_addr(addr))
            result = -1;
        else
            result = pio_i2c_read_blocking(pio, sm, addr, NULL, 0);

        printf(result < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
    }

    */
    
    printf("Done.\n");
    return 0;
}
