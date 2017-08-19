// Copyright [2013] Shawn

#include"AgendaService.h"
#include <functional>
#include <list>
#include"Meeting.h"
#include"Date.h"
#include"User.h"

std::function<bool(const User &)> AgendaService::userMatchFunction(
        const std::string & userName) {
    return std::function<bool(const User &)>(
            [userName](const User & user) {
                return user.getName() == userName;
            });
}

std::function<bool(const User &)> AgendaService::userMatchFunction(
        const std::string & userName, const std::string & password) {
    return std::function<bool(const User &)>(
            [userName, password](const User & user) {
                return user.getName() == userName &&
                       user.getPassword() == password;
            });
}

std::function<bool(const Meeting &)>
AgendaService::meetingMatchFunction_by_title(
        const std::string & userName, const std::string & title) {
    return std::function<bool(const Meeting &)>(
            [userName, title](const Meeting & meeting) {
                return meeting.getTitle() == title &&
                       (meeting.getSponsor() == userName ||
                        meeting.getParticipator() == userName);
            });
}

std::function<bool(const Meeting &)>
AgendaService::meetingMatchFunction_by_date(const std::string & userName,
        const std::string & startDate, const std::string & endDate) {
    return std::function<bool(const Meeting &)>(
            [userName, startDate, endDate](const Meeting & meeting) {
                return meeting.getStartDate() <= Date::stringToDate(endDate) &&
                       meeting.getEndDate() >= Date::stringToDate(startDate) &&
                       (meeting.getSponsor() == userName ||
                        meeting.getParticipator() == userName);
            });
}

std::function<bool(const Meeting &)>
AgendaService::meetingMatchFunction_by_sponsor(const std::string & sponsor) {
    return std::function<bool(const Meeting &)>(
            [sponsor](const Meeting & meeting) {
                return meeting.getSponsor() == sponsor;
            });
}

std::function<bool(const Meeting &)>
AgendaService::meetingMatchFunction_by_participator(
        const std::string & participator) {
    return std::function<bool(const Meeting &)>(
            [participator](const Meeting & meeting) {
                return meeting.getParticipator() == participator;
            });
}

bool AgendaService::userExists(const std::string & userName) {
    return _storage->queryUser(userMatchFunction(userName)).size() > 0;
}

AgendaService::AgendaService() {
    _storage = Storage::getInstance();
}

AgendaService::~AgendaService() {
    _storage->sync();
}

bool AgendaService::userLogIn(const std::string & userName,
                               const std::string & password) {
    return _storage->queryUser(userMatchFunction(userName, password)).size()
            > 0;
}

bool AgendaService::userRegister(const std::string & userName,
                                 const std::string & password, 
                                 const std::string & email,
                                 const std::string & phone) {
    if (!userExists(userName)) {
        _storage->createUser(User(userName, password, email, phone));
        return true;
    }
    return false;
}

bool AgendaService::deleteUser(const std::string & userName,
                               const std::string & password) {
    if (_storage->deleteUser(userMatchFunction(userName, password)) > 0) {
        _storage->deleteMeeting(
                [userName](const Meeting & meeting) {
                    return meeting.getSponsor() == userName ||
                           meeting.getParticipator() == userName;
                });
        return true;
    }
    return false;
}

std::list<User> AgendaService::listAllUsers() const {
    return _storage->queryUser([](const User & user) { return true; });
}

bool AgendaService::createMeeting(const std::string & userName,
        const std::string & title, const std::string & participator,
        const std::string & startDate, const std::string & endDate) {
    if (_storage->queryMeeting([title](const Meeting & meeting) {
                return meeting.getTitle() == title; }).size() > 0)
        return false;
    if (_storage->queryUser(userMatchFunction(participator)).size() == 0)
        return false;
    Date sDate = Date::stringToDate(startDate);
    Date eDate = Date::stringToDate(endDate);
    if (!Date::isValid(sDate) || !Date::isValid(eDate) || eDate <= sDate)
        return false;
    std::list<Meeting> sponsorMeetings = listAllMeetings(userName);
    std::list<Meeting> participatorMeetings = listAllMeetings(participator);
    std::list<Meeting>::iterator it;
    for (it = sponsorMeetings.begin(); it != sponsorMeetings.end(); ++it)
        if (Date::conflict(sDate, eDate, it->getStartDate(), it->getEndDate()))
            return false;
    for (it = participatorMeetings.begin();
         it != participatorMeetings.end(); ++it)
        if (Date::conflict(sDate, eDate, it->getStartDate(), it->getEndDate()))
            return false;
    _storage->createMeeting(
            Meeting(userName, participator, sDate, eDate, title));
    return true;
}

std::list<Meeting> AgendaService::meetingQuery(
        const std::string & userName, const std::string & title) {
    return _storage->queryMeeting(
            meetingMatchFunction_by_title(userName, title));
}

std::list<Meeting> AgendaService::meetingQuery(const std::string & userName,
        const std::string & startDate, const std::string & endDate) {
    return _storage->queryMeeting(
            meetingMatchFunction_by_date(userName, startDate, endDate));
}

std::list<Meeting> AgendaService::listAllMeetings(
        const std::string & userName) {
    std::list<Meeting> result = listAllSponsorMeetings(userName);
    std::list<Meeting> temp = listAllParticipateMeetings(userName);
    std::list<Meeting>::iterator it;
    for (it = temp.begin(); it != temp.end(); ++it)
        result.push_back(*it);
    return result;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(
        const std::string & userName) {
    return _storage->queryMeeting(meetingMatchFunction_by_sponsor(userName));
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string & userName) {
    return _storage->queryMeeting(
            meetingMatchFunction_by_participator(userName));
}

bool AgendaService::deleteMeeting(const std::string & userName,
        const std::string & title) {
    return _storage->deleteMeeting(
            [userName, title](const Meeting &meeting) {
                return meeting.getSponsor() == userName &&
                       meeting.getTitle() == title;
            }) > 0;
}

bool AgendaService::deleteAllMeetings(const std::string & userName) {
    return _storage->deleteMeeting(
            meetingMatchFunction_by_sponsor(userName)) > 0;
}

void AgendaService::startAgenda() {
}

void AgendaService::quitAgenda() {
}

