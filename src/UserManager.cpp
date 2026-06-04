#include "UserManager.h"
#include <sstream>
#include <fstream>
#include <iostream>

//생성자
UserManager::UserManager(){}

//getter
std::vector<User> UserManager::getUsers() const{ return users; }

//유저 정보 관리
void UserManager::addUser(const User& user){ users.push_back(user); }
void UserManager::removeUser(const std::string& name){
    for(size_t i = 0; i < users.size(); i++){
        if(users[i].getName() == name){
            users.erase(users.begin() + i);
            break;
        }
    }
}

//유저 검색
User* UserManager::findById(int id){
    for(User& u: users){
        if(u.getId() == id)
            return &u;             
    }
    return NULL;
}
User* UserManager::findByName(const std::string& name){
    for(User& u: users){
        if(u.getName() == name)
            return &u;             
    }
    return NULL;
}

//출력
void UserManager::showAll() const{
    for(const User& u : users){
        std::cout << u << std::endl;
    }
}

//파일 입출력
void UserManager::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);
        return;
    }
    std::string line;
    std::getline(file, line);
    int lineNum = 1;
    while(std::getline(file, line)){
        try{
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
        catch (const std::invalid_argument& e){
            std::cout << "Error Line: " << lineNum << " Invalid Argument" << std::endl;   
        }
        lineNum++;
    }
    file.close();
}
void UserManager::saveToFile(const std::string& filename) const{
    std::ofstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("저장 실패: " + filename);
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