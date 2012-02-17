/*
 * Mutex.cpp
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

#include "stdafx.h"

BEGIN_ELW

Mutex::Mutex() :
    m_pImpl(NULL)
//    m_fOwner(false)
{
//    m_pImpl = elw::ClassFactory::instantiate<elw::IMutexPolicy>(ELW_MUTEX_POLICY_IMPL_KEYWORD);
    m_pImpl = (elw::IMutexPolicy*)elw::CreatePolicyImpl(ELW_MUTEX_POLICY_IMPL_KEYWORD);
//    if (NULL == m_pImpl)
//        throw elw::ClassNotFoundException(ELW_MUTEX_POLICY_IMPL_KEYWORD);
//    m_fOwner = true;
}

//Mutex::Mutex(Mutex& rMtx) :
//    m_pImpl(rMtx.m_pImpl),
//    m_fOwner(false)
//{
//}

Mutex::~Mutex()
{
//    if (m_fOwner)
        delete m_pImpl;
}

void Mutex::lock()
{
    m_pImpl->lock();
}

void Mutex::unlock()
{
    m_pImpl->unlock();
}

bool Mutex::tryLock()
{
    return m_pImpl->tryLock();
}

END_ELW
