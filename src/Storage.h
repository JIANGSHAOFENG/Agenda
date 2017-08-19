// Copyright [2013] Shawn

#ifndef __STORAGE_H__
#define __STORAGE_H__

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

#include <list>
#include <string>
#include <functional>

#include"User.h"
#include"Meeting.h"

class Storage {
    public:
        static Storage *getInstance();
        ~Storage();
        void createUser(const User &);
        std::list<User> queryUser(const std::function<bool(const User &)> &);
        int updateUser(const std::function<bool(const User &)> &,  // filter
                       const std::function<void(User &)> &);  // switcher
        int deleteUser(const std::function<bool(const User &)> &);
        void createMeeting(const Meeting &);
        std::list<Meeting> queryMeeting(
                const std::function<bool(const Meeting &)> &);
        int updateMeeting(const std::function<bool(const Meeting &)> &,
                                // filter
                          const std::function<void(Meeting &)> &);
                                // switcher
        int deleteMeeting(const std::function<bool(const Meeting &)> &);
        bool sync();

    private:
        static Storage *_instance;
        Storage();
        std::list<User> _userList;
        std::list<Meeting> _meetingList;
        bool readFromFile(const char *);
        bool writeToFile(const char *);
        static const char DATAFILE[12];
        DISALLOW_COPY_AND_ASSIGN(Storage);
};

#endif

