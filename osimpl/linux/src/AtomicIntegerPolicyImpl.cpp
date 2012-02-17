/*
 * AtomicIntegerPolicyImpl.cpp
 *
 *  Created on: Oct 6, 2011
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
#include "AtomicIntegerPolicyImpl.h"

BEGIN_ELW
/*
int AtomicIntegerPolicyImpl::increment(int iVal)
{
    return __sync_add_and_fetch(&m_iValue, iVal);
}

int AtomicIntegerPolicyImpl::decrement(int iVal)
{
    return __sync_sub_and_fetch(&m_iValue, iVal);
}

int AtomicIntegerPolicyImpl::getValue() const
{
    int iRslt = 0;
    __sync_lock_test_and_set(&iRslt, m_iValue);
    return iRslt;
}

int AtomicIntegerPolicyImpl::setValue(int iVal)
{
    __sync_lock_test_and_set(&m_iValue, iVal);
    return iVal;
}
*/


AtomicIntegerPolicyImpl::AtomicIntegerPolicyImpl()
{
    ::pthread_mutex_init(&m_mtx, NULL);
}

AtomicIntegerPolicyImpl::~AtomicIntegerPolicyImpl()
{
    ::pthread_mutex_destroy(&m_mtx);
}

int AtomicIntegerPolicyImpl::increment(int iVal)
{
    int iRslt = 0;
    pthread_mutex_lock(&m_mtx);
    iRslt = m_iValue += iVal;
    pthread_mutex_unlock(&m_mtx);
    return iRslt;
}

int AtomicIntegerPolicyImpl::decrement(int iVal)
{
    int iRslt = 0;
    pthread_mutex_lock(&m_mtx);
    iRslt = m_iValue -= iVal;
    pthread_mutex_unlock(&m_mtx);
    return iRslt;
}

int AtomicIntegerPolicyImpl::getValue()
{
    int iRslt = 0;
    pthread_mutex_lock(&m_mtx);
    iRslt = m_iValue;
    pthread_mutex_unlock(&m_mtx);
    return iRslt;
}

int AtomicIntegerPolicyImpl::setValue(int iVal)
{
    pthread_mutex_lock(&m_mtx);
    m_iValue = iVal;
    pthread_mutex_unlock(&m_mtx);
    return iVal;
}


//REGISTER_ELW_ATOMIC_INTEGER_POLICY_IMPL(AtomicIntegerPolicyImpl);

END_ELW
