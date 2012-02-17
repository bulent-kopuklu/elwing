/*
 * ThreadQueue003.cpp
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
#include "tests/ThreadQueue003.h"
#include "util/Message.h"

std::string ThreadQueue003::getDescription() const
{
    std::stringstream strm;
    strm << "elw::ThreadQueu test." << " create 2 producer threads and create a consumer thread and pop from queu. msg cnt:" << MSGCNT;
    return strm.str();
}

bool ThreadQueue003::run()
{
    elw::ThreadQueue<Message*> que;

    class Consumer : public elw::IRunnable
    {
        elw::ThreadQueue<Message*>& m_que;
        dword m_dwPopCnt;
    public:
        Consumer(elw::ThreadQueue<Message*>& que) :
            m_que(que),
            m_dwPopCnt(0)
        {
        }

        int run()
        {
            Message* p = NULL;
            while ((p = m_que.pop()) != NULL)
            {
                ++m_dwPopCnt;
                delete p;
            }

            return 0;
        }

        dword getPopCnt() const
        {
            return m_dwPopCnt;
        }
    } r(que);

    elw::Thread tc(&r);
    tc.start();

    class Producer : public elw::IRunnable
    {
        elw::ThreadQueue<Message*>& m_que;
        dword m_dwMsgCnt;
    public:
        Producer(elw::ThreadQueue<Message*>& que, dword dwMsgCnt) :
            m_que(que),
            m_dwMsgCnt(dwMsgCnt)
        {
        }

        int run()
        {
            for (dword i = 0; i < m_dwMsgCnt; ++i)
                m_que.push(new Message(elw::Thread::selfId(), i));

            return 0;
        }
    };

    dword dwMessageCnt0 = MSGCNT / 2;
    dword dwMessageCnt1 = MSGCNT - dwMessageCnt0;

    Producer p0(que, dwMessageCnt0);
    Producer p1(que, dwMessageCnt1);

    elw::Thread tp0(&p0);
    elw::Thread tp1(&p1);
    tp0.start();
    tp1.start();

    tp0.join();
    tp1.join();
    que.push(NULL);
    tc.join();

    if (que.size() != 0)
        return false;
    if (MSGCNT != r.getPopCnt())
        return false;

    return true;
}
