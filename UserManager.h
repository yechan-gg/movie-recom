#pragma once
#include <vector>
#include "User.h"

class UserManager{
private:
    std::vector<User> users;
public:
    UserManager();
    void addUser(const User& user);
    void removeUser(const std::string& name);
    User* findByName(const std::string& name);
    void showAll() const;
};

