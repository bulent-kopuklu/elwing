/*
 * AtomicInteger.cpp
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

BEGIN_ELW

AtomicInteger::AtomicInteger(int iInitialValue) :
    m_pImpl(NULL)
{
//    m_pImpl = ClassFactory::instantiate<elw::IAtomicIntegerPolicy>(ELW_ATOMIC_INTEGER_POLICY_IMPL_KEYWORD);
    m_pImpl = (elw::IAtomicIntegerPolicy*)elw::CreatePolicyImpl(ELW_ATOMIC_INTEGER_POLICY_IMPL_KEYWORD);
//    if (NULL == m_pImpl)
//        throw elw::ClassNotFoundException(ELW_ATOMIC_INTEGER_POLICY_IMPL_KEYWORD);
    m_pImpl->setValue(iInitialValue);
}

AtomicInteger::~AtomicInteger()
{
    delete m_pImpl;
}

int AtomicInteger::operator +(int iVal)
{
    return m_pImpl->increment(iVal);
}

int AtomicInteger::operator -(int iVal)
{
    return m_pImpl->decrement(iVal);
}

int AtomicInteger::operator =(int iVal)
{
    m_pImpl->setValue(iVal);
    return iVal;
}

AtomicInteger::operator int()
{
    return m_pImpl->getValue();
}
END_ELW
