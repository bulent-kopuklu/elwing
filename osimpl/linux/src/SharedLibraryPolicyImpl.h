/*
 * SharedLibraryPolicyImpl.h
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

#ifndef ElwingSharedLibraryPolicyImpl_h__
#define ElwingSharedLibraryPolicyImpl_h__

BEGIN_ELW

class SharedLibraryPolicyImpl :
    public elw::ISharedLibraryPolicy
{
    void* m_pvHandle;
public:
    bool load(
            const std::string& strLibraryPath
            ) throw() ;

    void unload() throw() ;

    void* symbol(
            const std::string& strSymbolName
            ) throw() ;

    pcstr err() const throw();

public:
    SharedLibraryPolicyImpl() throw();
    virtual ~SharedLibraryPolicyImpl() throw();
};

END_ELW

#endif /* ElwingSharedLibraryPolicyImpl_h__ */
