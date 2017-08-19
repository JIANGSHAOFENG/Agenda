// Copyright [2013] Shawn

#ifndef __USER_H__
#define __USER_H__

#include <string>

class User {
    public:
        User();
        User(const std::string &, const std::string &,   // name, password
             const std::string &, const std::string &);  // email, phone
        std::string getName() const;
        void setName(const std::string &);
        std::string getPassword() const;
        void setPassword(const std::string &);
        std::string getEmail() const;
        void setEmail(const std::string &);
        std::string getPhone() const;
        void setPhone(const std::string &);

    private:
        std::string _name;
        std::string _password;
        std::string _email;
        std::string _phone;
};

#endif

