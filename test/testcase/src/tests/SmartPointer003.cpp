/*
 * SmartPointer003.cpp
 *
 *  Created on: Oct 7, 2011
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
#include "tests/SmartPointer003.h"
#include "util/Class.h"


std::string SmartPointer003::getDescription() const
{
    return "elw::SmartPtr() access stress test. 4 threads";
}

bool SmartPointer003::run()
{
    class MapClass
    {
        elw::SpinLock m_lock;
        std::map<int, elw::SmartPtr<ITestBase> > m_map;
        std::list<TestClass*> m_lst;
    public:
        MapClass()
        {
        }

        elw::SmartPtr<ITestBase> find(int i)
        {
            elw::ScopeGuard g(m_lock);
            std::map<int, elw::SmartPtr<ITestBase> >::iterator it = m_map.find(i);
            if (it == m_map.end())
                return NULL;
            return (*it).second;
        }

        void erase(int i)
        {
            elw::ScopeGuard g(m_lock);
            m_map.erase(i);
        }

        void fill()
        {
            for (int i = 0; i <= 10; ++i)
            {
                m_map[i] = new TestClass(i);
            }
        }

        int size()
        {
            return m_map.size();
        }
    } map;

    class Accessor : public elw::IRunnable
    {
        MapClass& m_rMap;
        bool m_fFailed;
    public:
        virtual int run()
        {
            while (m_rMap.size() != 0)
            {
                for (int i = 0; i <= 10; ++i)
                {
                    elw::SmartPtr<ITestBase> ptr = m_rMap.find(i);
                    if (ptr != NULL)
                    {
//                        try
//                        {
                            elw::Thread::sleep(5);
                            ptr->toString();
                            elw::Thread::yield();
                            ptr->getId();
//                        }
//                        catch (const elw::NullPointerException& e)
//                        {
//                            m_fFailed = true;
//                        }
                    }
                }
            }

            return 0;
        }

        bool isFailed()
        {
            return m_fFailed;
        }

        Accessor(MapClass& rMap) :
            m_rMap(rMap),
            m_fFailed(false)
        {
        }
    } a0(map), a1(map);

    class Remover :
        public elw::IRunnable
    {
        MapClass& m_rMap;
    public:
        virtual int run()
        {
            while (m_rMap.size() != 0)
            {
                for (int i = 0; i <= 10; ++i)
                {
                    elw::SmartPtr<ITestBase> ptr = m_rMap.find(i);
                    if (ptr != NULL && ptr.count() > 2)
                    {
                        m_rMap.erase(i);
                    }
                }
            }

            return 0;
        }

        Remover(MapClass& rMap) :
            m_rMap(rMap)
        {
        }
    } r0(map);

    elw::Thread t0(&r0), t2(&a0), t3(&a1);
    for (int i = 0; i < 20; ++i)
    {
        map.fill();

        t0.start(), t2.start(), t3.start();
        t0.join(), t2.join(), t3.join();

        if (a0.isFailed())
            return false;
        if (a1.isFailed())
            return false;
    }

    return true;
}
