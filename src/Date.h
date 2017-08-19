// Copyright [2013] Shawn

#ifndef __DATE_H__
#define __DATE_H__

#include <string>

class Date {
    public:
        Date();
        Date(const int &, const int &, const int &, const int &, const int &);
            // year, month, day, hour, minute
        int getYear() const;
        void setYear(const int &);
        int getMonth() const;
        void setMonth(const int &);
        int getDay() const;
        void setDay(const int &);
        int getHour() const;
        void setHour(const int &);
        int getMinute() const;
        void setMinute(const int &);

        static bool isValid(const Date &);
        static Date stringToDate(const std::string &);
        static std::string dateToString(const Date &);
            // string format: yyyy-mm-dd/hh:mi

        Date & operator=(const Date &);
        bool operator==(const Date &) const;
        bool operator>(const Date &) const;
        bool operator<(const Date &) const;
        bool operator>=(const Date &) const;
        bool operator<=(const Date &) const;

        static bool conflict(const Date &, const Date &,    // aStart, aEnd
                             const Date &, const Date &);   // bStart, bEnd
    private:
        int _year;
        int _month;
        int _day;
        int _hour;
        int _minute;
        static const int DAYS_LEAP[13];
        static const int DAYS_NORM[13];
        static bool is_leap(const int &);
};

#endif

