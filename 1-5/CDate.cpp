//
// Created by mrLogic on 5/16/2024.
//

#include "CDate.h"


CDate::CDate(unsigned day, Month month, unsigned year) 
{
    if (year < START_YEAR || year > END_YEAR) 
    {
        throw std::invalid_argument("Year must be in range 1970 to 9999.");
    }
    if (day == 0 || day > DaysInMonth(month, year)) 
    {
        throw std::invalid_argument("Invalid day count in month.");
    }

    m_timestamp = CalculateDays(day, month, year);
    if (m_timestamp > MAX_DAYS_COUNT) 
    {
        throw std::invalid_argument("You can't set a date later than 31/12/9999.");
    }
}

CDate::CDate(unsigned timestamp) 
{
    if (timestamp > MAX_DAYS_COUNT) 
    {
        throw std::invalid_argument("You can't set a date later than 31/12/9999.");
    }
    m_timestamp = timestamp;
}

CDate::CDate() : m_timestamp(0) {}

unsigned CDate::GetDay() const 
{
    unsigned days = m_timestamp;
    unsigned year = START_YEAR;

    auto yearDatePack = CalculateYearsAndRemainsDays(year, days);
    auto monthDatePack = CalculateMonthAndRemainsDays(yearDatePack.second, yearDatePack.first);

    return monthDatePack.second + 1;
}

CDate::Month CDate::GetMonth() const 
{
    unsigned days = m_timestamp;
    unsigned year = START_YEAR;

    auto yearDatePack = CalculateYearsAndRemainsDays(year, days);
    auto monthDatePack = CalculateMonthAndRemainsDays(yearDatePack.second, yearDatePack.first);

    return monthDatePack.first;
}

unsigned CDate::GetYear() const 
{
    unsigned days = m_timestamp;
    unsigned year = START_YEAR;

    auto yearDatePack = CalculateYearsAndRemainsDays(year, days);

    return yearDatePack.first;
}

CDate::WeekDay CDate::GetWeekDay() const 
{
    return static_cast<WeekDay>((m_timestamp + 4) % DAYS_IN_WEEK);
}

bool CDate::IsValid() const 
{
    return m_timestamp <= MAX_DAYS_COUNT;
}

bool CDate::IsLeapYear(unsigned year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned CDate::DaysInMonth(Month month, unsigned year) 
{
    switch (month) 
{
        case Month::JANUARY: return 31;
        case Month::FEBRUARY: return IsLeapYear(year) ? 29 : 28;
        case Month::MARCH: return 31;
        case Month::APRIL: return 30;
        case Month::MAY: return 31;
        case Month::JUNE: return 30;
        case Month::JULY:
        case Month::AUGUST: return 31;
        case Month::SEPTEMBER: return 30;
        case Month::OCTOBER: return 31;
        case Month::NOVEMBER: return 30;
        case Month::DECEMBER: return 31;
        default: throw std::invalid_argument("Invalid month.");
    }
}

unsigned CDate::CalculateDays(unsigned day, Month month, unsigned year) 
{
    unsigned days = day - 1;

    days += CalculateDaysByYear(year);

    static const unsigned DAYS_IN_MONTHS[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    days += DAYS_IN_MONTHS[static_cast<unsigned>(month) - 1];

    if (month > Month::FEBRUARY) 
    {
        days += IsLeapYear(year);
    }

    return days;
}

unsigned CDate::CalculateDaysByYear(unsigned year) 
{
    unsigned yearsSinceStart = year - START_YEAR;
    unsigned leapYears = (yearsSinceStart / 4) - (yearsSinceStart / 100) + (yearsSinceStart / 400);
    return yearsSinceStart * 365 + leapYears;
}

std::pair<unsigned, unsigned> CDate::CalculateYearsAndRemainsDays(unsigned year, unsigned days) 
{
    while (days >= 365 + IsLeapYear(year)) 
    {
        days -= 365 + IsLeapYear(year);
        ++year;
    }
    return {year, days};
}

std::pair<CDate::Month, unsigned> CDate::CalculateMonthAndRemainsDays(unsigned days, unsigned year) 
{
    static const unsigned DAYS_IN_MONTHS[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    unsigned month = 1;

    for (unsigned i = 12; i >= 1; --i) 
    {
        unsigned daysInMonth = DAYS_IN_MONTHS[i - 1];
        if (i > 2) 
        {
            daysInMonth += IsLeapYear(year);
        }
        if (days >= daysInMonth) 
        {
            month = i;
            days -= daysInMonth;
            break;
        }
    }

    return {static_cast<Month>(month), days};
}

[[maybe_unused]] bool CDate::HasDivisible(unsigned int divider, unsigned start, unsigned end) 
{
    unsigned startPos = (start + divider - 1) / divider * divider;
    unsigned endPos = (end / divider) * divider;
    return startPos <= endPos;
}

CDate& CDate::operator++() 
{
    if (m_timestamp + 1 > MAX_DAYS_COUNT) 
    {
        throw std::invalid_argument("You can't increment past 31/12/9999.");
    }
    ++m_timestamp;
    return *this;
}

CDate CDate::operator++(int) 
{
    CDate temp(*this);
    ++(*this);
    return temp;
}

CDate& CDate::operator--() 
{
    if (m_timestamp == 0) 
    {
        throw std::invalid_argument("You can't decrement before 01/01/1970.");
    }
    --m_timestamp;
    return *this;
}

CDate CDate::operator--(int) 
{
    CDate temp(*this);
    --(*this);
    return temp;
}

CDate CDate::operator+(int days) const 
{
    if (m_timestamp + days > MAX_DAYS_COUNT) 
    {
        throw std::invalid_argument("Resulting date is out of range.");
    }
    return CDate(m_timestamp + days);
}

CDate operator+(int days, const CDate& date) 
{
    return date + days;
}

CDate CDate::operator-(int days) const 
{
    if (days > static_cast<int>(m_timestamp)) 
    {
        throw std::invalid_argument("Resulting date is out of range.");
    }
    return CDate(m_timestamp - days);
}

int CDate::operator-(const CDate& date) const 
{
    return static_cast<int>(m_timestamp) - static_cast<int>(date.m_timestamp);
}

CDate& CDate::operator+=(int days) 
{
    if (m_timestamp + days > MAX_DAYS_COUNT) 
    {
        throw std::invalid_argument("Resulting date is out of range.");
    }
    m_timestamp += days;
    return *this;
}

CDate& CDate::operator-=(int days) 
{
    if (days > static_cast<int>(m_timestamp)) 
    {
        throw std::invalid_argument("Resulting date is out of range.");
    }
    m_timestamp -= days;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const CDate& date) 
{
    if (date.IsValid()) 
    {
        os << date.GetDay() << "." << static_cast<int>(date.GetMonth()) << "." << date.GetYear();
    } else
    {
        os << "INVALID";
    }
    return os;
}

std::istream& operator>>(std::istream& is, CDate& date) 
{
    unsigned day, year;
    int month;
    char separator;
    is >> day >> separator >> month >> separator >> year;
    date = CDate(day, static_cast<CDate::Month>(month), year);

    return is;
}

bool CDate::operator==(const CDate& date) const 
{
    return m_timestamp == date.m_timestamp;
}

bool CDate::operator!=(const CDate& date) const 
{
    return m_timestamp != date.m_timestamp;
}

bool CDate::operator<(const CDate& date) const 
{
    return m_timestamp < date.m_timestamp;
}

bool CDate::operator>(const CDate& date) const 
{
    return m_timestamp > date.m_timestamp;
}

bool CDate::operator<=(const CDate& date) const 
{
    return m_timestamp <= date.m_timestamp;
}

bool CDate::operator>=(const CDate& date) const 
{
    return m_timestamp >= date.m_timestamp;
}
