// Copyright [2013] Shawn

#include"Meeting.h"
#include <string>

Meeting::Meeting() {
}

Meeting::Meeting(const std::string & sponsor,
                 const std::string & participator,
                 const Date & startDate, const Date & endDate,
                 const std::string & title) {
    _sponsor = sponsor;
    _participator = participator;
    _startDate = startDate;
    _endDate = endDate;
    _title = title;
}

std::string Meeting::getSponsor() const {
    return _sponsor;
}

void Meeting::setSponsor(const std::string & sponsor) {
    _sponsor = sponsor;
}

std::string Meeting::getParticipator() const {
    return _participator;
}

void Meeting::setParticipator(const std::string & participator) {
    _participator = participator;
}

Date Meeting::getStartDate() const {
    return _startDate;
}

void Meeting::setStartDate(const Date & startDate) {
    _startDate = startDate;
}

Date Meeting::getEndDate() const {
    return _endDate;
}

void Meeting::setEndDate(const Date & endDate) {
    _endDate = endDate;
}

std::string Meeting::getTitle() const {
    return _title;
}

void Meeting::setTitle(const std::string & title) {
    _title = title;
}

