/*
 * SmartPtr.h
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

#ifndef ElwingSmartPtr_h__
#define ElwingSmartPtr_h__

BEGIN_ELW


class NullPointerException :
    public elw::Exception
{
public:
    NullPointerException(const std::string& str = "") :
        elw::Exception("NullPointerException<" + str + ">")
    {
    }
};

template <class _Ty>
class SmartPtr
{
    _Ty* m_pPtr;
    elw::AtomicCounter* m_pCounter;
public:

    SmartPtr(void) :
        m_pPtr(NULL)
    {
        m_pCounter = new elw::AtomicCounter(1);
    }

    SmartPtr(const _Ty* pPtr, int iRefCnt = 1) :
        m_pPtr(const_cast<_Ty*>(pPtr))
    {
        m_pCounter = new elw::AtomicCounter(iRefCnt);
    }

    SmartPtr(const SmartPtr& rThat) :
        m_pPtr(rThat.m_pPtr),
        m_pCounter(rThat.m_pCounter)
    {
        ++*m_pCounter;
    }

    SmartPtr(const _Ty* pPtr, elw::AtomicCounter* pCounter) :
        m_pPtr(const_cast<_Ty*>(pPtr)),
        m_pCounter(pCounter)
    {
        ++*m_pCounter;
    }

    virtual ~SmartPtr(void)
    {
        if (NULL == m_pCounter)
            return;
        int iRefCnt = --(*m_pCounter);
        if (iRefCnt == 0)
        {
            delete m_pCounter;
            m_pCounter = NULL;
            if (NULL != m_pPtr)
            {
                delete m_pPtr;
                m_pPtr = NULL;
            }
        }
    }

    int count() const
    {
        return *m_pCounter;
    }

    SmartPtr& operator=(const SmartPtr& rRight)
    {
        if (this == &rRight)
            return *this;
        SmartPtr<_Ty> tmp(rRight);
        tmp.swap(*this);
        return *this;
    }

    SmartPtr<_Ty>& operator=(const _Ty* pPtr)
    {
        return (*this = SmartPtr<_Ty>(pPtr));
    }

    _Ty* operator->() const
    {
//        if (NULL == m_pPtr)
//            throw elw::NullPointerException();
        return m_pPtr;
    }

    _Ty& operator*() const
    {
//        if (NULL == m_pPtr)
//            throw elw::NullPointerException();
        return *m_pPtr;
    }

    bool operator==(const SmartPtr& rRight) const
    {
        return m_pPtr == rRight.m_pPtr;
    }

    bool operator==(const _Ty* pRight) const
    {
        return m_pPtr == pRight;
    }

    bool operator!=(const SmartPtr& rRight) const
    {
        return m_pPtr != rRight.m_pPtr;
    }

    bool operator!=(const _Ty* pRight) const
    {
        return m_pPtr != pRight;
    }

    template <class _TyNew>
    elw::SmartPtr<_TyNew> cast()
    {
        _TyNew* p = (_TyNew*)(m_pPtr);
        if (NULL == p)
            return NULL;
        elw::SmartPtr<_TyNew> ptr(p, m_pCounter);//(*this);
        return ptr;
    }

protected:
    void swap(SmartPtr& rThat)
    {
        std::swap(m_pCounter, rThat.m_pCounter);
        std::swap(m_pPtr, rThat.m_pPtr);
    }
};

END_ELW

template <class _Ty>
inline bool operator==(void* pLeft, const elw::SmartPtr<_Ty>& ptrRight)
{
    return ptrRight == (_Ty*)pLeft;
}

template <class _Ty>
inline bool operator!=(void* pLeft, const elw::SmartPtr<_Ty>& ptrRight)
{
    return ptrRight != (_Ty*)pLeft;
}


#endif /* ElwingSmartPtr_h__ */
