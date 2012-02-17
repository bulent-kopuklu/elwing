/*
 * Condition.cpp
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

#include "stdafx.h"

BEGIN_ELW

Event::Event() :
    m_iNotifyCnt(0),
    m_iWaitCnt(0),
    m_cond(&m_mtx)
{
}

Event::~Event()
{
}

int Event::wait()
{
    elw::ScopeGuard g(m_mtx);
    ++m_iWaitCnt;
    while (m_iNotifyCnt == 0)
        m_cond.wait();
    --m_iNotifyCnt;
    --m_iWaitCnt;

    return 0;
}

int Event::wait(dword dwTimeout)
{
    int iRslt = 0;
    elw::ScopeGuard g(m_mtx);
    ++m_iWaitCnt;
    while (m_iNotifyCnt == 0)
    {
        iRslt = m_cond.wait(dwTimeout);
        if (iRslt == 1)
            break;
    }

    if (iRslt == 0)
        --m_iNotifyCnt;
    --m_iWaitCnt;

    return iRslt;
}

bool Event::notify()
{
    m_mtx.lock();
    bool fHaveWaiters = (m_iWaitCnt > 0);
    ++m_iNotifyCnt;
    m_mtx.unlock();
    bool fRslt = true;
    if (fHaveWaiters)
        fRslt = m_cond.signal();
    return fRslt;
}

bool Event::notifyAll()
{
    m_mtx.lock();
    m_iNotifyCnt = m_iWaitCnt;
    m_mtx.unlock();
    m_cond.broadcast();

    return true;
}

END_ELW
