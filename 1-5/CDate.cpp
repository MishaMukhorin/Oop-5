//
// Created by Misha on 19.04.2024.
//

#include "CDate.h"

const unsigned MAX_DAYS = 2932896;

// возвращает день месяца (от 1 до 31)
[[nodiscard]] unsigned CDate::GetDay() const
{
    auto month = Month(1);
    unsigned numOfLeapYearsBefore = GetNumOfLeapYearsBefore(m_timestamp);
    unsigned days = m_timestamp;
    days -= numOfLeapYearsBefore;
    unsigned day = days % 365;
    while (day > s_numDays[month])
    {
        day -= s_numDays[month];
        month = Month(month + 1);
    }
    return day + 1;
}

// возвращает месяц
[[nodiscard]] Month CDate::GetMonth()const
{
    auto month = Month(1);
    unsigned numOfLeapYearsBefore = GetNumOfLeapYearsBefore(m_timestamp);
    unsigned days = m_timestamp;
    days -= numOfLeapYearsBefore;
    unsigned day = days % 365;
    while (day > s_numDays[month])
    {
        day -= s_numDays[month];
        month = Month(month + 1);
    }
    return month;
}

// возвращает год
[[nodiscard]] unsigned CDate::GetYear()const
{
    unsigned year = 1970;
    unsigned numOfLeapYearsBefore = GetNumOfLeapYearsBefore(m_timestamp);
    unsigned days = m_timestamp;
    days -= numOfLeapYearsBefore;
    unsigned addYear = days / 365;
    return year + addYear;
}

// возвращает день недели
[[nodiscard]] WeekDay CDate::GetWeekDay() const
{
    unsigned day = (m_timestamp + 4) % 7;
    return WeekDay(day);
}

// возвращает информацию о корректности хранимой даты.
[[nodiscard]] bool CDate::IsValid()const
{
    return m_timestamp <= MAX_DAYS;
}

// переводит дату на следующий день
CDate& CDate::operator++()
{
    m_timestamp++;
    if (!IsValid())
        m_timestamp = 0;
    return *this;
}

// переводит дату на следующий день (постфиксная форма)
CDate CDate::operator++(int)
{
    CDate temp(*this);
    ++*this;
    return temp;
}

// переводит дату на предыдущий день
CDate& CDate::operator--()
{
    m_timestamp--;
    if (!IsValid())
        m_timestamp = 0;
    return *this;
}

// переводит дату на предыдущий день (постфиксная форма)
CDate CDate::operator--(int)
{
    CDate temp(*this);
    --*this;
    return temp;
}

// прибавляет к дате заданное целое количество дней
CDate& CDate::operator+=(unsigned days)
{
    m_timestamp += days;
    if (!IsValid())
        m_timestamp = 0;
    return *this;
}

// вычитает из даты заданное целое количество дней
CDate& CDate::operator-=(unsigned days)
{
    *this += -days;
    return *this;
}

// возвращает разность двух дат в днях
int CDate::operator-(const CDate& rhs) const
{
    return static_cast<int>(m_timestamp) - static_cast<int>(rhs.m_timestamp);
}


// выводит дату в поток вывода в формате ДД.ММ.ГГГГ
std::ostream& operator<<(std::ostream& os, const CDate& date)
{
    if (!date.IsValid())
        return os << "INVALID";
    unsigned day = date.GetDay();
    Month month = date.GetMonth();
    unsigned year = date.GetYear();
    os << day << '.' << int(month) << '.' << year;
    return os;
}

// вводит дату из потока ввода в формате ДД.ММ.ГГГГ
CDate CDate::operator>>(std::istream& is) const
{
    CDate date(m_timestamp);
    int day, month, year;
    char c;
    is >> day >> c >> month >> c >> year;
    if (is)
        date = CDate(day, static_cast<Month>(month), year);
    return date;
}


int main()
{
    CDate date22(0);
    CDate date(1, Month(1), 1971);
    std::cout << date << " " << date.GetDay() << " " << date.GetMonth() << " " << date.GetYear() << std::endl;
    CDate date2(MAX_DAYS - 1);
    std::cout << date2 << " " << date2.GetDay() << " " << date2.GetMonth() << " " << date2.GetYear() << std::endl;
    CDate date3(365);
    std::cout << date3 << " " << date3.GetDay() << " " << date3.GetMonth() << " " << date3.GetYear() << std::endl;
    CDate date4(0);
    std::cout << date4 << " " << date4.GetDay() << " " << date4.GetMonth() << " " << date4.GetYear() << std::endl;
    std::cout << date22.GetWeekDay() << std::endl;
    std::cout << date.GetWeekDay() << std::endl;
    std::cout << CDate::GetNumOfLeapYearsBefore(MAX_DAYS) << std::endl;
} 