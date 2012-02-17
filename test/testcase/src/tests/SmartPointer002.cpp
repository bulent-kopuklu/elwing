/*
 * SmartPointer002.cpp
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
#include "tests/SmartPointer002.h"
#include "util/Class.h"

std::string SmartPointer002::getDescription() const
{
    std::stringstream strm;
    strm << "elw::SmartPtr() refcount stress test. 4 threads";
    return strm.str();
}

bool SmartPointer002::run()
{
    elw::SmartPtr<TestClass> ptr(new TestClass(666));

    {
        class RefCount : public elw::IRunnable
        {
            elw::SmartPtr<ITestBase> m_ptr;
            std::list<elw::SmartPtr<TestClass> > m_lst;
        public:
            RefCount(elw::SmartPtr<ITestBase> ptr) :
                m_ptr(ptr)
            {
            }

            int run()
            {
                for (int i = 0; i < 5; ++i)
                {
                    for (int l = 0; l < 10000; ++l)
                    {
                        m_lst.push_back(m_ptr.cast<TestClass>());
                    }

                    m_lst.clear();
                }

                return 0;
            }
        } r0(ptr.cast<ITestBase>()), r1(ptr.cast<ITestBase>()), r2(ptr.cast<ITestBase>()), r3(ptr.cast<ITestBase>());

        elw::Thread t0(&r0);
        elw::Thread t1(&r1);
        elw::Thread t2(&r2);
        elw::Thread t3(&r3);
        t0.start(), t1.start(), t2.start(), t3.start();
        t0.join(), t1.join(), t2.join(), t3.join();
    }

    if (ptr.count() != 1)
        return false;

    return true;
}
