//
// Created by mrLogic on 5/16/2024.
//
#include "CMyString.h"

char CMyString::s_emptyString[1] = { '\0' };

CMyString::CMyString()
        : m_length(0), m_capacity(1), m_pData(s_emptyString)
{
}

CMyString::CMyString(const char* pString)
        : CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
        : m_length(length), m_capacity(length + 1), m_pData(new char[m_capacity])
{
    memcpy(m_pData, pString, length);
    m_pData[m_length] = '\0';
}

CMyString::CMyString(CMyString const& other)
        : m_length(other.m_length), m_capacity(other.m_capacity), m_pData(new char[other.m_capacity])
{
    memcpy(m_pData, other.m_pData, m_length + 1);
}

CMyString::CMyString(CMyString&& other) noexcept
        : m_length(other.m_length), m_capacity(other.m_capacity), m_pData(other.m_pData)
{
    other.m_length = 0;
    other.m_capacity = 1;
    other.m_pData = s_emptyString;
}

CMyString::CMyString(std::string const& stlString)
        : CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
    if (m_pData != s_emptyString)
    {
        delete[] m_pData;
    }
}

CMyString& CMyString::operator=(CMyString const& other)
{
    if (this != &other)
    {
        CMyString tmp(other);
        std::swap(m_length, tmp.m_length);
        std::swap(m_capacity, tmp.m_capacity);
        std::swap(m_pData, tmp.m_pData);
    }
    return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
    if (this != &other)
    {
        if (m_pData != s_emptyString)
        {
            delete[] m_pData;
        }
        m_length = other.m_length;
        m_capacity = other.m_capacity;
        m_pData = other.m_pData;
        other.m_length = 0;
        other.m_capacity = 1;
        other.m_pData = s_emptyString;
    }
    return *this;
}

// Concatenation operators
CMyString CMyString::operator+(CMyString const& other) const
{
    CMyString result;
    result.m_length = m_length + other.m_length;
    result.m_capacity = result.m_length + 1;
    result.m_pData = new char[result.m_capacity];
    memcpy(result.m_pData, m_pData, m_length);
    memcpy(result.m_pData + m_length, other.m_pData, other.m_length + 1);
    return result;
}

CMyString CMyString::operator+(std::string const& stlString) const
{
    CMyString result;
    result.m_length = m_length + stlString.length();
    result.m_capacity = result.m_length + 1;
    result.m_pData = new char[result.m_capacity];
    memcpy(result.m_pData, m_pData, m_length);
    memcpy(result.m_pData + m_length, stlString.c_str(), stlString.length() + 1);
    return result;
}


CMyString operator+(std::string const& stlString, CMyString const& myString)
{
    return CMyString(stlString.c_str()) + myString;
}

CMyString operator+(const char* pString, CMyString const& myString)
{
    return CMyString(pString) + myString;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
    if (m_length + other.m_length + 1 > m_capacity)
    {
        Resize((m_length + other.m_length + 1) * 2);
    }
    memcpy(m_pData + m_length, other.m_pData, other.m_length + 1);
    m_length += other.m_length;
    return *this;
}

// Comparison operators
bool CMyString::operator==(CMyString const& other) const
{
    return m_length == other.m_length && strcmp(m_pData, other.m_pData) == 0;
}

bool CMyString::operator!=(CMyString const& other) const
{
    return !(*this == other);
}

bool CMyString::operator<(CMyString const& other) const
{
    return strcmp(m_pData, other.m_pData) > 0;
}
//todo check "ckdkd\0dd"

bool CMyString::operator>(CMyString const& other) const
{
    return strcmp(m_pData, other.m_pData) < 0;
}

bool CMyString::operator<=(CMyString const& other) const
{
    return !(*this > other);
}

bool CMyString::operator>=(CMyString const& other) const
{
    return !(*this < other);
}

char& CMyString::operator[](size_t index)
{
    if (index >= m_length)
        throw std::range_error("CMyString out of range");

    return m_pData[index];
}

char const& CMyString::operator[](size_t index) const
{
    if (index >= m_length)
        throw std::range_error("CMyString out of range");

    return m_pData[index];
}

size_t CMyString::GetLength() const
{
    return m_length;
}

const char* CMyString::GetStringData() const
{
    return m_pData;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
    if (start >= m_length)
    {
        return {};
    }
    length = std::min(length, m_length - start); // todo обработать вариант когда строка длиннее
    return {m_pData + start, length};
}

void CMyString::Clear()
{
    m_length = 0;
    m_capacity = 1;
    m_pData[0] = '\0'; //todo нужно удалить остальное
}

size_t CMyString::GetCapacity() const
{
    return m_capacity;
}

std::ostream& operator<<(std::ostream& os, CMyString const& myString)
{
    os << myString.GetStringData();
    return os;
}

std::istream& operator>>(std::istream& is, CMyString& myString)
{
    std::string tmp;
    is >> tmp;
    myString = CMyString(tmp);
    return is;
}

void CMyString::Resize(size_t newCapacity)
{
    if (newCapacity > m_capacity)
    {
        char* newData = new char[newCapacity];
        memcpy(newData, m_pData, m_length + 1);
        if (m_pData != s_emptyString)
        {
            delete[] m_pData;
        }
        m_pData = newData;
        m_capacity = newCapacity;
    }
}


// Iterators
CMyString::Iterator CMyString::begin()
{
    return Iterator(m_pData);
}

CMyString::Iterator CMyString::end()
{
    return Iterator(m_pData + m_length);
}

CMyString::ConstIterator CMyString::begin() const
{
    return ConstIterator(m_pData);
}

CMyString::ConstIterator CMyString::end() const
{
    return ConstIterator(m_pData + m_length);
}

CMyString::ConstIterator CMyString::cbegin() const
{
    return ConstIterator(m_pData);
}

CMyString::ConstIterator CMyString::cend() const
{
    return ConstIterator(m_pData + m_length);
}

CMyString::ReverseIterator CMyString::rbegin()
{
    return ReverseIterator(m_pData + m_length - 1);
}

CMyString::ReverseIterator CMyString::rend()
{
    return ReverseIterator(m_pData - 1);
}

CMyString::ConstReverseIterator CMyString::rbegin() const
{
    return ConstReverseIterator(m_pData + m_length - 1);
}

CMyString::ConstReverseIterator CMyString::rend() const
{
    return ConstReverseIterator(m_pData - 1);
}

CMyString::ConstReverseIterator CMyString::crbegin() const
{
    return ConstReverseIterator(m_pData + m_length - 1);
}

CMyString::ConstReverseIterator CMyString::crend() const
{
    return ConstReverseIterator(m_pData - 1);
}


