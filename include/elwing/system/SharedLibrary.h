/*
 * SharedLibrary.h
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

#ifndef ElwingSharedLibrary_h__
#define ElwingSharedLibrary_h__

BEGIN_ELW

class SharedLibrary
{
    elw::ISharedLibraryPolicy* m_pImpl;
    bool m_fIsLoaded;
public:
    bool load(const std::string& strLibaryPath);
    void unload();

    void* operator()(const std::string& strSymbol);

    bool isLoaded() const;

    pcstr err() const;

public:
    SharedLibrary();
//    SharedLibrary(const std::string& strLibraryPath);
    virtual ~SharedLibrary();
};

END_ELW

#endif /* ElwingSharedLibrary_h__ */
