/*
 * Class.h
 *
 *  Created on: Oct 24, 2011
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

#ifndef Class_h__
#define Class_h__

class ITestBase :
    public elw::IInterface
{
public:
    virtual std::string toString() = 0;
    virtual int getId() const = 0;
};

class TestClass :
    public ITestBase
{
public:
    int m_i;
public:
    TestClass(int i) :
        m_i(i)
    {
    }

    std::string toString()
    {
        std::stringstream strm;
        strm << "Class:" << m_i;
        return strm.str();
    }

    int getId() const
    {
        return m_i;
    }

    virtual ~TestClass()
    {

    }
};


#endif /* Class_h__ */
