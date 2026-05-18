#pragma once
#include <vector>
#include "User.h"
#include "BaseManager.h"

class UserManager : public BaseManager{
private:
    std::vector<User> users;
public:
    UserManager();
    std::vector<User> getUsers() const; 

    void addUser(const User& user);
    void removeUser(const std::string& name);
    User* findByName(const std::string& name);
    void showAll() const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};

