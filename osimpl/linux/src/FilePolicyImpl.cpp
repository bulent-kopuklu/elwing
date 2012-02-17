/*
 * FilePolicyImpl.cpp
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
#include "FilePolicyImpl.h"

BEGIN_ELW

std::string FilePolicyImpl::getRoot() const
{
    return "/";
}

std::string FilePolicyImpl::getSperator() const
{
    return "/";
}

int FilePolicyImpl::getType(const std::string& strPath)
{
    int iRslt = 0;
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (0 > ::lstat(strPath.c_str(), &s))
        return false;

    if (S_ISLNK(s.st_mode))
    {
        if (0 > ::stat(strPath.c_str(), &s))
            return false;
        iRslt = elw::iobase::link;
    }

    if (S_ISREG(s.st_mode))
        iRslt |= elw::iobase::file;
    else if (S_ISCHR(s.st_mode) || S_ISBLK(s.st_mode))
        iRslt |= elw::iobase::dev;
    else if (S_ISDIR(s.st_mode))
        iRslt |= elw::iobase::dir;

    std::string strName;
    size_t pos = strPath.rfind(getSperator());
    if (pos != std::string::npos)
        strName = strPath.substr(pos + 1);
    if (strName.empty())
        strName = strPath;
    if (strName[0] == '.')
        iRslt |= elw::iobase::headen;

    return iRslt;
}

dword FilePolicyImpl::getLength(const std::string& strPath) const
{
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (0 > ::stat(strPath.c_str(), &s))
        return 0;
    return s.st_size;
}

bool FilePolicyImpl::canRead(const std::string& strPath) const
{
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (0 > ::stat(strPath.c_str(), &s))
        return false;
    bool fRslt = true;
    if (::geteuid() != 0)
    {
        if (s.st_uid == ::geteuid())
        {
            fRslt  = ((S_IRUSR & s.st_mode) == S_IRUSR);
        }
        else if (s.st_gid == ::getegid())
        {
            fRslt = ((S_IRGRP & s.st_mode) == S_IRGRP);
        }
        else
        {
            fRslt = ((S_IROTH & s.st_mode) == S_IROTH);
        }
    }

    return fRslt;
}

bool FilePolicyImpl::canWrite(const std::string& strPath) const
{
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (0 > ::stat(strPath.c_str(), &s))
        return false;
    bool fRslt = true;
    if (::geteuid() != 0)
    {
        if (s.st_uid == ::geteuid())
        {
            fRslt  = ((S_IWUSR & s.st_mode) == S_IWUSR);
        }
        else if (s.st_gid == ::getegid())
        {
            fRslt = ((S_IWGRP & s.st_mode) == S_IWGRP);
        }
        else
        {
            fRslt = ((S_IWOTH & s.st_mode) == S_IWOTH);
        }
    }

    return fRslt;
}

bool FilePolicyImpl::canExecute(const std::string& strPath) const
{
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (0 > ::stat(strPath.c_str(), &s))
        return false;
    bool fRslt = true;
    if (::geteuid() == 0 || s.st_uid == ::geteuid())
    {
        fRslt  = ((S_IXUSR & s.st_mode) == S_IXUSR);
    }
    else if (s.st_gid == ::getegid())
    {
        fRslt = ((S_IXGRP & s.st_mode) == S_IXGRP);
    }
    else
    {
        fRslt = ((S_IXOTH & s.st_mode) == S_IXOTH);
    }

    return fRslt;
}

bool FilePolicyImpl::setReadable(const std::string& strPath, bool fReadable, bool fOwnerOnly)
{
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (0 > ::stat(strPath.c_str(), &s))
        return false;
    mode_t m;
    if (fReadable)
    {
        m = s.st_mode | (S_IRUSR | S_IRGRP | S_IROTH);
        if (fOwnerOnly)
            m &= ~(S_IRGRP | S_IROTH);
    }
    else
    {
        m = s.st_mode & ~(S_IRUSR | S_IRGRP | S_IROTH);
    }

    if (s.st_mode == m)
        return true;

    return (0 == ::chmod(strPath.c_str(), m));
}

bool FilePolicyImpl::setWritable(const std::string& strPath, bool fWritable, bool fOwnerOnly)
{
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (0 > ::stat(strPath.c_str(), &s))
        return false;
    mode_t m;
    if (fWritable)
    {
        m = s.st_mode | (S_IWUSR | S_IWGRP | S_IWOTH);
        if (fOwnerOnly)
            m &= ~(S_IWGRP | S_IWOTH);
    }
    else
    {
        m = s.st_mode & ~(S_IWUSR | S_IWGRP | S_IWOTH);
    }

    if (s.st_mode == m)
        return true;

    return (0 == ::chmod(strPath.c_str(), m));
}

bool FilePolicyImpl::setExecutable(const std::string& strPath, bool fExecutable, bool fOwnerOnly)
{
    struct stat s;
    memset(&s, 0, sizeof(s));
    if (0 > ::stat(strPath.c_str(), &s))
        return false;
    mode_t m;
    if (fExecutable)
    {
        m = s.st_mode | (S_IXUSR | S_IXGRP | S_IXOTH);
        if (fOwnerOnly)
            m &= ~(S_IXGRP | S_IXOTH);
    }
    else
    {
        m = s.st_mode & ~(S_IXUSR | S_IXGRP | S_IXOTH);
    }

    if (s.st_mode == m)
        return true;

    return (0 == ::chmod(strPath.c_str(), m));
}

bool FilePolicyImpl::create(const std::string& strPath)
{
    int ifd = ::open(strPath.c_str(),
            O_WRONLY | O_CREAT | O_EXCL,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
            );
    if (ifd < 0)
        return false;
    ::close(ifd);
    return true;
}

bool FilePolicyImpl::mklink(const std::string& strSrc, const std::string& strDst)
{
    return (0 == ::symlink(strDst.c_str(), strSrc.c_str()));
}

bool FilePolicyImpl::mkdir(const std::string& strPath)
{
    return (0 == ::mkdir(strPath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO));
}

bool FilePolicyImpl::remove(const std::string& strPath)
{
    return (0 == ::remove(strPath.c_str()));
}

bool FilePolicyImpl::move(const std::string& strPath, const std::string& strDst)
{
    return (0 == ::rename(strPath.c_str(), strDst.c_str()));
}

bool FilePolicyImpl::readLink(const std::string& strSrc, std::string& strLink)
{
    char sz[PATH_MAX+1] = { 0 };
    if (0 > ::readlink(strSrc.c_str(), sz, sizeof(sz)))
        return false;
    strLink = sz;
    return true;
}

void FilePolicyImpl::readDir(const std::string& strPath, std::vector<std::string>& lst, const std::string& strFilter)
{
    std::string strLeft;
    std::string strRight;
    if (!strFilter.empty())
    {
        size_t pos = strFilter.find("*");
        if (pos == 0)
        {
            strLeft = "";
            strRight = strFilter.substr(1);
        }
        else if (pos > 0 && pos < strFilter.size()-1)
        {
            strLeft = strFilter.substr(0, pos);
            strRight = strFilter.substr(pos+1);
        }
        else if (pos == strFilter.size()-1)
        {
            strLeft = strFilter.substr(0, pos);
            strRight = "";
        }
        else if (pos == std::string::npos)
        {
            strLeft = strFilter;
            strRight = strFilter;
        }
    }

    DIR* pDir = ::opendir(strPath.c_str());
    if (pDir != NULL)
    {
        struct dirent* pEntry = NULL;
        while ((pEntry = ::readdir(pDir)) != NULL)
        {
            std::string str(pEntry->d_name);
            if (str == "." || str == "..")
                continue;

            bool fAdd = true;
            if (!strLeft.empty())
            {
                size_t pos = str.find(strLeft);
                if (pos == std::string::npos || pos != 0)
                    fAdd = false;
            }

            if (fAdd && !strRight.empty())
            {
                size_t pos = str.rfind(strRight);
                if (pos == std::string::npos)
                    fAdd = false;
            }

            if (fAdd)
                lst.push_back(str);
        }

        ::closedir(pDir);
    }
}

bool FilePolicyImpl::realPath(const std::string& strPath, std::string& strReal)
{
    char sz[PATH_MAX+1] = { 0 };
    if (NULL == ::realpath(strPath.c_str(), sz))
        return false;
    strReal = sz;
    return true;
}

std::string GetWorkingDirectory()
{
    char sz[PATH_MAX+1] = { 0 };
    return ::getcwd(sz, sizeof(sz));
}

bool SetWorkingDirectory(const std::string& str)
{
    return 0 == ::chdir(str.c_str());
}

//REGISTER_ELW_FILE_POLICY_IMPL(FilePolicyImpl);

END_ELW
