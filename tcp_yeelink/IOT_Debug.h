/*
  IOT_Debug.h
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

#ifndef __IOT_DEBUG_H__
#define __IOT_DEBUG_H__

#define DEBUG       1

#if DEBUG
#define DBG(message)    serial1.printf(message)
#else
#define DBG(message)
#endif // DEBUG

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
