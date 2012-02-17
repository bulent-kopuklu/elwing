/*
 * IMutexPolicy.h
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

#ifndef ElwingIMutexPolicy_h__
#define ElwingIMutexPolicy_h__

BEGIN_ELW

class IMutexPolicy :
    public elw::IInterface
{
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual bool tryLock() = 0;

    virtual void* getMutexObject() = 0;
};

#define ELW_MUTEX_POLICY_IMPL_KEYWORD   ("elw::thread::MutexPolicyImpl")
#define REGISTER_ELW_MUTEX_POLICY_IMPL(__impl) \
    REGISTER_CLASS(\
        ELW_MUTEX_POLICY_IMPL_KEYWORD,\
        IMutexPolicy,\
        __impl,\
        false,\
        ClassFactory::eStandart\
        )

END_ELW

#endif /* ElwingIMutexPolicy_h__ */
