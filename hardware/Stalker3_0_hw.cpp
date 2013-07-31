/*
  IOT_hw.cpp
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

#include "mbed.h"
#include "IOT_Mbed.h" 
#include "IOT_MbedDfs.h"
#include "Stalker3_0_hw.h"
#include "Stalker3_0_hw_dfs.h"

DigitalOut eg10_pwr(PINPWR);
DigitalOut eg10_on(PINONOFF);
DigitalInOut eg10_state(PINEGSTATE);
DigitalOut eg10_rst(PINSYSRST);

DigitalOut led1(PINLED1);
DigitalOut led2(PINLED2);
DigitalOut led3(PINLED3);
DigitalOut led4(PINLED4);

DigitalOut grove_pwr(GROVE_PWR);
DigitalIn  charging(PIN_CHRGING);
DigitalIn  chargdone(PIN_CHRGDONE);

AnalogIn vol_bat(PIN_READBAT);

void IOT_HW::EG10_PWRON()
{
    eg10_pwr = 0;
}

void IOT_HW::EG10_PWROFF()
{
    eg10_pwr = 1;
}

void IOT_HW::EG10_ON()
{
    eg10_on = 0;
    wait(2);
    eg10_on = 1;
}

int IOT_HW::init()
{
    init_io();
    EG10_PWROFF();
    wait(2);                // wait 2s
    EG10_PWRON();
    EG10_PWRON();
    EG10_ON();
    return (IOT.waitString("M2MRSSI", 30));
}

void IOT_HW::init_io()
{
    eg10_pwr = 1;
    eg10_on  = 1;
}

int IOT_HW::getEG10_State()
{
    eg10_state.input();
    eg10_state.mode(PullDown);
    if(eg10_state.read())
    {
        return 1;
    }
    return 0;
}
 
void IOT_HW::EG10StateLed(unsigned char state)
{
    eg10_state.output();
    eg10_state = 1-state;
}

void IOT_HW::userLed(unsigned char led, unsigned char state)
{
//    if(state!=0 || state!=1)return;

    if(1==led)led1 = state;
    else if(2==led)led2 = state;
    else if(3==led)led3 = state;
    else if(4==led)led4 = state;

}

int IOT_HW::readChrgState()
{
    if(!charging.read())return CHRGDONE;
    if(!chargdone.read())return CHRGING;
    return NOCHRG;
}

float IOT_HW::readBatVol()
{
    unsigned int tmp = vol_bat.read_u16();
    float dr = tmp;
    dr = dr/65536.0*3.3*2.0;
    return dr;
   // return ((float tmp)/65536.0*3.3*2.0);
}

void IOT_HW::grovePwrOn()
{
    grove_pwr = 0;
}

void IOT_HW::grovePwrOff()
{
    grove_pwr = 1;
}


IOT_HW iot_hw;
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
