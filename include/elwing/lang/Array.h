/*
 * Array.h
 *
 *  Created on: Aug 12, 2011
 *      Author: Bulent.Kopuklu
 */

#ifndef ElwingArray_h__
#define ElwingArray_h__

BEGIN_ELW

template <class _TyElem>
class BasicArray
{
    typedef _TyElem* _TyPtr;
    _TyPtr m_p;
    std::streamsize m_nLength;
    std::streamsize m_nMaxLenght;
public:
    BasicArray(uint uInitialLength = 64) :
        m_p(NULL),
        m_nLength(0),
        m_nMaxLenght(uInitialLength)
    {
        m_p = (_TyPtr) ::calloc(1, sizeOf());
    }

//    BasicArray(const BasicArray& that) :
//        m_p(NULL),
//        m_nLength(that.m_nLength),
//        m_nMaxLenght(that.m_nMaxLenght),
//    {
//        m_p = (_TyPtr) ::malloc(that.sizeOf());
//        ::memcpy(m_p, that.m_p, that.sizeOf());
//    }

//    BasicArray(_TyElem* pData, std::streamsize nSize) :
//        m_p(pData),
//        m_nLength(nSize),
//        m_nMaxLenght(nSize),
//        m_fMyPtr(false)
//    {
////        m_p = (_TyPtr) ::malloc(that.sizeOf());
////        ::memcpy(m_p, that.m_p, that.sizeOf());
//    }

    ~BasicArray()
    {
        ::free(m_p);
    }

    _TyPtr ptr() const
    {
        return m_p;
    }

    operator _TyPtr()
    {
        return m_p;
    }

    std::streamsize sizeOf() const
    {
        return m_nMaxLenght * sizeof(_TyElem);
    }

    std::streamsize length() const
    {
        return m_nLength;
    }

    void count(std::streamsize nLength)
    {
        m_nLength = nLength;
    }

    void reset()
    {
        m_nLength = 0;
    }

    bool resize(std::streamsize nNewLength)
    {
        if (nNewLength > m_nMaxLenght)
        {
            _TyPtr p = (_TyPtr)::realloc(m_p, nNewLength*sizeof(_TyElem));
            if (NULL == p)
                return false;
            m_p = p;
            m_nMaxLenght = nNewLength;
        }
        else if (nNewLength < m_nMaxLenght)
        {
            m_nMaxLenght = nNewLength;
            if (m_nLength > nNewLength)
                m_nLength = nNewLength;
        }
        else
        {
        }

        return true;
    }

    _TyElem operator[](int i)
    {
        if (i > length())
            throw elw::Exception("");
        return *(m_p+(i*sizeof(_TyElem)));
    }
};

template <class _TyCh>
inline std::basic_ostream<_TyCh>& operator <<(std::basic_ostream<_TyCh>& os, const BasicArray<_TyCh>& rBuff)
{
    if (os.good() && rBuff.length() > 0)
        os.write(rBuff.ptr(), rBuff.length());
    return os;
}

template <class _TyCh>
inline std::basic_istream<_TyCh>& operator >>(std::basic_istream<_TyCh>& is, BasicArray<_TyCh>& rBuff)
{
    if (is.good() && rBuff.sizeOf() > 0)
    {
        rBuff.reset();
        is.read(rBuff.ptr(), rBuff.sizeOf());
        rBuff.count(is.gcount());
    }

    return is;
}

typedef BasicArray<char>        CharArray;
typedef BasicArray<short>       ShortArray;
typedef BasicArray<int>         IntegerArray;
typedef BasicArray<long>        LongArray;

typedef BasicArray<char>        Buffer;

END_ELW

#endif /* ElwingArray_h__ */
