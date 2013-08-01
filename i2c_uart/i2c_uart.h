#ifndef __I2C_UART_H__
#define __I2C_UART_H__

#define __Debug            1

#if __Debug
#define DBG(X)    debug_i2c(X)
#else
#define DBG(X)
#endif


void debug_i2c(char *dta);


void debug_i2c(char dta);
#endif
