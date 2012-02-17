/*
 * ThreadPool.h
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

#ifndef ElwingThreadPool_h__
#define ElwingThreadPool_h__

BEGIN_ELW


template <
    class _TyKey,
    class _TyWork
    >
class ThreadPool
{
public:
    class IWorker :
        public elw::IInterface
    {
    public:
        virtual void onWork(_TyWork msg) = 0;
    };

protected:
    class Message
    {
        _TyWork m_msg;
        IWorker& m_rWorker;
    public:
        Message(_TyWork msg, IWorker& rWorker) :
            m_msg(msg),
            m_rWorker(rWorker)
        {
        }

        _TyWork getUserMessage() const
        {
            return m_msg;
        }

        IWorker& getWorker() const
        {
            return m_rWorker;
        }
    };

    class Dispatcher :
        public elw::Thread
    {
        elw::ThreadQueue<Message*> m_queue;
    public:
        int run()
        {
            Message* p = NULL;
            while ((p = m_queue.pop()) != NULL)
            {
                p->getWorker().onWork(p->getUserMessage());
                delete p;
            }

            return 0;
        }

        void work(Message* pMsg)
        {
            m_queue.push(pMsg);
        }
    };

    class Pair
    {
        IWorker& m_rWorker;
        Dispatcher& m_rDispatcher;
    public:
        Pair(IWorker& rWorker, Dispatcher& rDispatcher) :
            m_rWorker(rWorker),
            m_rDispatcher(rDispatcher)
        {
        }

        virtual ~Pair()
        {
        }

        IWorker& getWorker() const
        {
            return m_rWorker;
        }

        Dispatcher& getDispatcher() const
        {
            return m_rDispatcher;
        }
    };

    typedef std::list<Dispatcher*> ThreadList;
    typedef typename ThreadList::iterator ThreadIterator;
    typedef std::map<_TyKey, elw::SmartPtr<Pair> > PairMap;
    typedef typename PairMap::iterator PairIterator;

    ThreadList m_lstThread;
    ThreadIterator m_itCrnt;
    PairMap m_mapPair;
    elw::SpinLock m_lock;
    bool m_fRunning;

public:
    bool start(int iThreadCount)
    {
        if (m_lstThread.size() > 0)
            return true;
        iThreadCount = std::min<int>(iThreadCount, 64);
        iThreadCount = std::max<int>(iThreadCount, 1);
        for (int i = 0; i < iThreadCount; ++i)
        {
            Dispatcher* p = new Dispatcher();
            if (!p->start())
            {
                killAll();
                delete p;
                return false;
            }

            m_lstThread.push_back(p);
        }

        m_itCrnt = m_lstThread.begin();
        m_fRunning = true;

        return true;
    }

    void killAll()
    {
        m_lock.lock();
        m_fRunning = false;
//        for (PairIterator it = m_mapPair.begin(); it != m_mapPair.end(); ++it)
//            (*it).second.release();
        m_mapPair.clear();
        m_lock.unlock();

        for (ThreadIterator it = m_lstThread.begin(); it != m_lstThread.end(); ++it)
        {
            (*it)->work(NULL);
            (*it)->join();
            delete (*it);
        }

        m_lstThread.clear();
    }

    bool addWorker(_TyKey key, ThreadPool<_TyKey, _TyWork>::IWorker& rWorker)
    {
        elw::ScopeGuard g(m_lock);
        if (!m_fRunning)
            return false;
        PairIterator it = m_mapPair.find(key);
        if (it != m_mapPair.end())
            return false;
        m_mapPair[key] = elw::SmartPtr<Pair>(new Pair(rWorker, getDispatcher()));
        return true;
    }

    void removeWorker(_TyKey key)
    {
        elw::ScopeGuard g(m_lock);
//        PairIterator it = m_mapPair.find(key);
//        if (it == m_mapPair.end())
//            return;
//        (*it).second.release();
        m_mapPair.erase(key);
    }

    bool work(_TyKey key, _TyWork msg)
    {
        elw::SmartPtr<Pair> ptrPair = getPair(key);
        if (ptrPair == NULL)
            return false;
        ptrPair->getDispatcher().work(
                new Message(msg, ptrPair->getWorker())
                );
        return true;
    }

public:
    ThreadPool() :
        m_fRunning(false)
    {
    }

protected:
    Dispatcher& getDispatcher()
    {
        if (++m_itCrnt == m_lstThread.end())
            m_itCrnt = m_lstThread.begin();
        return *(*m_itCrnt);
    }

    elw::SmartPtr<Pair> getPair(_TyKey key)
    {
        elw::ScopeGuard g(m_lock);
        if (!m_fRunning)
            return NULL;
        PairIterator it = m_mapPair.find(key);
        if (it == m_mapPair.end())
            return NULL;
        return (*it).second;
    }
};

END_ELW

#endif /* ElwingThreadPool_h__ */
