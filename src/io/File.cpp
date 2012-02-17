/*
 * File.cpp
 *
 *  Created on: Oct 10, 2011
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

File::File(const std::string& strPath) :
    m_pImpl(NULL),
    m_iType(0)
{
//    m_pImpl = elw::ClassFactory::instantiate<elw::IFilePolicy>(ELW_FILE_POLICY_IMPL_KEYWORD); // singelton. dont delete
    m_pImpl = (elw::IFilePolicy*)elw::CreatePolicyImpl(ELW_FILE_POLICY_IMPL_KEYWORD);
//    if (m_pImpl == NULL)
//        throw elw::ClassNotFoundException(ELW_FILE_POLICY_IMPL_KEYWORD);
    init(strPath);
}

File::~File()
{
}

void File::init(const std::string& strPath)
{
    m_strPath = strPath;
    size_t pos = m_strPath.rfind(m_pImpl->getSperator());
    if (m_strPath.length() != 1 && pos == m_strPath.length() - 1)
        m_strPath = m_strPath.substr(0, strPath.length() - 1);

    m_iType = m_pImpl->getType(m_strPath);
}

bool File::exists() const
{
    return m_iType != 0;
}

dword File::length() const
{
    return m_pImpl->getLength(m_strPath);
}

std::string File::getPath() const
{
    return m_strPath;
}

std::string File::getParent() const
{
    std::string strParent;
    size_t pos = m_strPath.rfind(m_pImpl->getSperator());
    if (pos != std::string::npos)
        strParent = m_strPath.substr(0, pos);
    return strParent;
}

std::string File::getName() const
{
    std::string strName;
    size_t pos = m_strPath.rfind(m_pImpl->getSperator());
    if (pos != std::string::npos)
        strName = m_strPath.substr(pos + 1);
    if (strName.empty())
        strName = m_strPath;
    return strName;
}

std::string File::getAbsolutePath() const
{
    std::string strRslt;
    if (!isAbsolutePath())
    {
        strRslt = elw::File::getwd() + '/' + m_strPath;
    }
    else
    {
        strRslt = m_strPath;
    }

    return strRslt;
}

std::string File::getCanonicalPath() const
{
    std::string strRslt;
    if (!exists())
    {
        strRslt = getAbsolutePath();
    }
    else
    {
        m_pImpl->realPath(m_strPath, strRslt);
    }

    return strRslt;
}

bool File::isAbsolutePath() const
{
    size_t npos = m_strPath.find(m_pImpl->getRoot());
    if (npos != 0)
        return false;
    return true;
}

bool File::isDirectory() const
{
    if (!exists())
        return false;
    return ((m_iType & elw::iobase::dir) == elw::iobase::dir);
}

bool File::isLink() const
{
    if (!exists())
        return false;
    return ((m_iType & elw::iobase::link) == elw::iobase::link);
}

bool File::isFile() const
{
    if (!exists())
        return false;
    return ((m_iType & elw::iobase::file) == elw::iobase::file);
}

bool File::isDevice() const
{
    if (!exists())
        return false;
    return ((m_iType & elw::iobase::dev) == elw::iobase::dev);
}

bool File::isHidden() const
{
    if (!exists())
        return false;
    return ((m_iType & elw::iobase::headen) == elw::iobase::headen);
}

bool File::canRead() const
{
    if (!exists())
        return false;
    return m_pImpl->canRead(m_strPath);
}

bool File::canWrite() const
{
    if (!exists())
        return false;
    return m_pImpl->canWrite(m_strPath);
}

bool File::canExecute() const
{
    if (!exists())
        return false;
    return m_pImpl->canExecute(m_strPath);
}

bool File::setReadable(bool fReadable, bool fOwnerOnly)
{
    if (!exists())
        return false;
    return m_pImpl->setReadable(m_strPath, fReadable, fOwnerOnly);
}

bool File::setWritable(bool fWritable, bool fOwnerOnly)
{
    if (!exists())
        return false;
    return m_pImpl->setWritable(m_strPath, fWritable, fOwnerOnly);
}

bool File::setExecutable(bool fExecutable, bool fOwnerOnly)
{
    if (!exists())
        return false;
    return m_pImpl->setExecutable(m_strPath, fExecutable, fOwnerOnly);
}

bool File::create()
{
    if (exists())
        return false;
    if (m_pImpl->create(m_strPath))
        m_iType = m_pImpl->getType(m_strPath);
    return isFile();
}

bool File::mkdir()
{
    if (exists())
        return false;
    if (m_pImpl->mkdir(m_strPath))
        m_iType = m_pImpl->getType(m_strPath);
    return isDirectory();
}

bool File::mklink(const std::string& strTo)
{
    if (exists())
        return false;
    if (m_pImpl->mklink(m_strPath, strTo))
        m_iType = m_pImpl->getType(m_strPath);
    return isLink();
}

void File::list(std::vector<elw::File>& lst, const std::string& strFilter)
{
    std::vector<std::string> lstName;
    list(lstName, strFilter);
    std::vector<std::string>::iterator it;
    for (it = lstName.begin(); it != lstName.end(); ++it)
        lst.push_back(elw::File(m_strPath + '/' + (*it)));
}

void File::list(std::vector<std::string>& lst, const std::string& strFilter)
{
    if (isDirectory())
        m_pImpl->readDir(m_strPath, lst, strFilter);
}

std::string File::link() const
{
    std::string strRslt;
    if (isLink())
        m_pImpl->readLink(m_strPath, strRslt);
    return strRslt;
}

bool File::remove(bool fRecursive)
{
    if (!exists())
        return false;

    if (isDirectory() && fRecursive)
    {
        std::vector<elw::File> lst;
        list(lst);
        std::vector<elw::File>::iterator it;
        for (it = lst.begin(); it != lst.end(); ++it)
            (*it).remove(true);
    }

    if (m_pImpl->remove(m_strPath))
        m_iType = 0;

    return !exists();
}

bool File::move(const std::string& strDst)
{
    if (!exists())
        return false;
    if (!m_pImpl->move(m_strPath, strDst))
        return false;
    init(strDst);
    return true;
}

std::string File::getwd()
{
    return elw::GetWorkingDirectory();
}

bool File::setwd(const std::string& strPath)
{
    return elw::SetWorkingDirectory(strPath);
}

elw::SmartPtr<IInputChannel> File::openInputChannel()
{
    return new elw::FileInputChannel(*this);
}

elw::SmartPtr<IOutputChannel> File::openOutputChannel()
{
    return new elw::FileOutputChannel(*this);
}

END_ELW
