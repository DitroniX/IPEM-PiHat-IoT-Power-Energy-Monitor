#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "spi.h"
#include "atm30e36a.h"
#include "main.h"

int main(int argc, char* argv[]) {
	
	if (spi_init() > 0) {
		printf("SPI Init failed");
		return 0;
	}

	atm30e36a_init();
	atm30e36a_chipinit();

	for (int i = 0; i < 100; i++) {
		
		for (int j = 0; j < CT_MAX - 1; j++) {
			struct CT_Value_Result* output = GetCTRead(j);
			printf("CT %d VOLT:%.02lf FREQ:%.02lf AP:%.02lf CURR:%.02lf AP:%.02lf PH:%.02lf PF:%.02lf RA:%.02lf\r\n", j + 1, output->Voltage, output->Frequency, output->ActivePower, output->Current, output->Apprent, output->Phase, output->PowerFactor, output->Reactive);
			free(output);
		}
		sleep(1);
	}
	spi_close();
	
	printf("Finished");
}
