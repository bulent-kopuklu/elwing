/*
 * Serialization.h
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

#ifndef ElwingSerialization_h__
#define ElwingSerialization_h__

BEGIN_ELW

template <class _Ty>
class BasicSerializer
{
    _Ty m_val;
public:
    std::istream& serialize(std::istream& is)
    {
        is.read((char*)&m_val, sizeof(m_val));
        return is;
    }

    std::ostream& serialize(std::ostream& os) const
    {
        os.write((const char*)&m_val, sizeof(m_val));
        return os;
    }

    operator _Ty()
    {
        return m_val;
    }

public:
    BasicSerializer(_Ty val) :
        m_val(val)
    {
    }

    BasicSerializer(std::istream& is) :
        m_val(0)
    {
        serialize(is);
    }
};

template <>
class BasicSerializer<std::string>
{
    std::string m_val;
public:
    std::istream& serialize(std::istream& is)
    {
        uint16 u16 = BasicSerializer<uint16>(is);
        if (u16 > 0)
        {
            elw::CharArray ary(u16);
            is >> ary;
            m_val = std::string(ary.ptr(), ary.length());
        }

        return is;
    }

    std::ostream& serialize(std::ostream& os) const
    {
        BasicSerializer<uint16>(m_val.size()).serialize(os);
        if (m_val.size() > 0)
            os << m_val;
        return os;
    }

    operator std::string()
    {
        return m_val;
    }

public:
    BasicSerializer(const std::string& val) :
        m_val(val)
    {
    }

    BasicSerializer(std::istream& is)
    {
        serialize(is);
    }
};


namespace serializer {

typedef BasicSerializer<int8>           Integer8;
typedef BasicSerializer<int16>          Integer16;
typedef BasicSerializer<int32>          Integer32;

typedef BasicSerializer<uint8>          Unsigned8;
typedef BasicSerializer<uint16>         Unsigned16;
typedef BasicSerializer<uint32>         Unsigned32;

typedef BasicSerializer<bool>           Boolean;
typedef BasicSerializer<double>         Double;
typedef BasicSerializer<float>          Float;
typedef BasicSerializer<std::string>    String;

}

template <class _Ty>
inline std::ostream& operator <<(std::ostream& os, const BasicSerializer<_Ty>& rInt)
{
    if (os.good())
    {
        rInt.serialize(os);
    }

    return os;
}

template <class _Ty>
inline std::istream& operator >>(std::istream& is, BasicSerializer<_Ty>& rInt)
{
    if (is.good())
    {
        rInt.serialize(is);
    }

    return is;
}

class ISerializable :
    public elw::IInterface
{
public:
};

END_ELW

#endif /* ElwingSerialization_h__ */
