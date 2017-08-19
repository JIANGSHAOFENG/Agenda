// Copyright [2013] Shawn

#ifndef __AGENDASERVICE_H__
#define __AGENDASERVICE_H__

#include "Storage.h"
#include <list>
#include <string>
#include <functional>

class AgendaService {
    public:
        AgendaService();
        ~AgendaService();
        bool userLogIn(const std::string &, const std::string &);
            // userName, password
        bool userRegister(const std::string &, const std::string &,
                          const std::string &, const std::string &);
            // userName, password, email, phone
        bool deleteUser(const std::string &, const std::string &);
            // userNAme, password
        std::list<User> listAllUsers() const;

        bool createMeeting(const std::string &, const std::string &,
                           const std::string &,
                           const std::string &, const std::string &);
            // userName, title, participator, startDate, endDate
        std::list<Meeting> meetingQuery(const std::string &,  // userName
                                        const std::string &); // title
        std::list<Meeting> meetingQuery(const std::string &,  // userName
                                        const std::string &,  // startDate
                                        const std::string &); // endDate
        std::list<Meeting> listAllMeetings(const std::string &); // userName
        std::list<Meeting> listAllSponsorMeetings(const std::string &);
            // userName
        std::list<Meeting> listAllParticipateMeetings(const std::string &);
            // userName
        bool deleteMeeting(const std::string &, const std::string &);
            // userName, title
        bool deleteAllMeetings(const std::string &);    // userName

        void startAgenda();
        void quitAgenda();

    private:
        Storage *_storage;
        bool userExists(const std::string &);   // userName
        std::function<bool(const User &)> userMatchFunction(
                const std::string &);   // userName
        std::function<bool(const User &)> userMatchFunction(
                const std::string &, const std::string &);
            // userName, password
        std::function<bool(const Meeting &)> meetingMatchFunction_by_title(
                const std::string &, const std::string &);
            // userName, title
        std::function<bool(const Meeting &)> meetingMatchFunction_by_date(
                const std::string &, const std::string &, const std::string &);
            // userName, startDate, endDate
        std::function<bool(const Meeting &)> meetingMatchFunction_by_sponsor(
                const std::string &);
            // sponsor
        std::function<bool(const Meeting &)>
        meetingMatchFunction_by_participator(const std::string &);
            // participator
};

#endif

