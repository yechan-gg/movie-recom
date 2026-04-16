#include "UserManager.h"
#include <iostream>

UserManager::UserManager(){
}
void UserManager::addUser(const User& user){
    users.push_back(user);
}
void UserManager::removeUser(const std::string& name){
    for(size_t i = 0; i < users.size(); i++){
        if(users[i].getName() == name){
            users.erase(users.begin() + i);
            break;
        }
    }
}
User* UserManager::findByName(const std::string& name){
    for(User& u: users){
        if(u.getName() == name)
            return &u;              //왜 &를 쓰는지 알아보자.
    }
    std::cout << "해당하는 유저를 찾지 못했습니다." << std::endl;
    return NULL;
}
void UserManager::showAll() const{
    for(const User& u : users){
        std::cout << u << std::endl;
    }
}
    

