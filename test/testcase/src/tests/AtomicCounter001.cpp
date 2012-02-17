/*
 * AtomicCounter001.cpp
 *
 *  Created on: Oct 20, 2011
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
#include "tests/AtomicCounter001.h"

#define TRYCNT 50000

std::string AtomicCounter001::getDescription() const
{
    std::stringstream strm;
    strm << "elw::AtomicCounter() test. 4 threads (++, --) try cnt:" << TRYCNT*2;
    return strm.str();
}

bool AtomicCounter001::run()
{
    elw::AtomicCounter nCnt;
    class ThreadInc :
        public elw::Thread
    {
        elw::AtomicCounter& m_nCnt;
    public:
        ThreadInc(elw::AtomicCounter& nCnt) :
            m_nCnt(nCnt)
        {

        }

        int run()
        {
            for (int i = 0; i < TRYCNT; ++i)
                ++m_nCnt;
            for (int i = 0; i < TRYCNT; ++i)
                m_nCnt++;

            return 0;
        }
    } t0(nCnt), t1(nCnt);

    class ThreadDec :
        public elw::Thread
    {
        elw::AtomicCounter& m_nCnt;
    public:
        ThreadDec(elw::AtomicCounter& nCnt) :
            m_nCnt(nCnt)
        {

        }

        int run()
        {
            for (int i = 0; i < TRYCNT; ++i)
                --m_nCnt;
            for (int i = 0; i < TRYCNT; ++i)
                m_nCnt--;
            return 0;
        }
    } t2(nCnt), t3(nCnt);

    t0.start();
    t2.start();
    t1.start();
    t3.start();

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    if (nCnt != 0)
        return false;

    return true;
}
