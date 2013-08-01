/*
  IOT_Mbed.h
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

#ifndef __IOT_MBED_H__
#define __IOT_MBED_H__

#include "mbed.h"

class IOT_Mbed{

private:

    //Serial serial1(P0_19, P0_18);        // tx, rx
private:
    char yeelinkPostURL[100];
    char yeelinkPostHeads[100];
    
    char yeelinkDns[20];
    char yeelinkPort[10];
    
private:
	
		void callTest();
    
    int sendCmdAndWaitForRest(char *dta, const char *resq, int timeout);
    void sendCmd(char *dta);
    int parseURL(const char *url, char *host, int max_host_len, unsigned int *port, char *path, int max_path_len);

public:
		int waitString(const char *str, int timeout);
    void init(char *postURL, char *APIKey);
    int checkAT(int timeout);
    int connectTCP();
    int connectTCP(char *ip, char *port);
    void postDtaToYeelink();
    int postDtaToYeelink(char *url, char *apikey, int sensorDta);
    
    int sendDtaTcp(char *dta, int timeout);
    bool sendToYeelink_t();

};


extern IOT_Mbed IOT;


#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
