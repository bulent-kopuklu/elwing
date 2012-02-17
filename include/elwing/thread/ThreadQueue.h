/*
 * ThreadQueue.h
 *
 *  Created on: Sep 30, 2011
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

#ifndef ElwingThreadQueue_h__
#define ElwingThreadQueue_h__

BEGIN_ELW

template <
    class _TyMessage,
    class _TyEventPolicy = elw::Event,
    class _TyLockPolicy = elw::SpinLock
    >
class ThreadQueue
{
    std::deque<_TyMessage> m_queu;
    _TyEventPolicy m_event;
    _TyLockPolicy m_lock;
    dword m_dwMaxSize;

public:
    virtual void clear()
    {
        elw::ScopeGuard g(m_lock);
        m_queu.clear();
    }

    virtual size_t size()
    {
        return m_queu.size();
    }

    virtual bool push(_TyMessage msg)
    {
        m_lock.lock();
        m_queu.push_back(msg);
        m_lock.unlock();
        m_event.notify();
        return true;
    }

    virtual bool pushFront(_TyMessage msg)
    {
        m_lock.lock();
        m_queu.push_front(msg);
        m_lock.unlock();
        m_event.notify();
        return true;
    }

    virtual bool peek(_TyMessage& msg)
    {
        bool fRslt;
        m_lock.lock();
        if (!m_queu.empty())
        {
            msg = m_queu.front();
            m_queu.pop_front();
            fRslt = true;
        }
        m_lock.unlock();
        return fRslt;
    }

    virtual _TyMessage pop()
    {
        _TyMessage msg;
        m_event.wait();
        m_lock.lock();
        msg = m_queu.front();
        m_queu.pop_front();
        m_lock.unlock();

        return msg;
    }

public:
    ThreadQueue(dword dwMaxSize = MAX_ULONG) :
        m_dwMaxSize(dwMaxSize)
    {
    }

    virtual ~ThreadQueue()
    {
    }


private:
    DISABLE_COPY(ThreadQueue);
};

END_ELW

#endif /* ElwingConsumerThread_h__ */
