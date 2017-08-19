// Copyright [2013] Shawn

#include"Date.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

const int Date::DAYS_LEAP[13] = {
    -1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
const int Date::DAYS_NORM[13] = {
    -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

Date::Date() {
    _year = _month = _day = _hour = _minute = 0;
}

Date::Date(const int & year, const int & month, const int & day,
           const int & hour, const int & minute) {
    _year = year;
    _month = month;
    _day = day;
    _hour = hour;
    _minute = minute;
}

int Date::getYear() const {
    return _year;
}

void Date::setYear(const int & year) {
    _year = year;
}

int Date::getMonth() const {
    return _month;
}

void Date::setMonth(const int & month) {
    _month = month;
}

int Date::getDay() const {
    return _day;
}

void Date::setDay(const int & day) {
    _day = day;
}

int Date::getHour() const {
    return _hour;
}

void Date::setHour(const int & hour) {
    _hour = hour;
}

int Date::getMinute() const {
    return _minute;
}

void Date::setMinute(const int & minute) {
    _minute = minute;
}

bool Date::isValid(const Date & date) {
    if (date._year < 1000 || date._year > 9999)
        return false;
    if (date._month < 1 || date._month > 12)
        return false;
    if (is_leap(date._year)) {
        if (date._day < 1 || date._day > DAYS_LEAP[date._month])
            return false;
    } else {
        if (date._day < 1 || date._day > DAYS_NORM[date._month])
            return false;
    }
    if (date._hour < 0 || date._hour > 23)
        return false;
    if (date._minute < 0 || date._minute > 59)
        return false;
    return true;
}

Date Date::stringToDate(const std::string & dateString) {
    std::stringstream ss;
    char temp;
    int year, month, day, hour, minute;
    ss << dateString;
    ss >> year >> temp >> month >> temp >> day >> temp
       >> hour >> temp >> minute;
    return Date(year, month, day, hour, minute);
}

std::string Date::dateToString(const Date & date) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << date._year << '-'
       << std::setfill('0') << std::setw(2) << date._month << '-'
       << std::setfill('0') << std::setw(2) << date._day << '/'
       << std::setfill('0') << std::setw(2) << date._hour << ':'
       << std::setfill('0') << std::setw(2) << date._minute;
    return ss.str();
}

Date & Date::operator=(const Date & date) {
    _year = date._year;
    _month = date._month;
    _day = date._day;
    _hour = date._hour;
    _minute = date._minute;
    return *this;
}

bool Date::operator==(const Date & date) const {
    return _year == date._year && _month == date._month &&
           _day == date._day && _hour == date._hour &&
           _minute == date._minute;
}

bool Date::operator>(const Date & date) const {
    if (_year > date._year)
        return true;
    if (_year < date._year)
        return false;
    if (_month > date._month)
        return true;
    if (_month < date._month)
        return false;
    if (_day > date._day)
        return true;
    if (_day < date._day)
        return false;
    if (_hour > date._hour)
        return true;
    if (_hour < date._hour)
        return false;
    if (_minute > date._minute)
        return true;
    return false;
}

bool Date::operator<(const Date & date) const {
    if (_year < date._year)
        return true;
    if (_year > date._year)
        return false;
    if (_month < date._month)
        return true;
    if (_month > date._month)
        return false;
    if (_day < date._day)
        return true;
    if (_day > date._day)
        return false;
    if (_hour < date._hour)
        return true;
    if (_hour > date._hour)
        return false;
    if (_minute < date._minute)
        return true;
    return false;
}

bool Date::operator>=(const Date & date) const {
    if (_year > date._year)
        return true;
    if (_year < date._year)
        return false;
    if (_month > date._month)
        return true;
    if (_month < date._month)
        return false;
    if (_day > date._day)
        return true;
    if (_day < date._day)
        return false;
    if (_hour > date._hour)
        return true;
    if (_hour < date._hour)
        return false;
    if (_minute >= date._minute)
        return true;
    return false;
}

bool Date::operator<=(const Date & date) const {
    if (_year < date._year)
        return true;
    if (_year > date._year)
        return false;
    if (_month < date._month)
        return true;
    if (_month > date._month)
        return false;
    if (_day < date._day)
        return true;
    if (_day > date._day)
        return false;
    if (_hour < date._hour)
        return true;
    if (_hour > date._hour)
        return false;
    if (_minute <= date._minute)
        return true;
    return false;
}

bool Date::is_leap(const int & year) {
    return (year%4 == 0 && year%100 != 0) || year%400 == 0;
}

bool Date::conflict(const Date & aStart, const Date & aEnd,
                    const Date & bStart, const Date & bEnd) {
    return aStart < bEnd && aEnd > bStart;
}

