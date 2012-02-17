/*
 * InputStream.h
 *
 *  Created on: Oct 14, 2011
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

#ifndef ElwingInputStream_h__
#define ElwingInputStream_h__

BEGIN_ELW

class InputStream :
    public std::istream
{
    elw::SmartPtr<IInputChannel> m_ptrReader;
public:
    InputStream(elw::SmartPtr<elw::IInputChannel> ptrReader);
    virtual ~InputStream();


    bool isOpened();
    void close();
};

END_ELW

#endif /* ElwingInputStream_h__ */
