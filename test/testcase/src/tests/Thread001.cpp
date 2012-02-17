/*
 * Thread001.cpp
 *
 *  Created on: Oct 5, 2011
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
#include "tests/Thread001.h"

#define S0 119

std::string Thread001::getDescription() const
{
    std::stringstream strm;
    strm << "elw::Thread001() test. " << " start thread, join thread. thread func will wait " << S0 << " ms.";
    return strm.str();

}

bool Thread001::run()
{
    class TThread001 :
        public elw::Thread
    {
    public:
        int run()
        {
            elw::Thread::sleep(S0);
            return 0;
        }
    };

    dword dw0 = elw::Thread::tick();
    TThread001 t;
    t.start();
    t.join();
    dword dw1 = elw::Thread::tick();
    if ((dw1 - dw0) < S0)
        return false;
    return true;
}
