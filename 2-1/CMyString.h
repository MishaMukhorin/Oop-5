//
// Created by mrLogic on 5/16/2024.
//

#pragma once
#include <cstring>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

class CMyString
{
public:
    CMyString();

    explicit CMyString(const char* pString);

    CMyString(const char* pString, size_t length);

    CMyString(CMyString const& other);

    CMyString(CMyString&& other) noexcept;

    explicit CMyString(std::string const& stlString);

    ~CMyString();

    CMyString& operator=(CMyString const& other);
    CMyString& operator=(CMyString&& other) noexcept;

    // Concatenation operators
    CMyString operator+(CMyString const& other) const;
    CMyString operator+(std::string const& stlString) const;
    friend CMyString operator+(std::string const& stlString, CMyString const& myString);
    friend CMyString operator+(const char* pString, CMyString const& myString);
    CMyString& operator+=(CMyString const& other);

    // Comparison operators
    bool operator==(CMyString const& other) const;
    bool operator!=(CMyString const& other) const;
    bool operator<(CMyString const& other) const;
    bool operator>(CMyString const& other) const;
    bool operator<=(CMyString const& other) const;
    bool operator>=(CMyString const& other) const;

    char& operator[](size_t index);
    char const& operator[](size_t index) const;

    [[nodiscard]] size_t GetLength() const;

    [[nodiscard]] const char* GetStringData() const;

    [[nodiscard]] CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

    void Clear();

    [[nodiscard]] size_t GetCapacity() const;

    friend std::ostream& operator<<(std::ostream& os, CMyString const& myString);
    friend std::istream& operator>>(std::istream& is, CMyString& myString);

    class Iterator;
    class ConstIterator;
    class ReverseIterator;
    class ConstReverseIterator;

    // iterators
    Iterator begin();
    Iterator end();
    [[nodiscard]] ConstIterator begin() const;
    [[nodiscard]] ConstIterator end() const;
    [[nodiscard]] ConstIterator cbegin() const;
    [[nodiscard]] ConstIterator cend() const;
    ReverseIterator rbegin();
    ReverseIterator rend();
    [[nodiscard]] ConstReverseIterator rbegin() const;
    [[nodiscard]] ConstReverseIterator rend() const;
    [[nodiscard]] ConstReverseIterator crbegin() const;
    [[nodiscard]] ConstReverseIterator crend() const;

private:
    void Resize(size_t newCapacity);
    static char s_emptyString[1];
    size_t m_length;
    size_t m_capacity;
    char* m_pData;
};


// operators out of the class

CMyString operator+(std::string const& stlString, CMyString const& myString);
CMyString operator+(const char* pString, CMyString const& myString);


// Iterator classes
class CMyString::Iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = char;
    using difference_type = ptrdiff_t;
    using pointer = char*;
    using reference = char&;

    explicit Iterator(char* ptr) : m_ptr(ptr) {}

    reference operator*() { return *m_ptr; }
    Iterator& operator++() { ++m_ptr; return *this; } //todo out of range
    Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }
    Iterator& operator--() { --m_ptr; return *this; }
    Iterator operator--(int) { Iterator temp = *this; --(*this); return temp; }

    bool operator==(const Iterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const Iterator& other) const { return m_ptr != other.m_ptr; }

    Iterator operator+(size_t n) const { return Iterator(m_ptr + n); }
    Iterator operator-(size_t n) const { return Iterator(m_ptr - n); }
    difference_type operator-(const Iterator& other) const { return m_ptr - other.m_ptr; }
    reference operator[](size_t index) { return m_ptr[index]; }

private:
    char* m_ptr;
};

class CMyString::ConstIterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = const char;
    using difference_type = ptrdiff_t;
    using pointer = const char*;
    using reference = const char&;

    explicit ConstIterator(const char* ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    ConstIterator& operator++() { ++m_ptr; return *this; }
    ConstIterator operator++(int) { ConstIterator temp = *this; ++(*this); return temp; }
    ConstIterator& operator--() { --m_ptr; return *this; }
    ConstIterator operator--(int) { ConstIterator temp = *this; --(*this); return temp; }

    bool operator==(const ConstIterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const ConstIterator& other) const { return m_ptr != other.m_ptr; }

    ConstIterator operator+(size_t n) const { return ConstIterator(m_ptr + n); }
    ConstIterator operator-(size_t n) const { return ConstIterator(m_ptr - n); }
    difference_type operator-(const ConstIterator& other) const { return m_ptr - other.m_ptr; }
    reference operator[](size_t index) const { return m_ptr[index]; }

private:
    const char* m_ptr;
};

class CMyString::ReverseIterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = char;
    using difference_type = ptrdiff_t;
    using pointer = char*;
    using reference = char&;

    explicit ReverseIterator(char* ptr) : m_ptr(ptr) {}

    reference operator*() { return *m_ptr; }
    ReverseIterator& operator++() { --m_ptr; return *this; }
    ReverseIterator operator++(int) { ReverseIterator temp = *this; --(*this); return temp; }
    ReverseIterator& operator--() { ++m_ptr; return *this; }
    ReverseIterator operator--(int) { ReverseIterator temp = *this; ++(*this); return temp; }

    bool operator==(const ReverseIterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const ReverseIterator& other) const { return m_ptr != other.m_ptr; }

    ReverseIterator operator+(size_t n) const { return ReverseIterator(m_ptr - n); }
    ReverseIterator operator-(size_t n) const { return ReverseIterator(m_ptr + n); }
    difference_type operator-(const ReverseIterator& other) const { return other.m_ptr - m_ptr; }
    reference operator[](size_t index) { return *(m_ptr - index); }

private:
    char* m_ptr;
};

class CMyString::ConstReverseIterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = const char;
    using difference_type = ptrdiff_t;
    using pointer = const char*;
    using reference = const char&;

    explicit ConstReverseIterator(const char* ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    ConstReverseIterator& operator++() { --m_ptr; return *this; }
    ConstReverseIterator operator++(int) { ConstReverseIterator temp = *this; --(*this); return temp; }
    ConstReverseIterator& operator--() { ++m_ptr; return *this; }
    ConstReverseIterator operator--(int) { ConstReverseIterator temp = *this; ++(*this); return temp; }

    bool operator==(const ConstReverseIterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const ConstReverseIterator& other) const { return m_ptr != other.m_ptr; }

    ConstReverseIterator operator+(size_t n) const { return ConstReverseIterator(m_ptr - n); }
    ConstReverseIterator operator-(size_t n) const { return ConstReverseIterator(m_ptr + n); }
    difference_type operator-(const ConstReverseIterator& other) const { return other.m_ptr - m_ptr; }
    reference operator[](size_t index) const { return *(m_ptr - index); }

private:
    const char* m_ptr;
};

