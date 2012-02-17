/*
 * ThreadQueue002.cpp
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
#include "tests/ThreadQueue002.h"
#include "util/Message.h"

std::string ThreadQueue002::getDescription() const
{
    std::stringstream strm;
    strm << "elw::ThreadQueu test." << " create multiple consumer threads and pop from queu. msg cnt:" << MSGCNT;
    return strm.str();
}

bool ThreadQueue002::run()
{
    elw::ThreadQueue<Message*> que;

    class Runnable : public elw::IRunnable
    {
        elw::ThreadQueue<Message*>& m_que;
        dword m_dwSender;
        dword m_dwPopCnt;
    public:
        Runnable(elw::ThreadQueue<Message*>& que, dword dwSender) :
            m_que(que),
            m_dwSender(dwSender),
            m_dwPopCnt(0)
        {
        }

        int run()
        {
//            std::cout << "Starting " << elw::Thread::selfId() << std::endl;
            Message* p = NULL;
            while ((p = m_que.pop()) != NULL)
            {
//                std::cout << elw::Thread::selfId() << " " << p->getSender() << " " << p->getParam() << std::endl;
                if (m_dwSender != p->getSender())
                    return -1;
                ++m_dwPopCnt;
                delete p;
            }

//            std::cout << "Stopping " << elw::Thread::selfId() << " " << getPopCnt() << std::endl;

            return 0;
        }

        dword getPopCnt() const
        {
            return m_dwPopCnt;
        }
    };

    Runnable r0(que, elw::Thread::selfId());
    Runnable r1(que, elw::Thread::selfId());
    elw::Thread t0(&r0);
    elw::Thread t1(&r1);
    t0.start();
    t1.start();

    for (int i = 0; i < MSGCNT; ++i)
        que.push(new Message(elw::Thread::selfId(), i));
    que.push(NULL);
    que.push(NULL);

    t0.join();
    t1.join();

//    std::cout << r0.getPopCnt() << " " << r1.getPopCnt() << std::endl;

    if (que.size() != 0)
        return false;
    if (MSGCNT != (r0.getPopCnt() + r1.getPopCnt()))
        return false;

    return true;
}
