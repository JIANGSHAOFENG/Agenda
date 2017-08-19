// Copyright [2013] Shawn

#include"AgendaUI.h"
#include <string>
#include <list>
#include <iomanip>
#include <iostream>
#include"Date.h"

AgendaUI::AgendaUI() {
    startAgenda();
    _userName.clear();
    _userPassword.clear();
}

void AgendaUI::OperationLoop() {
    std::string operation;
    showMenu_notLogged();
    do {
        operation = getOperation();
        while (!is_vaild(operation)) {
            showInvaildOperation();
            operation = getOperation();
        }
    } while (executeOperation(operation));
}

int AgendaUI::max(const int & i, const size_t & s) {
    if (i < s)
        return s;
    return i;
}

void AgendaUI::showMenu_notLogged() {
    std::cout << std::string(36, '-') << " Agenda " << std::string(36, '-')
              << std::endl
              << "Action :" << std::endl
              << "m   - show menu" << std::endl
              << "l   - log in Agenda by user name and password" << std::endl
              << "r   - register an Agenda account" << std::endl
              << "q   - quit Agenda" << std::endl
              << std::string(80, '-') << std::endl << std::endl;
}

void AgendaUI::showMenu_logged() {
    std::cout << std::string(36, '-') << " Agenda " << std::string(36, '-')
              << std::endl
              << "Action :" << std::endl
              << "m   - show menu" << std::endl
              << "o   - log out Agenda" << std::endl
              << "dc  - delete Agenda account" << std::endl
              << "lu  - list all Agenda user" << std::endl
              << "cm  - create a meeting" << std::endl
              << "la  - list all meetings" << std::endl
              << "las - list all sponsor meetings" << std::endl
              << "lap - list all participate meetings" << std::endl
              << "qm  - query meeting by title" << std::endl
              << "qt  - query meeting by time interval" << std::endl
              << "dm  - delete meeting by title" << std::endl
              << "da  - delete all meetings" << std::endl
              << std::string(80, '-') << std::endl << std::endl;
}

bool AgendaUI::is_vaild(const std::string & operation) {
    if (_userName.empty())
        return operation == "l" || operation == "r" || operation == "q" ||
               operation == "m" || operation == "I have a wish";
    return operation == "o" || operation == "dc" || operation == "lu" ||
        operation == "cm" || operation == "la" || operation == "las" ||
        operation == "lap" || operation == "qm" || operation == "qt" ||
        operation == "dm" || operation == "da" || operation == "m" ||
        operation == "I have a wish";
}

void AgendaUI::showInvaildOperation() {
    std::cout << "Invaild Operation!" << std::endl;
}

void AgendaUI::startAgenda() {
    _agendaService.startAgenda();
}

std::string AgendaUI::getOperation() {
    std::string operation;
    operation.clear();
    if (_userName.empty())
        std::cout << "Agenda : ~$ ";
    else
        std::cout << "Agenda@" << _userName << " : # ";

    do {
        std::getline(std::cin, operation);
    } while (operation.empty());
    return operation;
}

bool AgendaUI::executeOperation(const std::string & operation) {
    if (operation == "l")
        userLogIn();
    else if (operation == "r")
        userRegister();
    else if (operation == "q") {
        quitAgenda();
        return false;
    }
    else if (operation == "m")
        if (_userName.empty())
            showMenu_notLogged();
        else
            showMenu_logged();
    else if (operation == "o")
        userLogOut();
    else if (operation == "dc")
        deleteUser();
    else if (operation == "lu")
        listAllUsers();
    else if (operation == "cm")
    createMeeting();
    else if (operation == "la")
        listAllMeetings();
    else if (operation == "las")
        listAllSponsorMeetings();
    else if (operation == "lap")
        listAllParticipateMeetings();
    else if (operation == "qm")
        queryMeetingByTitle();
    else if (operation == "qt")
        queryMeetingByTimeInterval();
    else if (operation == "dm")
        deleteMeetingByTitle();
    else if (operation == "I have a wish")
        QB();
    else 
        deleteAllMeetings();
    return true;
}

void AgendaUI::userLogIn() {
    std::string userName, password;
    std::cout << std::endl
              << "[log in] [user name] [password]" << std::endl
              << "[log in] ";
    std::cin >> userName >> password;
    if (_agendaService.userLogIn(userName, password)) {
        _userName = userName;
        _userPassword = password;
        std::cout << "[log in] succeed!" << std::endl << std::endl;
        showMenu_logged();
    } else {
        std::cout << "[error] log in fail!" << std::endl << std::endl;
    }
}

void AgendaUI::userRegister() {
    std::string userName, password, email, phone;
    std::cout << std::endl
              << "[register] [user name] [password] [email] [phone]"
              << std::endl << "[register] ";
    std::cin >> userName >> password >> email >> phone;
    if (_agendaService.userRegister(userName, password, email, phone))
        std::cout << "[register] succeed!" << std::endl << std::endl;
    else
        std::cout << "[error] register fail!" << std::endl << std::endl;
}

void AgendaUI::quitAgenda() {
    _agendaService.quitAgenda();
}

void AgendaUI::userLogOut() {
    _userName.clear();
    _userPassword.clear();
    showMenu_notLogged();
}

void AgendaUI::deleteUser() {
    _agendaService.deleteUser(_userName, _userPassword);
    std::cout << std::endl 
              <<"[delete agenda account] succeed!" << std::endl << std::endl;
    userLogOut();
}

void AgendaUI::listAllUsers() {
    std::list<User> users = _agendaService.listAllUsers();
    std::list<User>::iterator it;
    int l1 = 4, l2 = 5;
    for (it = users.begin(); it != users.end(); ++it) {
        l1 = max(l1, it->getName().length());
        l2 = max(l2, it->getEmail().length());
    }
    std::cout << std::endl
              << "[list all users]" << std::endl << std::endl
              << std::setfill(' ') << std::setw(l1+2) << std::left << "name"
              << std::setfill(' ') << std::setw(l2+2) << std::left << "email"
              << "phone" << std::endl;
    for (it = users.begin(); it != users.end(); ++it)
        std::cout << std::setfill(' ') << std::setw(l1+2) << std::left
                  << it->getName()
                  << std::setfill(' ') << std::setw(l2+2) << std::left
                  << it->getEmail() << it->getPhone() << std::endl;
    std::cout << std::endl;
}

void AgendaUI::createMeeting() {
    std::string title, participator, startTime, endTime;
    std::cout << std::endl
              << "[create meeting] [title] [participator] "
              << "[start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-de/hh:mm)]"
              << std::endl
              << "[create meeting]";
    std::cin >> title >> participator >> startTime >> endTime;
    if (_agendaService.createMeeting(_userName, title, participator,
                                     startTime, endTime))
        std::cout << "[create meeting] succeed!" << std::endl;
    else
        std::cout << "[create meeting] create meeting fail!" << std::endl;
    std::cout << std::endl;
}

void AgendaUI::listAllMeetings() {
    std::cout << std::endl
              << "[list all meetings]" << std::endl << std::endl;
    printMeetings(_agendaService.listAllMeetings(_userName));
}

void AgendaUI::listAllSponsorMeetings() {
    std::cout << std::endl
              << "[list all sponsor meetings]" << std::endl << std::endl;
    printMeetings(_agendaService.listAllSponsorMeetings(_userName));
}

void AgendaUI::listAllParticipateMeetings() {
    std::cout << std::endl
              << "[list all sponsor meetings]" << std::endl << std::endl;
    printMeetings(_agendaService.listAllParticipateMeetings(_userName));
}

void AgendaUI::queryMeetingByTitle() {
    std::cout << std::endl
              << "[query meeting] [title]:" << std::endl
              << "[query meeting] ";
    std::string title;
    std::cin >> title;
    std::list<Meeting> meeting = _agendaService.meetingQuery(_userName, title);
    if (meeting.size() > 0) {
        const int l1 = max(7, meeting.front().getSponsor().length())+2;
        const int l2 = max(12, meeting.front().getParticipator().length())+2;
        const int l3 = 18;
        std::cout << std::endl
                << std::setfill(' ') << std::setw(l1) << std::left
                << "sponsor"
                << std::setfill(' ') << std::setw(l2) << std::left
                << "paritcipator"
                << std::setfill(' ') << std::setw(l3) << std::left
                << "start time" << "endtime" << std::endl
                << std::setfill(' ') << std::setw(l1) << std::left
                << meeting.front().getSponsor()
                << std::setfill(' ') << std::setw(l2) << std::left
                << meeting.front().getParticipator()
                << std::setfill(' ') << std::setw(l3) << std::left
                << Date::dateToString(meeting.front().getStartDate())
                << Date::dateToString(meeting.front().getEndDate())
                << std::endl << std::endl;
    } else {
        std::cout << "[error]No such meeting!" << std::endl << std::endl;
    }
}

void AgendaUI::queryMeetingByTimeInterval() {
    std::cout << std::endl
              << "[query meetings] [start time(yyyy-mm-dd/hh:mm)]"
              << "[end time(yyyy-mm-dd/hh:mm)]" << std::endl
              << "[query meetings]";
    std::string sDate, eDate;
    std::cin >> sDate >> eDate;
    std::cout << std::endl
              << "[query meetings]" << std::endl;
    printMeetings(_agendaService.meetingQuery(_userName, sDate, eDate));
}

void AgendaUI::deleteMeetingByTitle() {
    std::cout << std::endl
              << "[delete meeting] [title]" << std::endl
              << "[delete meeting] ";
    std::string title;
    std::cin >> title;
    if (_agendaService.deleteMeeting(_userName, title))
        std::cout << "[delete meeting by title] succeed!";
    else
        std::cout << "[error] delete meeting fail!";
    std::cout << std::endl << std::endl;
}

void AgendaUI::deleteAllMeetings() {
    std::cout << std::endl;
    if (_agendaService.deleteAllMeetings(_userName))
        std::cout << "[delete all meetings] succeed!";
    else
        std::cout << "[error] delete meetings fail!";
    std::cout << std::endl << std::endl;
}

void AgendaUI::printMeetings(const std::list<Meeting> & meetings) {
    int l1 = 5, l2 = 7, l3 = 12;
    const int l4 = 18;
    std::list<Meeting>::const_iterator it;
    for (it = meetings.begin(); it != meetings.end(); ++it) {
        l1 = max(l1, it->getTitle().length());
        l2 = max(l2, it->getSponsor().length());
        l3 = max(l3, it->getParticipator().length());
    }
    l1 += 2;
    l2 += 2;
    l3 += 2;
    std::cout << std::setfill(' ') << std::setw(l1) << std::left
              << "title"
              << std::setfill(' ') << std::setw(l2) << std::left
              << "sponsor"
              << std::setfill(' ') << std::setw(l3) << std::left
              << "participator"
              << std::setfill(' ') << std::setw(l4) << std::left
              << "start time" << "end time" << std::endl;
    for (it = meetings.begin(); it != meetings.end(); ++it)
        std::cout << std::setfill(' ') << std::setw(l1) << std::left
                  << it->getTitle()
                  << std::setfill(' ') << std::setw(l2) << std::left
                  << it->getSponsor()
                  << std::setfill(' ') << std::setw(l3) << std::left
                  << it->getParticipator()
                  << std::setfill(' ') << std::setw(l4) << std::left
                  << Date::dateToString(it->getStartDate())
                  << Date::dateToString(it->getEndDate()) << std::endl;
    std::cout << std::endl;
}

void AgendaUI::QB() {
    std::cout << std::endl;
    std::cout << ". .  :r :::::::::7                                          .j.:i,::::ii ii ... " << std::endl
              << ".     ;  :...,:,.i                                           ..  :....,. i      " << std::endl
              << ", ..  v, ,:i7i,::                                             .i:.vji:i r:   .. " << std::endl
              << ". ....:5  Y7   ,                                                :i .uY :S,::... " << std::endl
              << "i,i:::.u:i,  ,:                                                  .i  rjL  .,::r." << std::endl
              << ",      7q   ::                                                    .i  :u        " << std::endl
              << "      77   .:                                                       :   X.      " << std::endl
              << "     v7    ,                                                        ..   k      " << std::endl
              << "    vr                                                                    1     " << std::endl
              << "   Yr                                                                      5    " << std::endl
              << ": J7               ,:::ii,                             ,i:ii:              :q.. " << std::endl
              << ".:j      :        ;rrrr: :i                          :rrrrr,,r,        .    7F. " << std::endl
              << "i7       i       ;riss@:  s:                        :sirsss  :s        :     qv " << std::endl
              << "M       .r       sirssrssrri                        :sissss2irs        i      M." << std::endl
              << ":       .:       ,s;rrsrrrs                          rrrsssrrs:        :      iS" << std::endl
              << "        .7        ,rrrrri:                            :rrrrri,         7       r" << std::endl
              << "        .Y            ,                                                L        " << std::endl
              << "         0                                                            ,7        " << std::endl
              << "         2:                                                           u         " << std::endl
              << "         .S                                                          Li         " << std::endl
              << "          0i                                                        r7          " << std::endl
              << "           q.                                                      rr           " << std::endl
              << "            @i                   .    ___    ,                   .u,            " << std::endl
              << "            8MP,                  \\__/   \\__/                   L@P             " << std::endl
              << "           :S:2MEi                                           .UOkrE             " << std::endl
              << "           Sri::7EOSr.                                    .71qL:::F.            " << std::endl
              << "================================================================================" << std::endl
              << "              Make a contract with me, and become a magic girl!                 " << std::endl;
}

