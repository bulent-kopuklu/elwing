/*
 * AtomicInteger001.cpp
 *
 *  Created on: Oct 21, 2011
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

#include "stdafx.h"
#include "tests/AtomicInteger001.h"

std::string AtomicInteger001::getDescription() const
{
    return "elw::AtomicInteger001 test.";
}

bool AtomicInteger001::run()
{
    elw::AtomicInteger i(10);
    int iVal = (int) i;
    if (i != 10)
        return false;
    if (i != iVal)
        return false;
    iVal = i + 100;
    if (iVal != 110)
        return false;
    iVal = i - 100;
    if (iVal != 10)
        return false;
    iVal = i = 5;
    if (iVal != 5)
        return false;
    if (i != 5)
        return false;

    return true;
}
