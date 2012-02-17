/*
 * ThreadPool001.cpp
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
#include "tests/ThreadPool001.h"
#include "util/Message.h"


class Handler :
    public elw::ThreadPool<uint, Message*>::IWorker
{
    uint m_uKey;
    dword m_dwSelfId;
    bool m_fSuccess;
    uint m_uWorkCnt;
    std::list<dword> m_lst;
public:
    Handler(uint uKey) :
        m_uKey(uKey),
        m_dwSelfId(0),
        m_fSuccess(true),
        m_uWorkCnt(0)
    {
    }

    bool isSuccess() const
    {
        if (!m_fSuccess)
            return false;
        return m_lst.size() == 2;
    }

    uint getWorkCnt() const
    {
        return m_uWorkCnt;
    }

    void onWork(Message* pmsg)
    {
        if (m_dwSelfId == 0)
        {
            m_dwSelfId = elw::Thread::selfId();
        }
        else
        {
            if (m_dwSelfId != elw::Thread::selfId())
            {
                m_fSuccess = false;
            }
        }

        bool fFound = false;
        dword dwSender = pmsg->getSender();
        for (std::list<dword>::iterator it = m_lst.begin(); it != m_lst.end(); ++it)
        {
            if ((*it) == dwSender)
            {
                fFound = true;
                break;
            }
        }

        if (!fFound)
        {
            m_lst.push_back(dwSender);
        }

        ++m_uWorkCnt;
        delete pmsg;
    }
};

class Producer :
    public elw::Thread
{
    uint m_uKey;
    uint m_uMsgCnt;
    uint m_uFailedWork;
    elw::ThreadPool<uint, Message*>& m_tp;
public:
    Producer(uint uKey, uint uMsgCnt, elw::ThreadPool<uint, Message*>& tp) :
        m_uKey(uKey),
        m_uMsgCnt(uMsgCnt),
        m_uFailedWork(0),
        m_tp(tp)
    {
        start();
    }

    uint getFailedCnt() const
    {
        return m_uFailedWork;
    }

protected:
    int run()
    {
        for (uint i = 0; i < m_uMsgCnt; ++i)
        {
            if (!m_tp.work(m_uKey, new Message(elw::Thread::selfId(), i)))
                ++m_uFailedWork;
        }

        m_tp.removeWorker(m_uKey);

        return 0;
    }
};

std::string ThreadPool001::getDescription() const
{
    std::stringstream strm;
    strm << "elw::ThreadPool test." << " consumer thread count 2, handler count 8, producer thread count 16. msg cnt:" << MSGCNT;
    return strm.str();
}

bool ThreadPool001::run()
{
    elw::ThreadPool<uint, Message*> tpool;
    if (!tpool.start(2))
        return false;

    std::list<Handler*> lstHandlers;
    for (int i = 1; i <= 8; ++i)
    {
        Handler* p = new Handler(i*1000);
        tpool.addWorker(i*1000, *p);
        lstHandlers.push_back(p);
    }

    uint uMsgCnt = MSGCNT / 16;
    uint uFirstThreadMsgCnt = uMsgCnt + (MSGCNT - uMsgCnt*16);

    std::list<Producer*> lstThreads;
    for (int i = 1; i <= 8; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            uint u = lstThreads.size() == 0 ? uFirstThreadMsgCnt : uMsgCnt;
            lstThreads.push_back(new Producer(i*1000, u, tpool));
        }
    }

    uint uWorkCnt = 0;
    for (std::list<Producer*>::iterator it = lstThreads.begin(); it != lstThreads.end(); ++it)
    {
        (*it)->join();
        uWorkCnt += (*it)->getFailedCnt();
        delete (*it);
    }

    lstThreads.clear();
    tpool.killAll();


    bool fSuccess = true;
    for (std::list<Handler*>::iterator it = lstHandlers.begin(); it != lstHandlers.end(); ++it)
    {
        if (!(*it)->isSuccess())
            fSuccess = false;
        uWorkCnt += (*it)->getWorkCnt();
        delete (*it);
    }

    lstHandlers.clear();
    if (!fSuccess)
        return false;

    if (uWorkCnt != MSGCNT)
        return false;

    return true;
}
