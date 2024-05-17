//
// Created by mrLogic on 5/16/2024.
//

#ifndef OOP_5_CDATE_H
#define OOP_5_CDATE_H

#pragma once

#include <stdexcept>
#include <iostream>
#include <string>
#include <utility>

class CDate {
public:
    enum class Month {
        JANUARY = 1, FEBRUARY, MARCH, APRIL,
        MAY, JUNE, JULY, AUGUST, SEPTEMBER,
        OCTOBER, NOVEMBER, DECEMBER
    };

    enum class WeekDay {
        SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
        THURSDAY, FRIDAY, SATURDAY
    };

    CDate(unsigned day, Month month, unsigned year);
    explicit CDate(unsigned timestamp);
    CDate();

    [[nodiscard]] unsigned GetDay() const;
    [[nodiscard]] Month GetMonth() const;
    [[nodiscard]] unsigned GetYear() const;
    [[nodiscard]] WeekDay GetWeekDay() const;

    [[nodiscard]] bool IsValid() const;

    CDate& operator++();
    CDate operator++(int);
    CDate& operator--();
    CDate operator--(int);

    CDate operator+(int days) const;
    friend CDate operator+(int days, const CDate& date);
    CDate operator-(int days) const;
    int operator-(const CDate& date) const;

    CDate& operator+=(int days);
    CDate& operator-=(int days);

    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
    friend std::istream& operator>>(std::istream& is, CDate& date);

    bool operator==(const CDate& date) const;
    bool operator!=(const CDate& date) const;
    bool operator<(const CDate& date) const;
    bool operator>(const CDate& date) const;
    bool operator<=(const CDate& date) const;
    bool operator>=(const CDate& date) const;

private:
    static constexpr unsigned START_YEAR = 1970;
    static constexpr unsigned END_YEAR = 9999;
    static constexpr unsigned MAX_DAYS_COUNT = 2932896; // 31/12/9999 is 2932896 days after 1/1/1970
    static constexpr unsigned DAYS_IN_WEEK = 7;

    unsigned m_timestamp;

    static bool IsLeapYear(unsigned year);
    static unsigned DaysInMonth(Month month, unsigned year);
    static unsigned CalculateDays(unsigned day, Month month, unsigned year);
    static unsigned CalculateDaysByYear(unsigned year);
    static std::pair<unsigned, unsigned> CalculateYearsAndRemainsDays(unsigned int year, unsigned int days);
    static std::pair<Month, unsigned> CalculateMonthAndRemainsDays(unsigned int days, unsigned year);

    [[maybe_unused]] static bool HasDivisible(unsigned int divider, unsigned start, unsigned end);
};


std::ostream& operator<<(std::ostream& os, const CDate& date);
std::istream& operator>>(std::istream& is, CDate& date);


#endif //OOP_5_CDATE_H
