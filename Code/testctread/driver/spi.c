#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <gpiod.h>

#include "spi.h"

#define SPISPEED 200000
#define SPI_DEVICE          "/dev/spidev0.0"

static struct {
	uint32_t scratch32;
	int fd;
}SPI_STATE;


int spi_init(void) {
	int ret = 0;
	
	SPI_STATE.fd = open(SPI_DEVICE, O_RDWR);
	if (SPI_STATE.fd < 0) {
		printf("Could not open the SPI device...\r\n");
		exit(EXIT_FAILURE);
	}

	ret = ioctl(SPI_STATE.fd, SPI_IOC_RD_MODE32, &SPI_STATE.scratch32);
	if (ret != 0) {
		printf("Could not read SPI mode...\r\n");
		close(SPI_STATE.fd);
		exit(EXIT_FAILURE);
	}

	SPI_STATE.scratch32 |= SPI_MODE_3;

	ret = ioctl(SPI_STATE.fd, SPI_IOC_WR_MODE32, &SPI_STATE.scratch32);
	if (ret != 0) {
		printf("Could not write SPI mode...\r\n");
		close(SPI_STATE.fd);
		exit(EXIT_FAILURE);
	}

	ret = ioctl(SPI_STATE.fd, SPI_IOC_RD_MAX_SPEED_HZ, &SPI_STATE.scratch32);
	if (ret != 0) {
		printf("Could not read the SPI max speed...\r\n");
		close(SPI_STATE.fd);
		exit(EXIT_FAILURE);
	}

	SPI_STATE.scratch32 = 5000000;

	ret = ioctl(SPI_STATE.fd, SPI_IOC_WR_MAX_SPEED_HZ, &SPI_STATE.scratch32);
	if (ret != 0) {
		printf("Could not write the SPI max speed...\r\n");
		close(SPI_STATE.fd);
		exit(EXIT_FAILURE);
	}

	
	return 0;
}

int spi_write(char* buf, unsigned count)
{
	int err;
	struct spi_ioc_transfer spi;

	memset(&spi, 0, sizeof(spi));

	spi.tx_buf = (unsigned long)buf;
	spi.rx_buf = (unsigned)NULL;
	spi.len = count;
	spi.speed_hz = SPISPEED;
	spi.delay_usecs = 10;
	spi.bits_per_word = 0;
	spi.cs_change = 0;

	err = ioctl(SPI_STATE.fd, SPI_IOC_MESSAGE(1), &spi);

	return err;
}

int spi_txrx(char* txBuf, char* rxBuf, unsigned count)
{
	int err;
	struct spi_ioc_transfer spi;

	memset(&spi, 0, sizeof(spi));

	spi.tx_buf = (unsigned long)txBuf;
	spi.rx_buf = (unsigned long)rxBuf;
	spi.len = count;
	spi.speed_hz = SPISPEED;
	spi.delay_usecs = 10;
	spi.bits_per_word = 0;
	//spi.cs_change = 0;
	err = ioctl(SPI_STATE.fd, SPI_IOC_MESSAGE(1), &spi);
	if (err != 0) {
		//printf("SPI transfer returned %d...\r\n", err);
	}
	
	return err;
}


int spi_read(char* buf, unsigned count)
{
	int err;
	struct spi_ioc_transfer spi;

	memset(&spi, 0, sizeof(spi));

	spi.tx_buf = (unsigned)NULL;
	spi.rx_buf = (unsigned long)buf;
	spi.len = count;
	spi.speed_hz = SPISPEED;
	spi.delay_usecs = 10;
	spi.bits_per_word = 8;
	spi.cs_change = 0;

	err = ioctl(SPI_STATE.fd, SPI_IOC_MESSAGE(1), &spi);

	return err;
}

int spi_close(void) {
	close(SPI_STATE.fd);
}