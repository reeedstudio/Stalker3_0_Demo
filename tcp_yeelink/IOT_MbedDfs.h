/*
  IOT_MbedDfs.h
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

#ifndef __IOT_MBEDDFS_H__
#define __IOT_MBEDDFS_H__

#define HTTP_DEFAULT_PORT                   80

#define HTTP_MAX_HOST_LEN                   20
#define HTTP_MAX_PATH_LEN                   64
#define HTTP_MAX_BUF_LEN                    100

// some useful AT command
#define STRCSQ          "AT+CSQ"
#define STROPENGPRS     "AT+CGATT=1"
#define STRSETGPRS      "AT+CGDCONT=1,\"IP\",\"CMNET\""
#define STRSETAPN       "AT+CSTT=\"CMNET\",\"\",\"\""
#define STRSETMODE      "AT+CIPMODE=0"
#define STRSTARTTCP     "AT+CIPSTART=\"TCP\",\"42.96.164.52\",\"80\""
#define STRCLOSE        "AT+CIPCLOSE"
#define STRECHOFF				"ATE0"

// err code
#define ERRTOUT			 0 
//#define NOK          0
#define OK				   1


// post data
#define POST1  "POST /v1.0/device/3091/sensor/4346/datapoints HTTP/1.1"
#define POST2  "Host: api.yeelink.net"
#define POST3  "Connection: close"
#define POST4  "Content-Length: 15"
#define POST5  "Content-Type: text/plain"
#define POST6  "U-ApiKey: 9270322fd7c7683cb9ad198f3464cf0d"

#define POST7  "{\"value\": 100}"

#define CONTENT_TYPE    " application/x-www-form-urlencoded"



#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
