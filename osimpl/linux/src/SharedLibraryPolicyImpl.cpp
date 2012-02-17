/*
 * SharedLibraryPolicyImpl.cpp
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
#include "SharedLibraryPolicyImpl.h"

BEGIN_ELW

SharedLibraryPolicyImpl::SharedLibraryPolicyImpl() throw() :
    m_pvHandle(NULL)
{
}

SharedLibraryPolicyImpl::~SharedLibraryPolicyImpl() throw()
{
    if (NULL == m_pvHandle)
        unload();
}

bool SharedLibraryPolicyImpl::load(const std::string& strLibraryPath) throw()
{
    m_pvHandle = ::dlopen(strLibraryPath.c_str(), RTLD_LAZY);
    if (NULL == m_pvHandle)
        return false;
    ::dlerror();
    return true;
}

void SharedLibraryPolicyImpl::unload() throw()
{
    if ((m_pvHandle != NULL) && (0 == ::dlclose(m_pvHandle)))
    {
        m_pvHandle = NULL;
    }
}

void* SharedLibraryPolicyImpl::symbol(const std::string& strSymbolName) throw()
{
    if (NULL == m_pvHandle)
        return NULL;
    return ::dlsym(m_pvHandle, strSymbolName.c_str());
}

pcstr SharedLibraryPolicyImpl::err() const throw()
{
    return ::dlerror();
}

//REGISTER_ELW_SHARED_LIBRARY_POLICY_IMPL(SharedLibraryPolicyImpl);

END_ELW
