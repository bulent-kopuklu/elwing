/*
 * ConditionPolicyImpl.h
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

#ifndef ElwingConditionPolicyImpl_h__
#define ElwingConditionPolicyImpl_h__

BEGIN_ELW

class ConditionPolicyImpl :
    public elw::IConditionPolicy
{
    pthread_cond_t m_cond;
public:
    ConditionPolicyImpl();
    virtual ~ConditionPolicyImpl();

    bool signal();
    bool broadcast();
    int  wait(void* pvMtx);
    int  wait(void* pvMtx, dword dwMiliseconds);
};

END_ELW

#endif /* ElwingConditionPolicyImpl_h__ */
