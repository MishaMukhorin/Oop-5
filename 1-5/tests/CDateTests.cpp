//
// Created by mrLogic on 5/16/2024.
//
#include "../CDate.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(create_date_test, default_create)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::THURSDAY;

    CDate date;

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(create_date_test, create_with_timestamp)
{
    unsigned expectedDay = 6;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::TUESDAY;

    CDate date(5);

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(create_date_test, create_with_timestamp_other_month)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::FEBRUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::SUNDAY;

    CDate date(31);

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(create_date_test, create_with_timestamp_leap_year_extra_day)
{
    unsigned expectedDay = 29;
    CDate::Month expectedMonth = CDate::Month::FEBRUARY;
    unsigned expectedYear = 1972;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::TUESDAY;

    CDate date(789);

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(create_date_test, create_with_timestamp_last_day_february)
{
    unsigned expectedDay = 28;
    CDate::Month expectedMonth = CDate::Month::FEBRUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::SATURDAY;

    CDate date(58);

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(create_date_test, create_date_calendar_format)
{
    unsigned expectedDay = 30;
    CDate::Month expectedMonth = CDate::Month::JULY;
    unsigned expectedYear = 2000;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::SUNDAY;

    CDate date(expectedDay, expectedMonth, expectedYear);

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(create_date_test, create_date_calendar_format_leap_year_extra_day)
{
    unsigned expectedDay = 29;
    CDate::Month expectedMonth = CDate::Month::FEBRUARY;
    unsigned expectedYear = 1972;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::TUESDAY;

    CDate date(expectedDay, expectedMonth, expectedYear);

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(create_date_test, invalid_create_date_with_timestamp)
{
    EXPECT_THROW(CDate(3'000'000), std::invalid_argument);
    EXPECT_THROW(CDate(-1), std::invalid_argument);
}

TEST(create_date_test, invalid_create_date_calendar_format_by_year)
{
    EXPECT_THROW(CDate(10, CDate::Month::JULY, 10000), std::invalid_argument);
    EXPECT_THROW(CDate(10, CDate::Month::JULY, 1969), std::invalid_argument);
}

TEST(create_date_test, invalid_create_date_calendar_format_by_day)
{
    EXPECT_THROW(CDate(0, CDate::Month::JULY, 1970), std::invalid_argument);
    EXPECT_THROW(CDate(-1, CDate::Month::JULY, 1970), std::invalid_argument);
    EXPECT_THROW(CDate(32, CDate::Month::JULY, 1970), std::invalid_argument);
}

TEST(create_date_test, invalid_create_date_calendar_format_by_month)
{
    EXPECT_THROW(CDate(10, static_cast<CDate::Month>(0), 1970), std::invalid_argument);
    EXPECT_THROW(CDate(10, static_cast<CDate::Month>(13), 1970), std::invalid_argument);
}

TEST(logic_test, change_year)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1971;

    CDate date(31, CDate::Month::DECEMBER, 1970);
    date++;

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
}

TEST(logic_test, change_month)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::FEBRUARY;
    unsigned expectedYear = 1970;

    CDate date(31, CDate::Month::JANUARY, 1970);
    date++;

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
}

TEST(logic_test, change_month_extra_day)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::MARCH;
    unsigned expectedYear = 1972;

    CDate date(29, CDate::Month::FEBRUARY, 1972);
    date++;

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
}

TEST(unary_operation_date_test, inc_prefix)
{
    unsigned expectedDay = 2;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::FRIDAY;

    CDate date(1, expectedMonth, expectedYear);
    ++date;

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(unary_operation_date_test, inc_postfix)
{
    unsigned expectedDay = 2;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::FRIDAY;

    CDate date(1, expectedMonth, expectedYear);
    date++;

    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(unary_operation_date_test, inc_prefix_result)
{
    unsigned expectedDay = 2;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::FRIDAY;

    CDate date(1, expectedMonth, expectedYear);
    CDate temp = ++date;

    EXPECT_EQ(expectedDay, temp.GetDay());
    EXPECT_EQ(expectedMonth, temp.GetMonth());
    EXPECT_EQ(expectedYear, temp.GetYear());
    EXPECT_EQ(expectedWeekDay, temp.GetWeekDay());
}

TEST(unary_operation_date_test, inc_postfix_result)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::THURSDAY;

    CDate date(expectedDay, expectedMonth, expectedYear);
    CDate temp = date++;

    EXPECT_EQ(expectedDay, temp.GetDay());
    EXPECT_EQ(expectedMonth, temp.GetMonth());
    EXPECT_EQ(expectedYear, temp.GetYear());
    EXPECT_EQ(expectedWeekDay, temp.GetWeekDay());
}

TEST(unary_operation_date_test, inc_prefix_error)
{
    CDate date(31, CDate::Month::DECEMBER, 9999);
    EXPECT_THROW(++date, std::invalid_argument);
}

TEST(unary_operation_date_test, inc_postfix_error)
{
    CDate date(31, CDate::Month::DECEMBER, 9999);
    EXPECT_THROW(date++, std::invalid_argument);
}

TEST(unary_operation_date_test, dec_prefix)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::THURSDAY;

    CDate date(2, expectedMonth, expectedYear);
    --date;
    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(unary_operation_date_test, dec_postfix)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::THURSDAY;

    CDate date(2, expectedMonth, expectedYear);
    date--;
    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(unary_operation_date_test, dec_prefix_result)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::THURSDAY;

    CDate date(2, expectedMonth, expectedYear);
    CDate temp = --date;

    EXPECT_EQ(expectedDay, temp.GetDay());
    EXPECT_EQ(expectedMonth, temp.GetMonth());
    EXPECT_EQ(expectedYear, temp.GetYear());
    EXPECT_EQ(expectedWeekDay, temp.GetWeekDay());
}

TEST(unary_operation_date_test, dec_postfix_result)
{
    unsigned expectedDay = 2;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::FRIDAY;

    CDate date(expectedDay, expectedMonth, expectedYear);
    CDate temp = date--;

    EXPECT_EQ(expectedDay, temp.GetDay());
    EXPECT_EQ(expectedMonth, temp.GetMonth());
    EXPECT_EQ(expectedYear, temp.GetYear());
    EXPECT_EQ(expectedWeekDay, temp.GetWeekDay());
}

TEST(unary_operation_date_test, dec_prefix_error)
{
    CDate date(1, CDate::Month::JANUARY, 1970);
    EXPECT_THROW(--date, std::invalid_argument);
}

TEST(unary_operation_date_test, dec_postfix_error)
{
    CDate date(1, CDate::Month::JANUARY, 1970);
    EXPECT_THROW(date--, std::invalid_argument);
}


TEST(operation_date_test, plus_postfix)
{
    unsigned expectedDay = 5;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::MONDAY;

    CDate date(1, expectedMonth, expectedYear);
    CDate date1 = date + 4;
    EXPECT_EQ(expectedDay, date1.GetDay());
    EXPECT_EQ(expectedMonth, date1.GetMonth());
    EXPECT_EQ(expectedYear, date1.GetYear());
    EXPECT_EQ(expectedWeekDay, date1.GetWeekDay());
}

TEST(operation_date_test, plus_prefix)
{
    unsigned expectedDay = 5;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::MONDAY;

    CDate date(1, expectedMonth, expectedYear);
    CDate date1 = 4 + date;
    EXPECT_EQ(expectedDay, date1.GetDay());
    EXPECT_EQ(expectedMonth, date1.GetMonth());
    EXPECT_EQ(expectedYear, date1.GetYear());
    EXPECT_EQ(expectedWeekDay, date1.GetWeekDay());
}

TEST(operation_date_test, plus_postfix_error)
{
    CDate date(31, CDate::Month::DECEMBER, 9999);
    EXPECT_THROW(date + 1, std::invalid_argument);
}

TEST(operation_date_test, plus_prefix_error)
{
    CDate date(31, CDate::Month::DECEMBER, 9999);
    EXPECT_THROW(1 + date, std::invalid_argument);
}

TEST(operation_date_test, minus)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::THURSDAY;

    CDate date(3, expectedMonth, expectedYear);
    CDate date1 = date - 2;
    EXPECT_EQ(expectedDay, date1.GetDay());
    EXPECT_EQ(expectedMonth, date1.GetMonth());
    EXPECT_EQ(expectedYear, date1.GetYear());
    EXPECT_EQ(expectedWeekDay, date1.GetWeekDay());
}

TEST(operation_date_test, minus_error)
{
    CDate date(1, CDate::Month::JANUARY, 1970);
    EXPECT_THROW(date - 1, std::invalid_argument);
}

TEST(operation_date_test, minus_dates)
{
    unsigned expectedDay = 1;

    CDate date1(3, CDate::Month::JANUARY, 1970);
    CDate date2(2, CDate::Month::JANUARY, 1970);
    unsigned resultDays = date1 - date2;
    EXPECT_EQ(expectedDay, resultDays);
}

TEST(operation_date_test, minus_dates_negative_result)
{
    unsigned expectedDay = -1;

    CDate date1(3, CDate::Month::JANUARY, 1970);
    CDate date2(2, CDate::Month::JANUARY, 1970);
    unsigned resultDays = date2 - date1;
    EXPECT_EQ(expectedDay, resultDays);
}

TEST(operation_date_test, inc_equals)
{
    unsigned expectedDay = 5;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::MONDAY;

    CDate date(1, expectedMonth, expectedYear);
    date += 4;
    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(operation_date_test, plus_equals_error)
{
    CDate date(31, CDate::Month::DECEMBER, 9999);
    EXPECT_THROW(date += 2, std::invalid_argument);
}

TEST(operation_date_test, minus_equals)
{
    unsigned expectedDay = 1;
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;
    CDate::WeekDay expectedWeekDay = CDate::WeekDay::THURSDAY;

    CDate date(5, expectedMonth, expectedYear);
    date -= 4;
    EXPECT_EQ(expectedDay, date.GetDay());
    EXPECT_EQ(expectedMonth, date.GetMonth());
    EXPECT_EQ(expectedYear, date.GetYear());
    EXPECT_EQ(expectedWeekDay, date.GetWeekDay());
}

TEST(operation_date_test, minus_equals_error)
{
    CDate date(1, CDate::Month::JANUARY, 1970);
    EXPECT_THROW(date -= 2, std::invalid_argument);
}

TEST(bool_operation_date_test, equals_operation)
{
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;

    CDate date1(1 + 2, expectedMonth, expectedYear);
    CDate date2(1 + 2, expectedMonth, expectedYear);
    CDate date3(1 + 3, expectedMonth, expectedYear);

    EXPECT_TRUE(date1 == date2);
    EXPECT_FALSE(date1 == date3);
}

TEST(bool_operation_date_test, not_equals_operation)
{
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;

    CDate date1(1 + 2, expectedMonth, expectedYear);
    CDate date2(1 + 2, expectedMonth, expectedYear);
    CDate date3(1 + 3, expectedMonth, expectedYear);

    EXPECT_TRUE(date1 != date3);
    EXPECT_FALSE(date1 != date2);
}

TEST(bool_operation_date_test, more_operation)
{
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;

    CDate date1(4, expectedMonth, expectedYear);
    CDate date2(5, expectedMonth, expectedYear);

    EXPECT_TRUE(date1 < date2);
    EXPECT_FALSE(date2 < date1);
}

TEST(bool_operation_date_test, less_operation)
{
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;

    CDate date1(4, expectedMonth, expectedYear);
    CDate date2(5, expectedMonth, expectedYear);

    EXPECT_TRUE(date2 > date1);
    EXPECT_FALSE(date1 > date2);
}

TEST(bool_operation_date_test, more_equals_operation)
{
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;

    CDate date1(1, expectedMonth, expectedYear);
    CDate date2(2, expectedMonth, expectedYear);
    CDate date3(2, expectedMonth, expectedYear);

    EXPECT_TRUE(date1 <= date2);
    EXPECT_TRUE(date2 <= date3);
    EXPECT_FALSE(date2 <= date1);
}

TEST(bool_operation_date_test, less_equals_operation)
{
    CDate::Month expectedMonth = CDate::Month::JANUARY;
    unsigned expectedYear = 1970;

    CDate date1(1, expectedMonth, expectedYear);
    CDate date2(2, expectedMonth, expectedYear);
    CDate date3(2, expectedMonth, expectedYear);

    EXPECT_TRUE(date2 >= date1);
    EXPECT_TRUE(date3 >= date2);
    EXPECT_FALSE(date1 >= date2);
}

TEST(stream_date_test, ostream)
{
    CDate date(20, CDate::Month::JULY, 2000);
    std::ostringstream oss;
    oss << date;
    EXPECT_EQ("20.7.2000", oss.str());
}

TEST(stream_date_test, istream)
{
    std::istringstream iss("20.7.2000");
    CDate date;
    iss >> date;
    EXPECT_EQ(20, date.GetDay());
    EXPECT_EQ(CDate::Month::JULY, date.GetMonth());
    EXPECT_EQ(2000, date.GetYear());
}

GTEST_API_ int main(int argc, char** argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}