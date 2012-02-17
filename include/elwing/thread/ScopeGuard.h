/*
 * ScopeLock.h
 *
 *  Created on: Oct 7, 2011
 *      Author: altar
 */

#ifndef SCOPELOCK_H_
#define SCOPELOCK_H_

BEGIN_ELW

class ScopeGuard
{
    elw::ILockable& m_rLock;
public:
    ScopeGuard(elw::ILockable& rLock) :
        m_rLock(rLock)
    {
        m_rLock.lock();
    }

    virtual ~ScopeGuard()
    {
        m_rLock.unlock();
    }
};

END_ELW

#endif /* SCOPELOCK_H_ */
