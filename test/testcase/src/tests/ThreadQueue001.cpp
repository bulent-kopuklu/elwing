/*
 * ThreadQueue001.cpp
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
#include "tests/ThreadQueue001.h"
#include "util/Message.h"

std::string ThreadQueue001::getDescription() const
{
    std::stringstream strm;
    strm << "elw::ThreadQueu test." << " create consumer thread and pop from queu. msg cnt:" << MSGCNT;
    return strm.str();
}

bool ThreadQueue001::run()
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
            Message* p = NULL;
            while ((p = m_que.pop()) != NULL)
            {
    //            std::cout << p->getSender() << " " << p->getParam() << std::endl;
                if (m_dwSender != p->getSender())
                    return -1;
                if (m_dwPopCnt != p->getParam())
                    return -1;
                ++m_dwPopCnt;
                delete p;
            }

            return 0;
        }

        dword getPopCnt() const
        {
            return m_dwPopCnt;
        }
    };

    Runnable r(que, elw::Thread::selfId());
    elw::Thread t(&r);
    t.start();

    for (int i = 0; i < MSGCNT; ++i)
    {
//        std::cout << "push " << i << std::endl;
        que.push(new Message(elw::Thread::selfId(), i));
    }
    que.push(NULL);
//    std::cout << "push completed" << std::endl;

    t.join();
    if (que.size() != 0)
        return false;
    if (MSGCNT != r.getPopCnt())
        return false;

    return true;
}
