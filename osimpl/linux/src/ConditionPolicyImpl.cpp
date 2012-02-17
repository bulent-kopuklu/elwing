/*
 * ConditionPolicyImpl.cpp
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
#include "ConditionPolicyImpl.h"

BEGIN_ELW

ConditionPolicyImpl::ConditionPolicyImpl()
{
    ::pthread_cond_init(&m_cond, 0);
}

ConditionPolicyImpl::~ConditionPolicyImpl()
{
    ::pthread_cond_destroy(&m_cond);
}

bool ConditionPolicyImpl::signal()
{
    return 0 == ::pthread_cond_signal(&m_cond);
}

bool ConditionPolicyImpl::broadcast()
{
   return 0 == ::pthread_cond_broadcast(&m_cond);
}

int ConditionPolicyImpl::wait(void* pvMtx)
{
    return ::pthread_cond_wait(&m_cond, (pthread_mutex_t*)pvMtx);
}

int ConditionPolicyImpl::wait(void* pvMtx, dword dwMiliseconds)
{
    struct timeval tp;
    ::gettimeofday(&tp, 0);
    dword dwSeconds = tp.tv_sec;
    dword dwNanoSeconds = tp.tv_usec*1000;
    dword dwInSeconds = dwMiliseconds/1000;
    dwSeconds += dwInSeconds;
    dwNanoSeconds += (dwMiliseconds - dwInSeconds*1000) * 1000000;
    if (dwNanoSeconds > 999999999)
    {
        dwSeconds += 1;
        dwNanoSeconds -= 1000000000;
    }

    timespec rqts = { dwSeconds, dwNanoSeconds };
    int iRslt = ::pthread_cond_timedwait(&m_cond, (pthread_mutex_t*)pvMtx, &rqts);
    if (iRslt == ETIMEDOUT)
        return 1;

    return 0;
}

//REGISTER_ELW_CONDITION_POLICY_IMPL(ConditionPolicyImpl);

END_ELW
