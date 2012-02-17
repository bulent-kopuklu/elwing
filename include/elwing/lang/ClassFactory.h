/*
 * ClassFactory.h
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

#ifndef ElwingClassFactory_h__
#define ElwingClassFactory_h__

BEGIN_ELW

class IAllocator :
    public elw::IInterface
{
public:
    virtual void* allocate() = 0;
};

template <class _TyBase, class _TyDerived>
class AllocatorImpl :
    public IAllocator
{
public:
    void* allocate()
    {
        _TyBase* pBase = new _TyDerived();
        return pBase;
    }
};

template <class _TyBase, class _TyDerived>
class SingeltonAllocatorImpl :
    public IAllocator
{
   _TyBase* m_pDerived;
public:
    void* allocate()
    {
        if (NULL == m_pDerived)
            m_pDerived = new _TyDerived();
        return m_pDerived;
    }

    SingeltonAllocatorImpl() :
        m_pDerived(NULL)
    {
    }

    virtual ~SingeltonAllocatorImpl()
    {
        if (NULL != m_pDerived)
        {
            delete m_pDerived;
            m_pDerived = NULL;
        }
    }
};

//////////////////////////////////////////////////////////////////////////

class Instantator
{
    IAllocator* m_pAllocator;
    bool m_fIsOverridable;
public:
    Instantator(
            IAllocator* pAllocator,
            bool fIsOverridable
            );

    virtual ~Instantator();

    bool override(
            IAllocator* pAllocator
            );
    bool isOveridable() const;

    template <class _TyBase>
    _TyBase* instantiate()
    {
        return static_cast<_TyBase*>(m_pAllocator->allocate());
    }
};

/*
template<class _TyClass>
class ClassName
{
public:
    operator std::string()
    {
        return typeid(_TyClass).name();
    }
};
*/

class ClassFactory
{
public:
    enum AllocatorType
    {
        eStandart,
        eSingelton
    };

public:
    template <class _TyBase, class _TyDerived>
    class Registrar
    {
    public:
        Registrar(const std::string& strKey, bool fIsOverridable = false, AllocatorType type = eStandart)
        {
            std::string strTypeName = "";//elw::ClassName<_TyBase>();
            strTypeName += strKey;
            Instantator* pInstantator = getStorage()[strTypeName];
            if (NULL == pInstantator)
            {
                pInstantator = new Instantator(newAllocator(type), fIsOverridable);
                if (NULL != pInstantator)
                    getStorage()[strTypeName] = pInstantator;
            }
            else
            {
                if (pInstantator->isOveridable())
                {
                    IAllocator* pAllocator = newAllocator(type);
                    if (NULL != pAllocator)
                        pInstantator->override(pAllocator);
                }
            }
        }

        IAllocator* newAllocator(AllocatorType type)
        {
            IAllocator* pAllocator = NULL;
            switch (type)
            {
            case eStandart:
                pAllocator = new AllocatorImpl<_TyBase, _TyDerived>();
                break;
            case eSingelton:
                pAllocator = new SingeltonAllocatorImpl<_TyBase,_TyDerived>();
                break;
            }

            return pAllocator;
        }
    };

public:
    template <class _TyBase>
    static _TyBase* instantiate(const std::string& strKey)
    {
        _TyBase* pRslt = NULL;
        std::string strTypeName = "";//elw::ClassName<_TyBase>();
        strTypeName += strKey;
        Instantator* pInstantator = getStorage()[strTypeName];
        if (NULL != pInstantator)
            pRslt = pInstantator->instantiate<_TyBase>();
        return pRslt;
    }

    template <class _TyBase>
    static _TyBase* unregister(const std::string& strKey)
    {
        std::string strTypeName = "";//elw::ClassName<_TyBase>();
        strTypeName += strKey;
        Instantator* pInstantator = getStorage()[strTypeName];
        getStorage().erase(strTypeName);
        delete pInstantator;
    }

protected:
    class Storage :
        public std::map<std::string, Instantator*>
    {
    public:
        virtual ~Storage();
    };

    static Storage& getStorage();
};

END_ELW

#define REGISTER_CLASS(__key, __base, __derived, __overridable, __type) \
        elw::ClassFactory::Registrar<__base, __derived> __registrar_##__base##__derived(__key, __overridable, __type)


#endif /* ElwingClassFactory_h__ */
