/*
 * ClassFactory.cpp
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

#include "stdafx.h"

BEGIN_ELW

Instantator::Instantator(IAllocator* pAllocator, bool fIsOverridable) :
    m_pAllocator(pAllocator),
    m_fIsOverridable(fIsOverridable)
{
}

Instantator::~Instantator()
{
    delete m_pAllocator;
}

bool Instantator::override(IAllocator* pAllocator)
{
    if (!m_fIsOverridable)
        return false;

    delete m_pAllocator;
    m_pAllocator = pAllocator;
    return true;
}

bool Instantator::isOveridable() const
{
    return m_fIsOverridable;
}

ClassFactory::Storage::~Storage()
{
    for (iterator it = begin(); it != end(); ++it)
        delete (*it).second;
    clear();
}

ClassFactory::Storage& ClassFactory::getStorage()
{
    static ClassFactory::Storage s;
    return s;
}

END_ELW
