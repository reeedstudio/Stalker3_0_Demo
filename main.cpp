/*
  main.cpp, iot_mbed demo 
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-7-21

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "IOT_Mbed.h"
#include "mbed.h"
#include "IOT_MbedDfs.h"
#include "Stalker3_0_hw.h"
#include "i2c_uart.h"

Serial serial1(P0_19, P0_18);        // tx, rx
Timer tcnt;

AnalogIn light_sensor(GROVE_ADC_1);

char dtaUart[100];
char dtaUartLen = 0;

char dtaUart1[100];
char dtaUartLen1 = 0;


#define HTTP_POST_URL "http://api.yeelink.net/v1.0/device/4190/sensor/6074/datapoints"
#define YEELINK_APIKEY "38645582d54121679dee8104f140c29a"

void delay(int ms)
{
    wait_ms(ms);
}

#if 1

int getAnalog()
{
		long sum = 0;
		for(int i=0; i<32; i++)
		{
				sum += light_sensor.read_u16();
		}
		sum = sum >> 5;
		
		sum = sum >> 6;
		
		return sum;
}
void iot_demo()
{
		int dtaVal = 0;
		IOT.init(HTTP_POST_URL, YEELINK_APIKEY);
START:
		DBG("begin to start\r\n");
		iot_hw.EG10_PWROFF();					// eg10 power off
		wait(1);							
		iot_hw.EG10_PWRON();						// eg10 power on
		wait(1);
		if(iot_hw.init()==1)
    {
        iot_hw.EG10StateLed(1);
				DBG("hardware init ok\r\n");
    }
    else
    {
				DBG("hardware init fail\r\n");
				DBG("hardware init again\r\n");
				goto START;
    }
		
		DBG("wait ten second\r\n");
		wait(10);

	//	IOT.init(HTTP_POST_URL, YEELINK_APIKEY);
		while(1)
		{
				if(!IOT.connectTCP())
				{
						DBG("connect to tcp err\r\n");
						goto START;
				}
				
				dtaVal = getAnalog()/10;
				//dtaVal /= 41;
				
				DBG("light sensor value: ");
				char tmp[10];
				sprintf(tmp, "%d\r\n", dtaVal);
				DBG(tmp);
				
				if(!IOT.postDtaToYeelink(HTTP_POST_URL, YEELINK_APIKEY, dtaVal))
				{
						DBG("post data err\r\n");
						goto START;
				}
				else
				{
						DBG("post data ok!\r\n");
				}
        iot_hw.userLed(1, 1);
        wait(.2);
        iot_hw.userLed(1, 0);
        wait(10);
		}
		
		
}

#endif

int main(void) 
{

    serial1.baud(115200);
		iot_demo();
	
	
		DBG("begin to init hardware\r\n");
    if(iot_hw.init()==1)
    {
        iot_hw.EG10StateLed(1);
				DBG("hardware init ok\r\n");
    }
    else
    {
				DBG("hardware init err\r\n");
        while(1);
    }
		
/*		
				while(1)
		{
				serial1.printf("AT\r\n");
				wait(0.01);
				while(serial1.readable())               // display the other thing..
				{
						char c = serial1.getc();
						DBG(c);
				}
				
				wait(1);
				
								while(serial1.readable())               // display the other thing..
				{
						char c = serial1.getc();
						DBG(c);
				}
		}
		*/
		
    //test_rtc();
    wait(5); 
    IOT.init(HTTP_POST_URL, YEELINK_APIKEY);
    
    int dtaVal = 0;
    
    while(1)
    {
        IOT.connectTCP();
        IOT.postDtaToYeelink(HTTP_POST_URL, YEELINK_APIKEY, dtaVal++);
        iot_hw.userLed(1, 1);
        wait(.2);
        iot_hw.userLed(1, 0);
        wait(10);
    };

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
