// Copyright [2013] Shawn

#ifndef __AGENDAUI_H__
#define __AGENDAUI_H__

#include"AgendaService.h"
#include <iostream>
#include <string>

class AgendaUI {
    public:
        AgendaUI();
        void OperationLoop();

    private:
        int max(const int &, const size_t &);
        void showMenu_notLogged();
        void showMenu_logged();
        bool is_vaild(const std::string &);
        void showInvaildOperation();
        void startAgenda();
        std::string getOperation();
        bool executeOperation(const std::string &);
        void userLogIn();
        void userRegister();
        void quitAgenda();
        void userLogOut();
        void deleteUser();
        void listAllUsers();
        void createMeeting();
        void listAllMeetings();
        void listAllSponsorMeetings();
        void listAllParticipateMeetings();
        void queryMeetingByTitle();
        void queryMeetingByTimeInterval();
        void deleteMeetingByTitle();
        void deleteAllMeetings();
        void QB();
        void printMeetings(const std::list<Meeting> &);

        std::string _userName;
        std::string _userPassword;
        AgendaService _agendaService;
};

#endif

