/*
 * Thread.cpp
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

BEGIN_ELW

Thread::Thread(IRunnable* pRunnable) :
    m_pImpl(NULL),
    m_pRunnable(pRunnable)
{
//    m_pImpl = elw::ClassFactory::instantiate<elw::IThreadPolicy>(ELW_THREAD_POLICY_IMPL_KEYWORD);
    m_pImpl = (elw::IThreadPolicy*)elw::CreatePolicyImpl(ELW_THREAD_POLICY_IMPL_KEYWORD);
//    if (NULL == m_pImpl)
//        throw elw::ClassNotFoundException(ELW_THREAD_POLICY_IMPL_KEYWORD);
}

Thread::~Thread()
{
    kill();
    delete m_pImpl;
}

bool Thread::start()
{
    return m_pImpl->start(m_pRunnable != NULL ? *m_pRunnable : *this);
}

void Thread::kill()
{
    m_pImpl->kill();
}

void Thread::join()
{
    m_pImpl->join();
}

dword Thread::getId() const
{
    return m_pImpl->getId();
}

int Thread::run()
{
    return 0;
}

void Thread::sleep(dword dwMiliseconds)
{
    elw::Sleep(dwMiliseconds);
}

void Thread::yield(void)
{
    elw::Yield();
}

dword Thread::selfId(void)
{
    return elw::SelfId();
}

dword Thread::tick(void)
{
    return elw::Tick();
}

END_ELW
