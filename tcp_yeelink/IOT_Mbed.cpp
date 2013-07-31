/*
  IOT_Mbed.cpp
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
#include <stdio.h>

#include "mbed.h"
#include "IOT_Mbed.h"
#include "IOT_MbedDfs.h"
#include "IOT_Debug.h"

extern Serial serial1;        // tx, rx
extern void delay(int ms);
extern Timer tcnt;



void IOT_Mbed::init(char *postURL, char *APIKey)
{
    strcpy(yeelinkPostURL, postURL);
    sprintf(yeelinkPostHeads, "U-ApiKey: %s\r\n", APIKey);
    strcpy(yeelinkDns, "42.96.164.52");                     		// api.yeelink.net
    sprintf(yeelinkPort, "%d", HTTP_DEFAULT_PORT);
}

void IOT_Mbed::callTest()
{
		sendCmdAndWaitForRest("ATD:10086;\r\n", "OK", 10);
}

int IOT_Mbed::checkAT(int timeout)
{
		return sendCmdAndWaitForRest("AT\r\n", "OK", timeout);
}
int IOT_Mbed::waitString(const char *str, int timeout)			    // time out : s
{
    int len = strlen(str);
    int sum=0;

    tcnt.start();                                                   // start timer
    
    for(;;)
    {
        if(serial1.readable())
        {
            char c = serial1.getc();
            sum = (c==str[sum]) ? sum+1 : 0;
            if(sum == len)break;
        }
        
        if(tcnt.read() > timeout)           // time out
        {
            tcnt.stop();
            tcnt.reset();
            return ERRTOUT;
        }
    }
    
    tcnt.stop();                            // stop timer
    tcnt.reset();                           // clear timer
	
    while(serial1.readable())               // display the other thing..
    {
        char c = serial1.getc();
    }

    return (len == sum);
}

int IOT_Mbed::sendCmdAndWaitForRest(char *dta, const char *resq, int timeout)
{
    sendCmd(dta);
    return waitString(resq, timeout);
}

void IOT_Mbed::sendCmd(char *dta)
{
    serial1.printf("%s\r\n", dta);
}

void IOT_Mbed::connectTCP()
{
    //sendCmdAndWaitForRest(STRCSQ, "OK", 10);
    sendCmdAndWaitForRest(STROPENGPRS, "OK", 20);
    sendCmdAndWaitForRest(STRSETGPRS, "OK", 20);
    sendCmdAndWaitForRest(STRSETAPN, "OK", 20);
    
    char cipstart[50];
    sprintf(cipstart, "AT+CIPSTART=\"TCP\",\"%s\",\"%s\"", yeelinkDns, yeelinkPort);
    sendCmdAndWaitForRest(cipstart, "CONNECT OK", 20);              // connect tcp
}

void IOT_Mbed::connectTCP(char *ip, char *port)
{
		while(sendCmdAndWaitForRest(STROPENGPRS, "OK", 20) == ERRTOUT)
		{
				wait(5);
		}

    sendCmdAndWaitForRest(STRSETGPRS, "OK", 20);
    sendCmdAndWaitForRest(STRSETAPN, "OK", 20);
    
    char cipstart[50];
    sprintf(cipstart, "AT+CIPSTART=\"TCP\",\"%s\",\"%s\"", ip, port);
    sendCmdAndWaitForRest(cipstart, "CONNECT OK", 20);              // connect tcp
    
}

//send data to tcp
int IOT_Mbed::sendDtaTcp(char *dta, int timeout)
{
    serial1.printf("AT+CIPSEND=%d\r\n", strlen(dta));
    waitString(">", 10);
    serial1.printf("%s", dta);
    
    delay(50);
    return waitString("SEND OK", timeout);
}

bool IOT_Mbed::sendToYeelink_t()
{
    char dtaSend[300];
    sprintf(dtaSend, "%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n\r\n%s\r\n", POST1, POST2, POST3, POST4, POST5, POST6, POST7);
    return sendDtaTcp(dtaSend, 20);
}

void IOT_Mbed::postDtaToYeelink()
{
    
}

void IOT_Mbed::postDtaToYeelink(char *url, char *apikey, int sensorDta)
{
    char dtaPost[350];
    
    char request[100];
    char heads[200];
    char body[100];
	
    unsigned int port;
    
    
    char host[HTTP_MAX_HOST_LEN];
    char path[HTTP_MAX_PATH_LEN];
  
    if (parseURL(url, host, sizeof(host), &port, path, sizeof(path)) != 0) 
    {
        DBG("Failed to parse URL.\r\n");
        return ;
    }

    sprintf(body, "{\"value\": %d}\r\n", sensorDta);
    sprintf(request, "POST %s HTTP/1.1\r\n", path);
    sprintf(heads, "Host: %s\r\nU-ApiKey: %s\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n",host, apikey, strlen(body), CONTENT_TYPE);
    sprintf(dtaPost, "%s%s%s", request, heads, body);

    sendDtaTcp(dtaPost, 10);
    
    while(serial1.readable())
    {
        char c = serial1.getc();
    }
    
    sendCmdAndWaitForRest(STRCLOSE, "OK", 20);
}

int IOT_Mbed::parseURL(const char *url, char *host, int max_host_len, unsigned int *port, char *path, int max_path_len)
{
    char *scheme_ptr = (char *)url;
    char *host_ptr = (char *)strstr(url, "://");
    if (host_ptr != NULL)
    {
        if (strncmp(scheme_ptr, "http://", 7))
        {
            DBG("Bad scheme\r\n");
            return -1;
        }
        host_ptr += 3;
    }
    else
    {
        host_ptr = (char *)url;
    }

    int host_len = 0;
    char *port_ptr = strchr(host_ptr, ':');

    if (port_ptr != NULL)
    {
        host_len = port_ptr - host_ptr;
        port_ptr++;
        if (sscanf(port_ptr, "%hu", port) != 1)
        {
            DBG("Could not find port.\r\n");
            return -3;
        }
    }
    else
    {
        *port = HTTP_DEFAULT_PORT;
    }

    char *path_ptr = strchr(host_ptr, '/');
    
    if (host_len == 0)
    {
        host_len = path_ptr - host_ptr;
    }

    if (max_host_len < (host_len + 1))
    {
        DBG("Host buffer is too small.\r\n");
        return -4;
    }
    
    memcpy(host, host_ptr, host_len);
    host[host_len] = '\0';

    int path_len;
    
    char *fragment_ptr = strchr(host_ptr, '#');
    if (fragment_ptr != NULL)
    {
        path_len = fragment_ptr - path_ptr;
    }
    else
    {
        path_len = strlen(path_ptr);
    }

    if (max_path_len < (path_len + 1))
    {
        DBG("Path buffer is too small.\r\n");
        return -5;
    }
    memcpy(path, path_ptr, path_len);
    path[path_len] = '\0';

    return 0;
}



IOT_Mbed IOT;
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
