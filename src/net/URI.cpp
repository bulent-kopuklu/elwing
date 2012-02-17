
/*
 * URI.cpp
 *
 *  Created on : 2011/08/19  1:11
 *      Author : Bulent Kopuklu
 *      Contact: bulent.kopuklu@gmail.com
 */


#include "stdafx.h"

BEGIN_ELW

URI::URI(void) :
    m_wPort(0)
{
}

URI::URI(const std::string& strURI) :
    m_strURI(strURI),
    m_wPort(0)
{
    parse(strURI);
}

URI::~URI(void)
{
}

std::string URI::toString() const
{
    return m_strURI;
}

URI& URI::operator =(const std::string& strURI)
{
    clear();
    m_strURI = strURI;
    parse(strURI);
    return *this;
}

static size_t scan(
    const std::string::iterator itb,
    const std::string::iterator ite,
    const std::string& strError,
    const std::string& strStop
    )
{
    size_t nRslt = std::string::npos;
    size_t nCrnt = 0;
    for (std::string::iterator it = itb; it != ite; ++it, ++nCrnt)
    {
        if (!strError.empty())
        {
            if (std::string::npos != strError.find((*it)))
                break;
        }

        if (std::string::npos != strStop.find((*it)))
        {
            nRslt = nCrnt;
            break;
        }
    }

    return nRslt;
}

bool URI::parseAuthority(std::string& str)
{ // [ userinfo "@" ] host [ ":" port ]

    size_t npos = scan(str.begin(), str.end(), "", "]");
    if (npos != std::string::npos)
        return false;

    npos = scan(str.begin(), str.end(), "/?#", "@");
    if (npos != std::string::npos)
    { // user info
        m_strUserInfo = str.substr(0, npos);
        str = str.substr(npos+1);
    }

    // host
    npos = scan(str.begin(), str.end(), "/?#", ":");
    if (npos != std::string::npos)
    {
        m_strHost = str.substr(0, npos);
        m_wPort = (word) atoi(str.substr(npos+1).c_str());
    }
    else
    {
        m_strHost = str;
    }

    return true;
}

bool URI::parseHierarchical(std::string& str)
{ // [//authority]<path>[?<query>]
    if ('/' == str.at(0) && '/' == str.at(1))
    {
        str = str.substr(2);
        size_t npos = scan(str.begin(), str.end(), "", "/?#");
        if (npos != std::string::npos)
        {
            std::string str0 = str.substr(0, npos);
            parseAuthority(str0);
            str = str.substr(npos);
        }
    }

    size_t npos = scan(str.begin(), str.end(), "", "?#");
    size_t nmax = npos == std::string::npos ? str.length() : npos;
    m_strPath = str.substr(0, nmax);
    str = str.substr(nmax);
    if (!str.empty())
    {
        npos = scan(str.begin(), str.end(), "", "#");
        m_strQuery = str.substr(0, npos);
        str = str.substr(npos);
    }

    if (!str.empty())
    {
        m_strFragment = str;
        str = "";
    }

    return true;
}

bool URI::parse(const std::string& strURI)
{ // [<scheme>:]<scheme-specific-part>[#<fragment>]
    std::string strTemp(strURI);
    size_t npos = scan(strTemp.begin(), strTemp.end(), "/?#", ":");
    if (npos != std::string::npos)
    {
        m_strScheme = strTemp.substr(0, npos);
        strTemp = strTemp.substr(npos+1); // :
        if (strTemp.empty())
            return false;
    }

    parseHierarchical(strTemp);
    if (!strTemp.empty())
        std::cout << strTemp << std::endl;

    return true;
}

void URI::clear()
{
    m_strURI.clear();
    m_strScheme.clear();
    m_strUserInfo.clear();
    m_strHost.clear();
    m_wPort = 0;
    m_strPath.clear();
    m_strQuery.clear();
    m_strFragment.clear();
}

END_ELW
