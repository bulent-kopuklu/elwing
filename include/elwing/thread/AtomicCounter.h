/*
 * AtomicCounter.h
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

#ifndef ElwingAtomicCounter_h__
#define ElwingAtomicCounter_h__

BEGIN_ELW

class AtomicCounter
{
    elw::AtomicInteger m_int;
public:
    AtomicCounter(int iInitialValue = 0) :
        m_int(iInitialValue)
    {
    }

public:
    int operator++()
    {
        return m_int + 1;
    }

    int operator++(int)
    {
        return m_int + 1;
    }

    int operator--()
    {
        return m_int - 1;
    }

    int operator--(int)
    {
        return m_int - 1;
    }

    operator int()
    {
        return m_int;
    }
};

END_ELW

#endif /* ElwingAtomicCounter_h__ */
