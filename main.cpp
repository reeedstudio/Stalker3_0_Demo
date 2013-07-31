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


Serial serial1(P0_19, P0_18);        // tx, rx
Timer tcnt;

char dtaUart[100];
char dtaUartLen = 0;

char dtaUart1[100];
char dtaUartLen1 = 0;

#define HTTP_POST_URL "http://api.yeelink.net/v1.0/device/3091/sensor/4346/datapoints"
#define YEELINK_APIKEY "9270322fd7c7683cb9ad198f3464cf0d"

void delay(int ms)
{
    wait_ms(ms);
}

int main(void) 
{

    serial1.baud(115200);
    if(iot_hw.init()==1)
    {
        iot_hw.EG10StateLed(1);
    }
    else
    {
        while(1);
    }
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
