/*
 * Factory.cpp
 *
 *  Created on: Jan 23, 2012
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
#include "ConditionPolicyImpl.h"
#include "FilePolicyImpl.h"
#include "MutexPolicyImpl.h"
#include "SharedLibraryPolicyImpl.h"
#include "SocketPolicyImpl.h"
#include "SpinLockPolicyImpl.h"
#include "ThreadPolicyImpl.h"

BEGIN_ELW

IInterface* CreatePolicyImpl(const std::string& strName)
{
    IInterface* pRslt = NULL;
    if (strName == ELW_ATOMIC_INTEGER_POLICY_IMPL_KEYWORD)
        pRslt = new AtomicIntegerPolicyImpl();
    else if (strName == ELW_CONDITION_POLICY_IMPL_KEYWORD)
        pRslt = new ConditionPolicyImpl();
    else if (strName == ELW_FILE_POLICY_IMPL_KEYWORD)
        pRslt = new FilePolicyImpl();
    else if (strName == ELW_MUTEX_POLICY_IMPL_KEYWORD)
        pRslt = new MutexPolicyImpl();
    else if (strName == ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD)
        pRslt = new SharedLibraryPolicyImpl();
    else if (strName == ELW_SOCKET_POLICY_IMPL_KEYWORD)
        pRslt = new SocketPolicyImpl();
    else if (strName == ELW_SPIN_LOCK_POLICY_IMPL_KEYWORD)
        pRslt = new SpinLockPolicyImpl();
    else if (strName == ELW_THREAD_POLICY_IMPL_KEYWORD)
        pRslt = new ThreadPolicyImpl();

    return pRslt;
}



END_ELW
