// Copyright [2013] Shawn

#include <string>
#include"User.h"

User::User() {
    _name.clear();
    _password.clear();
    _email.clear();
    _phone.clear();
}

User::User(const std::string & name, const std::string & password,
           const std::string & email, const std::string & phone) {
    _name = name;
    _password = password;
    _email = email;
    _phone = phone;
}

std::string User::getName() const {
    return _name;
}

void User::setName(const std::string & name) {
    _name = name;
}

std::string User::getPassword() const {
    return _password;
}

void User::setPassword(const std::string & password) {
    _password = password;
}

std::string User::getEmail() const {
    return _email;
}

void User::setEmail(const std::string & email) {
    _email = email;
}

std::string User::getPhone() const {
    return _phone;
}

void User::setPhone(const std::string & phone) {
    _phone = phone;
}

