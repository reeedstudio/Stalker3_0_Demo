/*
  IOT_hw_dfs.h
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

#ifndef __STALKER3_0_HW_DFS_H__
#define __STALKER3_0_HW_DFS_H__

// pin define
#define PINPWR          P1_2            // power on EG 10, low enable
#define PINONOFF        P1_7            // switch of EG10, low enable, low for 2s to turn on EG10
#define PINTX           P0_18           // EG10 TX
#define PINRX           P0_19           // EG10 RX
#define PINSYSRST       P1_6            // EG10 RST，high enable
#define PINEGSTATE      P1_15           // in and out, read eg10 state, HIGH: on, LOW: off


// grove pin
#define GROVE_I2C_SCL   P0_4            // grove i2c pin
#define GROVE_I2C_SDA   P0_5            // grove i2c sda

#define GROVE_UART_RX   P0_14           // grove uart rx
#define GROVE_UART_TX   P0_13           // grove uart tx

#define GROVE_ADC_1     P0_12           // grove ADC, the outside one
#define GROVE_ADC_2     P0_11           // grove ADC, the other one

#define GROVE_PWR       P1_3            // control all grove power, low enable

// charge circuit
#define PIN_CHRGING     P1_1            // charging, low enable
#define PIN_CHRGDONE    P1_0            // charge done
#define PIN_READBAT     P0_23           // battery voltage in, the value should x2

// led pin
#define PINLED1         P1_8
#define PINLED2         P1_9
#define PINLED3         P1_10
#define PINLED4         P1_11

// charge state
#define CHRGING         1
#define CHRGDONE        2
#define NOCHRG          3

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
