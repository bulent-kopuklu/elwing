/*
 * ILockable.h
 *
 *  Created on: Oct 7, 2011
 *      Author: altar
 */

#ifndef ILOCKABLE_H_
#define ILOCKABLE_H_

BEGIN_ELW

class ILockable :
    public elw::IInterface
{
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual bool tryLock() = 0;
};

END_ELW

#endif /* ILOCKABLE_H_ */
