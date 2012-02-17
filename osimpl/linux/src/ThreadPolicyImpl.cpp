/*
 * ThreadPolicyImpl.cpp
 *
 *  Created on: Sep 29, 2011
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
#include "ThreadPolicyImpl.h"

BEGIN_ELW

ThreadPolicyImpl::ThreadPolicyImpl(void) :
    m_hThread(0)
{
}

ThreadPolicyImpl::~ThreadPolicyImpl(void)
{
    kill();
}

bool ThreadPolicyImpl::start(IRunnable& rRunnable)
{
    if (m_hThread != 0)
        return true;
    return (0 == ::pthread_create(&m_hThread, NULL, main, &rRunnable));
}

bool ThreadPolicyImpl::kill()
{
    if (m_hThread == 0)
        return false;
    ::pthread_cancel(m_hThread);
    ::pthread_join(m_hThread, NULL);
    m_hThread = 0;
    return true;
}

bool ThreadPolicyImpl::join()
{
    if (m_hThread == 0)
        return false;
    ::pthread_join(m_hThread, NULL);
    m_hThread = 0;
    return true;
}

//void ThreadPolicyImpl::setPriority(elw::IThread::EPriority ePriority)
//{
//}

dword ThreadPolicyImpl::getId() const
{
    return (dword) m_hThread;
}

//////////////////////////////////////////////////////////////////////////

void* ThreadPolicyImpl::main(void* pvParam)
{
    elw::IRunnable* pThis = (elw::IRunnable*)pvParam;
    int iRslt = pThis->run();
    pthread_exit((void*)iRslt);

    return NULL;
}

//////////////////////////////////////////////////////////////////////////

void Sleep(dword dwMiliseconds)
{
    struct timespec timeout = {
            dwMiliseconds / 1000,
            (dwMiliseconds % 1000) * 1000 * 1000
            };
    ::nanosleep(&timeout, NULL);
}

dword SelfId(void)
{
    return (dword) ::pthread_self();
}

dword Tick(void)
{
    struct timeval tp;
    int iRslt =  ::gettimeofday(&tp, NULL);
    if (iRslt < 0)
        return 0;
    return ((tp.tv_sec*1000) + (tp.tv_usec/1000));
}

void Yield(void)
{
//    ::pthread_yield();
    ::sched_yield();
}

//REGISTER_ELW_THREAD_POLICY_IMPL(ThreadPolicyImpl);

END_ELW
