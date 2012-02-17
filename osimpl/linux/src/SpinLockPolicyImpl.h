/*
 * SpinLockPolicyImpl.h
 *
 *  Created on: Oct 7, 2011
 *      Author: altar
 */

#ifndef SPINLOCKPOLICYIMPL_H_
#define SPINLOCKPOLICYIMPL_H_

BEGIN_ELW

/*
class SpinLockPolicyImpl :
    public elw::ISpinLockPolicy
{
    pthread_spinlock_t m_spin;
public:
    SpinLockPolicyImpl();
    virtual ~SpinLockPolicyImpl() throw();

    bool lock() throw();
    bool unlock() throw();
    bool tryLock() throw();
};
*/

class SpinLockPolicyImpl :
    public elw::ISpinLockPolicy
{
    pthread_mutex_t m_mtx;
public:
    SpinLockPolicyImpl();
    virtual ~SpinLockPolicyImpl();

    void lock();
    void unlock();
    bool tryLock();
};

END_ELW

#endif /* SPINLOCKPOLICYIMPL_H_ */
