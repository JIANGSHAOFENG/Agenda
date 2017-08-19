// Copyright [2013] Shawn

#include"Storage.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const char Storage::DATAFILE[12] = "agenda.data";
Storage *Storage::_instance = nullptr;

Storage::Storage() {
    _userList.clear();
    _meetingList.clear();
    readFromFile(DATAFILE);
}

bool Storage::readFromFile(const char * fpath) {
    std::ifstream fin(fpath);
    if (!fin.is_open())
        return false;
    std::stringstream uss, mss;
    std::string temp, name, password, email, phone;
    std::string sponsor, participator, sdate, edate, title;
    std::size_t pos[10];
    int n, i;

    if (fin.peek() == EOF) {
        fin.close();
        return true;
    }
    std::getline(fin, temp);
    if (temp.find("\"User\"") != std::string::npos) {
        pos[0] = temp.find("total:");
        temp.erase(0, pos[0]+6);
        uss << temp;
        uss >> n;
        while (n > 0) {
            --n;
            std::getline(fin, temp);
            pos[0] = temp.find_first_of('\"');
            for (i = 1; i < 8; ++i)
                pos[i] = temp.find_first_of('\"', pos[i-1]+1);
            name.assign(temp, pos[0]+1, pos[1]-pos[0]-1);
            password.assign(temp, pos[2]+1, pos[3]-pos[2]-1);
            email.assign(temp, pos[4]+1, pos[5]-pos[4]-1);
            phone.assign(temp, pos[6]+1, pos[7]-pos[6]-1);
            _userList.push_back(User(name, password, email, phone));
        }

        if (fin.peek() == EOF) {
            fin.close();
            return true;
        }
        std::getline(fin, temp);
    }
    pos[0] = temp.find("total:");
    temp.erase(0, pos[0]+6);
    mss << temp;
    mss >> n;
    while (n > 0) {
        --n;
        std::getline(fin, temp);
        pos[0] = temp.find_first_of('\"');
        for (i = 1; i < 10; ++i)
            pos[i] = temp.find_first_of('\"', pos[i-1]+1);
        sponsor.assign(temp, pos[0]+1, pos[1]-pos[2]-1);
        participator.assign(temp, pos[2]+1, pos[3]-pos[2]-1);
        sdate.assign(temp, pos[4]+1, pos[5]-pos[4]-1);
        edate.assign(temp, pos[6]+1, pos[7]-pos[6]-1);
        title.assign(temp, pos[8]+1, pos[9]-pos[8]-1);
        _meetingList.push_back(
                Meeting(sponsor, participator, Date::stringToDate(sdate),
                        Date::stringToDate(edate), title));
    }

    fin.close();
    return true;
}

bool Storage::writeToFile(const char * fpath) {
    std::ofstream fout(fpath);
    if (!fout.is_open())
        return false;

    if (_userList.size() > 0) {
        std::list<User>::iterator uit;
        fout << "{collection:\"User\",total:"
             << _userList.size() << '}' << std::endl;
        for (uit = _userList.begin(); uit != _userList.end(); ++uit)
            fout << "{name:\"" << uit->getName()
                 << "\",password:\"" << uit->getPassword()
                 << "\",email:\"" << uit->getEmail()
                 << "\",phone:\"" << uit->getPhone() << "\"}" << std::endl;
    }

    if (_meetingList.size() > 0) {
        std::list<Meeting>::iterator mit;
        fout << "{collection:\"Meeting\",total:"
             << _meetingList.size() << '}' << std::endl;
        for (mit = _meetingList.begin(); mit != _meetingList.end(); ++mit)
            fout << "{sponsor:\"" << mit->getSponsor()
                 << "\",participator:\"" << mit->getParticipator()
                 << "\",sdate:\"" << Date::dateToString(mit->getStartDate())
                 << "\",edate:\"" << Date::dateToString(mit->getEndDate())
                 << "\",title:\"" << mit->getTitle() << "\"}" << std::endl;
    }

    fout.close();
    return true;
}

Storage * Storage::getInstance() {
    if (_instance == nullptr)
        _instance = new Storage;
    return _instance;
}

Storage::~Storage() {
    _userList.clear();
    _meetingList.clear();
    _instance = nullptr;
}

void Storage::createUser(const User & user) {
    _userList.push_back(user);
}

std::list<User> Storage::queryUser(const std::function<bool(const User &)> &
                                                                    filter) {
    std::list<User> result;
    result.clear();
    std::list<User>::iterator it;
    for (it = _userList.begin(); it != _userList.end(); ++it)
        if (filter(*it))
            result.push_back(*it);
    return result;
}

int Storage::updateUser(const std::function<bool(const User &)> & filter,
                        const std::function<void(User &)> & switcher) {
    int counter = 0;
    std::list<User>::iterator it;
    for (it = _userList.begin(); it != _userList.end(); ++it)
        if (filter(*it)) {
            ++counter;
            switcher(*it);
        }
    return counter;
}

int Storage::deleteUser(const std::function<bool(const User &)> & filter) {
    int counter = 0;
    std::list<User>::iterator it;
    for (it = _userList.begin(); it != _userList.end();)
        if (filter(*it)) {
            it = _userList.erase(it);
            ++counter;
        } else {
            ++it;
        }
    return counter;
}

void Storage::createMeeting(const Meeting & meeting) {
    _meetingList.push_back(meeting);
}

std::list<Meeting> Storage::queryMeeting(
        const std::function<bool(const Meeting &)> & filter) {
    std::list<Meeting> result;
    result.clear();
    std::list<Meeting>::iterator it;
    for (it = _meetingList.begin(); it != _meetingList.end(); ++it)
        if (filter(*it))
            result.push_back(*it);
    return result;
}

int Storage::updateMeeting(
        const std::function<bool(const Meeting &)> & filter,
        const std::function<void(Meeting &)> & switcher) {
    int counter = 0;
    std::list<Meeting>::iterator it;
    for (it = _meetingList.begin(); it != _meetingList.end(); ++it)
        if (filter(*it)) {
            ++counter;
            switcher(*it);
        }
    return counter;
}

int Storage::deleteMeeting(
        const std::function<bool(const Meeting &)> & filter) {
    int counter = 0;
    std::list<Meeting>::iterator it;
    for (it = _meetingList.begin(); it != _meetingList.end();)
        if (filter(*it)) {
            it = _meetingList.erase(it);
            ++counter;
        } else {
            ++it;
        }
    return counter;
}

bool Storage::sync() {
    return writeToFile(DATAFILE);
}

