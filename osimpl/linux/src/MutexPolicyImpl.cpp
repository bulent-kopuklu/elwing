/*
 * MutexPolicyImpl.cpp
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
#include "MutexPolicyImpl.h"

BEGIN_ELW

MutexPolicyImpl::MutexPolicyImpl()
{
    pthread_mutexattr_t attr;

    ::pthread_mutexattr_init(&attr);
    ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    ::pthread_mutex_init(&m_mtx, &attr);
    ::pthread_mutexattr_destroy(&attr);
}

MutexPolicyImpl::~MutexPolicyImpl()
{
    ::pthread_mutex_destroy(&m_mtx);
}

void MutexPolicyImpl::lock()
{
    ::pthread_mutex_lock(&m_mtx);
}

void MutexPolicyImpl::unlock()
{
    ::pthread_mutex_unlock(&m_mtx);
}

bool MutexPolicyImpl::tryLock()
{
    return 0 == ::pthread_mutex_trylock(&m_mtx);
}

void* MutexPolicyImpl::getMutexObject()
{
    return &m_mtx;
}

//REGISTER_ELW_MUTEX_POLICY_IMPL(MutexPolicyImpl);

END_ELW
