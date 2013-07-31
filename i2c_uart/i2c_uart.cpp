#include "mbed.h"
#include "i2c_uart.h"
#include "Stalker3_0_hw_dfs.h"

#define ADDRESS		0x20<<1

I2C i2c_debug(GROVE_I2C_SDA, GROVE_I2C_SCL);


void debug_i2c(char *dta)
{
		int len = strlen(dta);
		i2c_debug.write(ADDRESS, dta, len);
		//wait_ms(10);
}

void debug_i2c(char dta)
{
		char dta1[5];
		sprintf(dta1, "%c", dta);
		debug_i2c(dta1);
}
//
