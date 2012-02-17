/*
 * Condition.cpp
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

#include "stdafx.h"

BEGIN_ELW

Condition::Condition(elw::Mutex* pMtx) :
    m_pImpl(NULL),
    m_pMtx(pMtx),
    m_fPrivateMutex(false)
{
//    m_pImpl = ClassFactory::instantiate<elw::IConditionPolicy>(ELW_CONDITION_POLICY_IMPL_KEYWORD);
    m_pImpl = (elw::IConditionPolicy*)elw::CreatePolicyImpl(ELW_CONDITION_POLICY_IMPL_KEYWORD);
//    if (NULL == m_pImpl)
//        throw elw::ClassNotFoundException(ELW_CONDITION_POLICY_IMPL_KEYWORD);
    if (NULL == m_pMtx)
    {
        m_pMtx = new elw::Mutex();
        m_fPrivateMutex = true;
    }
}

Condition::~Condition()
{
    delete m_pImpl;
    if (m_fPrivateMutex)
        delete m_pMtx;
}

bool Condition::signal()
{
    return m_pImpl->signal();
}
bool Condition::broadcast()
{
    return m_pImpl->broadcast();
}

int Condition::wait()
{
    if (m_fPrivateMutex)
        m_pMtx->lock();
    int iRslt = m_pImpl->wait(m_pMtx->m_pImpl->getMutexObject());
    if (m_fPrivateMutex)
        m_pMtx->unlock();
    return iRslt;
}

int Condition::wait(dword dwMiliseconds)
{
    if (m_fPrivateMutex)
        m_pMtx->lock();
    int iRslt = m_pImpl->wait(m_pMtx->m_pImpl->getMutexObject(), dwMiliseconds);
    if (m_fPrivateMutex)
        m_pMtx->unlock();
    return iRslt;
}

END_ELW
