/*
 * MutexPolicyImpl.h
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

#ifndef ElwingMutexPolicyImpl_h__
#define ElwingMutexPolicyImpl_h__

BEGIN_ELW

class MutexPolicyImpl :
    public elw::IMutexPolicy
{
    pthread_mutex_t m_mtx;
public:
    MutexPolicyImpl();
    virtual ~MutexPolicyImpl();

public:
    void lock();
    void unlock();

    bool tryLock();

    void* getMutexObject();
};

END_ELW

#endif /* ElwingMutexPolicyImpl_h__ */
