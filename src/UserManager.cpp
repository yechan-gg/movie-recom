#include "UserManager.h"
#include <sstream>
#include <fstream>
#include <iostream>

UserManager::UserManager(){
}

std::vector<User> UserManager::getUsers() const{
    return users;
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
    return NULL;
}
void UserManager::showAll() const{
    for(const User& u : users){
        std::cout << u << std::endl;
    }
}
    
void UserManager::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, ',');
        int id = std::stoi(token);
        std::getline(ss, token, ',');
        std::string name = token;
        std::getline(ss, token, ',');
        std::string email = token;
        users.push_back(User(id, name, email));
    }
    file.close();
}

void UserManager::saveToFile(const std::string& filename) const{
    std::ofstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error: " << filename << " 저장 실패" << std::endl;
        return;
    }
    file << "id,name,email" << std::endl;
    for(const auto& u : users){
        file << u.getId()    << ","
             << u.getName()  << ","
             << u.getEmail() << std::endl;
    }
    file.close();
}

int UserManager::size() const{
    return users.size();
}