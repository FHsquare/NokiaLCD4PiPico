#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

void reg_write( spi_inst_t *spi, 
                const uint cs, 
                const uint8_t *data, 
                const uint8_t len) {

    // Write to register
    gpio_put(cs, 0);
    spi_write_blocking(spi, data, len);
    gpio_put(cs, 1);
}

void clear( spi_inst_t *spi, 
                const uint cs, 
                const uint8_t *data, 
                const uint8_t len) {

    // Write to register
    gpio_put(cs, 0);
	for(int i=0;i<504;i++)
		spi_write_blocking(spi, data, len);
    gpio_put(cs, 1);
}
int main()
{
	const uint cs_pin = 5; 
    const uint sck_pin = 2;
    const uint mosi_pin = 3;
    const uint miso_pin = 16;
	const uint cmd_pin = 12;
	const uint rst_pin = 11;

    // Buffer to store raw reads
    uint8_t data[6];
    uint8_t cmd1[]={0x21,0xB8,0x04,0x14,0x20,0x0C};
	uint8_t cmd2[]={0x20,0x80,0x40};
	uint8_t cmd3[]={0x45,0x80};
    uint8_t clear1[]={0x00};
	uint8_t data1[]={0x1F,0x05,0x07};
    // Ports
    spi_inst_t *spi = spi0;

    // Initialize chosen serial port
    stdio_init_all();

    // Initialize CS pin high
    gpio_init(cs_pin);
    gpio_set_dir(cs_pin, GPIO_OUT);
	gpio_init(cmd_pin);
    gpio_set_dir(cmd_pin, GPIO_OUT);
	gpio_init(rst_pin);
    gpio_set_dir(rst_pin, GPIO_OUT);
    gpio_put(cs_pin, 1);

	gpio_put(rst_pin, 0);
    // Initialize SPI port at 1 MHz
    spi_init(spi, 1000 * 1000);
	
    // Set SPI format
    spi_set_format( spi0,   // SPI instance
                    8,      // Number of bits per transfer
                    1,      // Polarity (CPOL)
                    1,      // Phase (CPHA)
                    SPI_MSB_FIRST);

    // Initialize SPI pins
    gpio_set_function(sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin, GPIO_FUNC_SPI);
    gpio_set_function(miso_pin, GPIO_FUNC_SPI);
	gpio_put(rst_pin, 1);
	
	gpio_put(cmd_pin, 0);
	reg_write(spi,cs_pin, cmd1, 6);
	
	gpio_put(cmd_pin, 0);
	reg_write(spi,cs_pin, cmd2, 3);
	
	gpio_put(cmd_pin, 1);
	clear(spi,cs_pin,clear1,1);
	
	gpio_put(cmd_pin, 1);
    reg_write(spi,cs_pin, data1, 3);		
	
	gpio_put(cmd_pin, 0);
	reg_write(spi,cs_pin, cmd3, 2);
	
	gpio_put(cmd_pin, 1);
    reg_write(spi,cs_pin, data1, 3);		
	
	
}
