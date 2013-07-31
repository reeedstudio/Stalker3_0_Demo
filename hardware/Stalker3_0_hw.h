/*
  IOT_hw.h
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

#ifndef __STALKER3_0_HW_H__
#define __STALKER3_0_HW_H__

#include "Stalker3_0_hw_dfs.h"


class IOT_HW{

private:

public:
    int init();                                     // init all
    void init_io();                                 // init io
    void EG10_PWRON();                              // power on eg10
    void EG10_PWROFF();                             // power off eg10, cut the power
    void EG10_ON();                                 // turn on eg10
    void EG10_OFF();                                // turn off eg10
    int getEG10_State();                            // get state of eg10
    void EG10StateLed(unsigned char state);         // control led

		int readChrgState();
    float readBatVol();
    void userLed(unsigned char led, unsigned char state);
    void grovePwrOn();
    void grovePwrOff();
};

extern IOT_HW iot_hw;

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
