/*
 * SmartPointer001.cpp
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
#include "tests/SmartPointer001.h"
#include "util/Class.h"

std::string SmartPointer001::getDescription() const
{
    std::stringstream strm;
    strm << "elw::SmartPtr() functionality test.";
    return strm.str();
}

bool SmartPointer001::run()
{
    elw::SmartPtr<TestClass> ptr = new TestClass(666);
    elw::SmartPtr<ITestBase> ptrBase = ptr.cast<ITestBase>();

    if (ptr.count() != 2)
        return false;
    if (ptrBase.count() != 2)
        return false;
    ptr = NULL;
    if (ptrBase.count() != 1)
        return false;
    ptr = ptrBase.cast<TestClass>();
    if (ptr.count() != 2)
        return false;
    if (ptrBase.count() != 2)
        return false;
    ptrBase = NULL;
    if (ptr.count() != 1)
        return false;

    {
        elw::SmartPtr<TestClass> ptr0 = ptr;
        if (ptr.count() != 2)
            return false;
        {
            elw::SmartPtr<TestClass> ptr1 = ptr0;
            if (ptr.count() != 3)
                return false;
            {
                elw::SmartPtr<TestClass> ptr2 = ptr1;
                if (ptr.count() != 4)
                    return false;
                {
                    elw::SmartPtr<TestClass> ptr3 = ptr2;
                    if (ptr.count() != 5)
                        return false;
                    {
                        elw::SmartPtr<TestClass> ptr4 = ptr3;
                        if (ptr.count() != 6)
                            return false;

                        if (ptr.count() != ptr0.count())
                            return false;
                        if (ptr.count() != ptr1.count())
                            return false;
                        if (ptr.count() != ptr2.count())
                            return false;
                        if (ptr.count() != ptr3.count())
                            return false;
                        if (ptr.count() != ptr4.count())
                            return false;

                        if (ptr != ptr0)
                            return false;
                        if (ptr != ptr1)
                            return false;
                        if (ptr != ptr2)
                            return false;
                        if (ptr != ptr3)
                            return false;
                        if (ptr != ptr4)
                            return false;


                        ptr2 = NULL;
//                        if (ptr2 != NULL)
//                            return false;
//                        if (ptr2.count() != 1)
//                            return false;
//                        bool fCatch = false;
//                        try
//                        {
//                            ptr2->m_i;
//                        }
//                        catch (const elw::NullPointerException& e)
//                        {
//                            fCatch = true;
//                        }
//
//                        if (!fCatch)
//                            return false;
//
//                        fCatch = false;
//                        try
//                        {
//                            (*ptr2).m_i;
//                        }
//                        catch (const elw::NullPointerException& e)
//                        {
//                            fCatch = true;
//                        }
//
//                        if (!fCatch)
//                            return false;

                        if (ptr.count() != 5)
                            return false;

                        if (ptr.count() != ptr0.count())
                            return false;
                        if (ptr.count() != ptr1.count())
                            return false;
                        if (ptr.count() != ptr3.count())
                            return false;
                        if (ptr.count() != ptr4.count())
                            return false;
                    }
                }
            }
        }
    }

    if (ptr.count() != 1)
        return false;

    {
        elw::SmartPtr<TestClass>& rPtr = ptr;
        if (ptr.count() != 1 && rPtr.count() != 1)
            return 0;
    }

    if (ptr.count() != 1)
        return false;

    std::list<elw::SmartPtr<TestClass> > lst;
    for (int i = 0; i < 1000; ++i)
        lst.push_back(ptr);

    if (ptr.count() != 1001)
        return false;
    if (lst.front().count() != 1001)
        return false;

    lst.erase(lst.begin());

    if (ptr.count() != 1000)
        return false;
    if (lst.front().count() != 1000)
        return false;

    ptr = NULL;

    if (ptr.count() != 1)
        return false;
    if (lst.front().count() != 999)
        return false;

    elw::SmartPtr<TestClass> ptrFront = *(lst.begin());
    if (ptrFront.count() != 1000)
        return false;
    if (lst.front().count() != 1000)
        return false;

    lst.clear();

    if (ptrFront.count() != 1)
        return false;

    if (ptrFront->m_i != 666)
        return false;

    std::map<int, elw::SmartPtr<TestClass> > map;
    for (int i = 0; i < 1000; ++i)
        map[i] = ptrFront;

    ptrFront = NULL;
    {
        elw::SmartPtr<TestClass> ptr5 = map[5];
        if (ptr5.count() != 1001)
            return false;
        map.erase(300);
        if (ptr5.count() != 1000)
            return false;
        map.clear();

        if (ptr5.count() != 1)
            return false;
    }

    return true;
}
