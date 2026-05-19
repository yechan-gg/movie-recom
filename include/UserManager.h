#pragma once
#include <vector>
#include "User.h"
#include "BaseManager.h"

class UserManager : public BaseManager{
private:
    std::vector<User> users;

public:
    //생성자
    UserManager();

    //getter
    std::vector<User> getUsers() const; 

    //유저 정보 관리
    void addUser(const User& user);
    void removeUser(const std::string& name);

    //유저 검색
    User* findById(int id);
    User* findByName(const std::string& name);

    //출력
    void showAll() const;

    //파일 입출력
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    
    int size() const override;
};

