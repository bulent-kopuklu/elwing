/*
 * elwtypes.h
 *
 *  Created on: Sep 27, 2010
 *      Author: Bulent.Kopuklu
 *
 *  Copyright (C) 2010 by Bulent Kopuklu (bulent.kopuklu@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef elwtypes_h__
#define elwtypes_h__

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned short      word;
typedef unsigned int        uint;

typedef unsigned long       ulong;
typedef unsigned long       dword;

typedef char                int8;
typedef short               int16;
typedef int                 int32;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;

typedef uint32              ptr32;

typedef char*               pstr;
typedef const char*         pcstr;

#define MAX_CHAR            (0x7f)
#define MAX_SHORT           (0x7fff)
#define MAX_INT             (0x7fffffff)
#define MAX_LONG            (0x7fffffff)

#define MAX_BYTE            (0xff)
#define MAX_UCHAR           (0xff)
#define MAX_USHORT          (0xffff)
#define MAX_UINT            (0xffffffff)
#define MAX_ULONG           (0xffffffff)

#define MAX_INT8            MAX_CHAR
#define MAX_INT16           MAX_SHORT
#define MAX_INT32           MAX_INT
#define MAX_INT64           (0x7fffffffffffffff)

#define MAX_UINT8           MAX_UCHAR
#define MAX_UINT16          MAX_USHORT
#define MAX_UINT32          MAX_UINT
#define MAX_UINT64          (0xffffffffffffffff)

#ifndef NULL
#define NULL                ((void*)0)
#endif

#endif // elwtypes_h__
