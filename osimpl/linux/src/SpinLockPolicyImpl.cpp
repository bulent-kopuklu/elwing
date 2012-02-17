/*
 * SpinLockPolicyImpl.cpp
 *
 *  Created on: Oct 7, 2011
 *      Author: altar
 */

#include "stdafx.h"
#include "SpinLockPolicyImpl.h"

BEGIN_ELW
/*
SpinLockPolicyImpl::SpinLockPolicyImpl()
{
    if (0 > ::pthread_spin_init(&m_spin, 0))
        throw elw::SystemErrorException(
                MKSTR("::pthread_spin_init() failed !!! " << errno << " <" << strerror(errno) << ">")
                );
}

SpinLockPolicyImpl::~SpinLockPolicyImpl() throw()
{
    ::pthread_spin_destroy(&m_spin);
}

bool SpinLockPolicyImpl::lock() throw()
{
    return 0 == ::pthread_spin_lock(&m_spin);
}

bool SpinLockPolicyImpl::unlock() throw()
{
    return 0 == ::pthread_spin_unlock(&m_spin);
}

bool SpinLockPolicyImpl::tryLock() throw()
{
    return true;
}
*/

SpinLockPolicyImpl::SpinLockPolicyImpl()
{
    ::pthread_mutex_init(&m_mtx, NULL);
}

SpinLockPolicyImpl::~SpinLockPolicyImpl()
{
    ::pthread_mutex_destroy(&m_mtx);
}

void SpinLockPolicyImpl::lock()
{
    ::pthread_mutex_lock(&m_mtx);
}

void SpinLockPolicyImpl::unlock()
{
    ::pthread_mutex_unlock(&m_mtx);
}

bool SpinLockPolicyImpl::tryLock()
{
    return 0 == ::pthread_mutex_trylock(&m_mtx);
}
//REGISTER_ELW_SPIN_LOCK_POLICY_IMPL(SpinLockPolicyImpl);

END_ELW
