//
// Created by Misha on 19.04.2024.
//

#ifndef OOP_5_CDATE_H
#define OOP_5_CDATE_H

#include <iostream>
#include <cassert>
#include <ctime>

const unsigned DAYS_IN_FOUR_YEARS = 1'461;
const unsigned DAYS_IN_YEAR = 365;
const unsigned DAYS_IN_LEAP_YEAR = 366;
const unsigned DAYS_IN_FOUR_HUNDRED_YEARS = 146'097;
const unsigned DAYS_BEFORE_2000 = 10'957;

// �����
enum Month: int
{
    JANUARY = 1, FEBRUARY = 2, MARCH = 3, APRIL = 4,
    MAY = 5, JUNE = 6, JULY = 7, AUGUST = 8, SEPTEMBER = 9,
    OCTOBER = 10, NOVEMBER = 11, DECEMBER = 12
};

// ���� ������
enum WeekDay: int
{
    SUNDAY = 0, MONDAY = 1, TUESDAY = 2, WEDNESDAY = 3,
    THURSDAY = 4, FRIDAY = 5, SATURDAY = 6
};

class CDate
{
public:
    // �������������� ���� ��������� ����, ������� � �����.
    // ����������: ��� >= 1970
    CDate(unsigned day, Month month, unsigned year)
    {
        if (year < 1970 || day > 31 || day < 1 || month < Month::JANUARY || month > Month::DECEMBER)
            throw std::invalid_argument("Invalid date");
        unsigned years = year - 1970;
        unsigned totalDays = 0;
        totalDays += years * 365 + GetNumOfLeapYearsByYear(year);
        for (int i = 1; i < (month); i++)
        {
            totalDays += s_numDays[i];
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && i == 1)
            {
                totalDays++;
            }
        }
        totalDays += day - 1;
        m_timestamp = totalDays;
    }

    // �������������� ���� ����������� ����, ��������� ����� 1 ������ 1970 ����
    explicit CDate(unsigned timestamp)
    {
        m_timestamp = timestamp;
    }

    // ����������� �� ���������. ������ ����, ������ 1 ������ 1970.
    CDate()
    {
        m_timestamp = 0;
    }

    // ���������� ���� ������ (�� 1 �� 31)
    [[nodiscard]] unsigned GetDay() const;

    // ���������� �����
    [[nodiscard]] Month GetMonth() const;

    // ���������� ���
    [[nodiscard]] unsigned GetYear() const;

    // ���������� ���� ������
    [[nodiscard]] WeekDay GetWeekDay() const;

    // ���������� ���������� � ������������ �������� ����.
    [[nodiscard]] bool IsValid() const;

    // ��������� ���� �� ��������� ����
    CDate& operator++();

    // ��������� ���� �� ��������� ���� (����������� �����)
    CDate operator++(int);

    // ��������� ���� �� ���������� ����
    CDate& operator--();

    // ��������� ���� �� ���������� ���� (����������� �����)
    CDate operator--(int);

    // ���������� � ���� �������� ����� ���������� ����
    CDate& operator+=(unsigned days);

    // �������� �� ���� �������� ����� ���������� ����
    CDate& operator-=(unsigned days);

    // ���������� �������� ���� ��� � ����
    int operator-(const CDate& rhs) const;


    // ������ ���� �� ������ ����� � ������� ��.��.����
    CDate operator>>(std::istream& is) const;

    // ��������� ��������� ���� ���
    bool operator==(const CDate& rhs) const
    {
        return m_timestamp == rhs.m_timestamp;
    }

    // ��������� ����������� ���� ���
    bool operator!=(const CDate& rhs) const
    {
        return !operator==(rhs);
    }

    // ��������� ������� ����������� ���� ���
    bool operator<(const CDate& rhs) const
    {
        return m_timestamp < rhs.m_timestamp;
    }

    // ��������� ������� ����������� ���� ���
    bool operator>(const CDate& rhs) const
    {
        return m_timestamp > rhs.m_timestamp;
    }

    // ��������� ��������� ����������� ���� ���
    bool operator<=(const CDate& rhs) const
    {
        return !operator>(rhs);
    }

    // ��������� ��������� ����������� ���� ���
    bool operator>=(const CDate& rhs) const
    {
        return !operator<(rhs);
    }

    [[nodiscard]] static unsigned GetNumOfLeapYearsBefore(unsigned numOfDays)
    {
        unsigned year = 1970;
        unsigned numOfLeapYearsBefore = 0;
        unsigned numOfYearsBefore = 0;
        unsigned i = 1;
        if (numOfDays > 365)
        {
            if (numOfDays > DAYS_BEFORE_2000)
            {
                numOfYearsBefore += 30;
                numOfLeapYearsBefore += 7;
                numOfDays -= DAYS_BEFORE_2000;
                numOfYearsBefore += numOfDays / DAYS_IN_FOUR_HUNDRED_YEARS * 400;
                numOfLeapYearsBefore += numOfDays / DAYS_IN_FOUR_HUNDRED_YEARS * 97;
                numOfDays %= DAYS_IN_FOUR_HUNDRED_YEARS;
            }
            numOfYearsBefore += numOfDays / DAYS_IN_FOUR_YEARS * 4;
            numOfLeapYearsBefore += numOfDays / DAYS_IN_FOUR_YEARS;
            numOfDays %= DAYS_IN_FOUR_YEARS;
            year += numOfYearsBefore;
            for (int j = 0; j < 3; ++j)
            {
                if (IsLeapYear(year))
                {
                    numOfDays -= DAYS_IN_LEAP_YEAR;
                    numOfLeapYearsBefore++;
                }
                else
                {
                    numOfDays -= DAYS_IN_YEAR;
                }
                year++;
            }
        }
        return numOfLeapYearsBefore;
    }

    [[nodiscard]] static unsigned GetNumOfLeapYearsByYear(unsigned year)
    {
        unsigned years = year - 1970;
        unsigned numOfLeapYearsBefore = 0;
        unsigned i = 1;

        if (years > 30)
        {
            numOfLeapYearsBefore += 7;
            years -= 30;
            numOfLeapYearsBefore += years / 400 * 97;
            years %= 400;
        }
        numOfLeapYearsBefore += years / 4;
        years %= 4;
        for (int j = 0; j < 3; ++j)
        {
            if (IsLeapYear(years + 1970))
            {
                numOfLeapYearsBefore++;
            }
            years++;
        }
        
        return numOfLeapYearsBefore;
    }

private:
    unsigned m_timestamp;

    constexpr static const unsigned s_numDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // ���������, �������� �� ��� ����������
    [[nodiscard]] static bool IsLeapYear(unsigned year)
    {
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    }
};

std::ostream& operator<<(std::ostream& os, const CDate& date);


#endif //OOP_5_CDATE_H
