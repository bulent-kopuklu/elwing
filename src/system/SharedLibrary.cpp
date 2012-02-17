/*
 * SharedLibrary.cpp
 *
 *  Created on: Dec 2, 2011
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

SharedLibrary::SharedLibrary() :
    m_pImpl(NULL),
    m_fIsLoaded(false)
{
//    m_pImpl = elw::ClassFactory::instantiate<elw::ISharedLibraryPolicy>(ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD);
    m_pImpl = (elw::ISharedLibraryPolicy*)elw::CreatePolicyImpl(ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD);
//    if (NULL == m_pImpl)
//        throw elw::ClassNotFoundException(ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD);
}

//SharedLibrary::SharedLibrary(const std::string& strLibraryPath) :
//    m_pImpl(NULL),
//    m_fIsLoaded(false)
//{
////    m_pImpl = elw::ClassFactory::instantiate<elw::ISharedLibraryPolicy>(ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD);
//    m_pImpl = (elw::ISharedLibraryPolicy*)elw::CreatePolicyImpl(ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD);
//    if (NULL == m_pImpl)
//        throw elw::ClassNotFoundException(ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD);
//    if (!load(strLibraryPath))
//        throw elw::SystemErrorException("load()");
//}

SharedLibrary::~SharedLibrary()
{
    if (NULL != m_pImpl)
    {
        if (m_fIsLoaded)
            m_pImpl->unload();
        delete m_pImpl;
    }
}

bool SharedLibrary::load(const std::string& strLibraryPath)
{
    if (true == m_fIsLoaded)
        unload();
    m_fIsLoaded = m_pImpl->load(strLibraryPath);
    return m_fIsLoaded;
}

void SharedLibrary::unload()
{
    m_pImpl->unload();
    m_fIsLoaded = false;
}

void* SharedLibrary::operator()(const std::string& strSymbolName)
{
    void* pvRslt = NULL;
    if (m_fIsLoaded)
        pvRslt = m_pImpl->symbol(strSymbolName);
    return pvRslt;
}

bool SharedLibrary::isLoaded() const
{
    return m_fIsLoaded;
}

pcstr SharedLibrary::err() const
{
    return m_pImpl->err();
}

END_ELW
