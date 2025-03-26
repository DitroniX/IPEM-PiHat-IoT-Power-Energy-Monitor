#ifndef _SPI_H_
#define _SPI_H_

	int spi_init(void);
	int spi_close(void);

	int spi_write(char* buf, unsigned count);
	int spi_txrx(char* txBuf, char* rxBuf, unsigned count);
	int spi_read(char* buf, unsigned count);

#endif