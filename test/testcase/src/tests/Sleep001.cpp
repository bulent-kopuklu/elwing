/*
 * Sleep001.cpp
 *
 *  Created on: Oct 4, 2011
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
#include "tests/Sleep001.h"

#define S0 2
#define S1 5
#define S2 13
#define S3 80
#define S4 1000
#define S5 2900

std::string Sleep001::getDescription() const
{
    std::stringstream strm;
    strm << "elw::Thread::sleep() test. " << " waiting " << S0 << " ms. " << S1 << " ms. " << S2 << " ms. " << S3 << " ms." << S4 << " ms. " << S5 << " ms.";
    return strm.str();
}

bool Sleep001::run()
{
    dword dwTotal = 0;

    dword dw0 = elw::Thread::tick();
    elw::Thread::sleep(S0);
    dword dw1 = elw::Thread::tick();
    if ((dw1 - dw0) < S0)
        return false;
    dwTotal += dw1-dw0;

    dw0 = elw::Thread::tick();
    elw::Thread::sleep(S1);
    dw1 = elw::Thread::tick();
    if ((dw1 - dw0) < S1)
        return false;
    dwTotal += dw1-dw0;

    dw0 = elw::Thread::tick();
    elw::Thread::sleep(S2);
    dw1 = elw::Thread::tick();
    if ((dw1 - dw0) < S2)
        return false;
    dwTotal += dw1-dw0;

    dw0 = elw::Thread::tick();
    elw::Thread::sleep(S3);
    dw1 = elw::Thread::tick();
    if ((dw1 - dw0) < S3)
        return false;
    dwTotal += dw1-dw0;

    dw0 = elw::Thread::tick();
    elw::Thread::sleep(S4);
    dw1 = elw::Thread::tick();
    if ((dw1 - dw0) < S4)
        return false;
    dwTotal += dw1-dw0;

    dw0 = elw::Thread::tick();
    elw::Thread::sleep(S5);
    dw1 = elw::Thread::tick();
    if ((dw1 - dw0) < S5)
        return false;
    dwTotal += dw1-dw0;

    if (dwTotal < (S0 + S1 + S2 + S3 + S4 + S5))
        return false;
    return true;
}
