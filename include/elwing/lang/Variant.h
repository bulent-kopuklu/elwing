/*
 * Variant.h
 *
 *  Created on: Dec 20, 2011
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

#ifndef ElwingVariant_h__
#define ElwingVariant_h__

BEGIN_ELW

template <typename _Ty>
struct Type
{
    typedef _Ty type;
    typedef const _Ty const_type;
    typedef _Ty& ref_type;
    typedef const _Ty& const_ref_type;
};

class Variant
{
    template<class _Ty>
    struct Value :
        public elw::IInterface
    {
        Value(_Ty val) :
            m_val(val)
        {
        }

        virtual ~Value()
        {
        }

        _Ty m_val;
    };

    elw::SmartPtr<elw::IInterface> m_ptrVal;

public:
    Variant()
    {
    }

    template<class _Ty>
    Variant(_Ty val) :
        m_ptrVal(new Value<typename Type<_Ty>::type>(val))
    {
    }

    template<class _Ty>
    typename Type<_Ty>::ref_type getValue()
    {
        return dynamic_cast<Value<typename Type<_Ty>::type>&>(*m_ptrVal).m_val;
    }

    template<class _Ty>
    typename Type<_Ty>::const_ref_type getValue() const
    {
        return dynamic_cast<Value<typename Type<_Ty>::type>&>(*m_ptrVal).m_val;
    }

    template<class _Ty>
    void setValue(typename Type<_Ty>::const_ref_type val)
    {
        m_ptrVal = new Value<typename Type<_Ty>::type>(val);
    }
};

END_ELW

#endif /* ElwingVariant_h__ */
