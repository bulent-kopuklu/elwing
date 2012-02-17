/*
 * ISharedLibraryPolicy.h
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

#ifndef ElwingISharedLibraryPolicy_h__
#define ElwingISharedLibraryPolicy_h__

BEGIN_ELW

class ISharedLibraryPolicy :
    public elw::IInterface
{
public:
    virtual bool load(
            const std::string& strLibraryPath
            ) throw () = 0;

    virtual void unload() throw() = 0;

    virtual void* symbol(
            const std::string& strSymbolName
            ) throw() = 0;

    virtual pcstr err() const throw() = 0;
};

#define ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD   ("elw::system::SharedLibraryPolicyImpl")
#define REGISTER_ELW_SHARED_LIBRARY_POLICY_IMPL(__impl) \
    REGISTER_CLASS(\
        ELW_SHARED_LIBRARY_POLICY_IMPL_KEYWORD,\
        ISharedLibraryPolicy,\
        __impl,\
        false,\
        ClassFactory::eStandart\
        )

END_ELW

#endif /* ElwingISharedLibraryPolicy_h__ */
