// Copyright [2013] Shawn

#ifndef __MEETING_H__
#define __MEETING_H__

#include <string>
#include"Date.h"

class Meeting {
    public:
        Meeting();
        Meeting(const std::string &, const std::string &,
                const Date &, const Date &, const std::string &);
            // sponsor participator startTime endTime title
        std::string getSponsor() const;
        void setSponsor(const std::string &);
        std::string getParticipator() const;
        void setParticipator(const std::string &);
        Date getStartDate() const;
        void setStartDate(const Date &);
        Date getEndDate() const;
        void setEndDate(const Date &);
        std::string getTitle() const;
        void setTitle(const std::string &);

    private:
        std::string _sponsor;
        std::string _participator;
        Date _startDate;
        Date _endDate;
        std::string _title;
};

#endif

