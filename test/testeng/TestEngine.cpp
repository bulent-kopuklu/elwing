/*
 * TestEngine.cpp
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
#include "TestEngine.h"

void TestEngine::start()
{
    Testcases::load();

    dword dwStart = elw::Thread::tick();
    int iStart = 1;
    int iEnd = 0;
    int iTotal = 0;
    int iFailed = 0;
    for ( ; ; )
    {
        char sz[64];
        sprintf(sz, "Test%03d", iStart);
        ITest* pTest = elw::ClassFactory::instantiate<ITest>(sz);
        if (pTest == NULL)
            break;

        std::cout << "Starting " << sz << " " << pTest->getDescription() << std::endl;
        dword dwBegin = elw::Thread::tick();
        bool fRslt = pTest->run();
        std::cout << "\t" << (fRslt ? "done" : "failed") << ". completion time:" << elw::Thread::tick() - dwBegin << "ms." << std::endl;
        if (false == fRslt)
            ++iFailed;
        std::cout << std::endl;

        delete pTest;

        ++iStart;
        ++iTotal;

        if (iEnd != 0 && iTotal == iEnd)
            break;

    }

    std::cout << std::endl << std::endl << "completed ... " << elw::Thread::tick() - dwStart << " ms. "<< std::endl;
    std::cout << "\ttotal test  :" << iTotal << std::endl;
    std::cout << "\tsuccess test:" << iTotal - iFailed << std::endl;
    std::cout << "\tfail test   :" << iFailed << std::endl;
}
