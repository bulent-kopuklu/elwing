/*
 * elwstd.h
 *
 *  Created on: Sep 29, 2011
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

#ifndef elwstd_h__
#define elwstd_h__

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include <exception>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <list>
#include <deque>
#include <queue>
#include <vector>
#include <map>
#include <typeinfo>
#include <limits>

#define BEGIN_ELW   namespace elw {
#define END_ELW     }

#define MKSTR(argv) \
    (((std::ostringstream &)( \
            std::ostringstream().seekp(0, std::ios_base::cur) << argv)\
            ).str())

#define TYPE2STR(__t)    (#__t)

#define DISABLE_COPY(cls) \
    cls(const cls& that); \
    cls& operator=(const cls& that);

#endif /* elwstd_h__ */
