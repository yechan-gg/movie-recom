#include "User.h"
#include <iostream>
#include <iomanip>

//생성자
User::User(int id, const std::string& name, const std::string& email)
    :id(id), name(name), email(email) {}

//getter
int User::getId() const{ return id; }
std::string User::getName() const{ return name; } 
std::string User::getEmail() const{ return email;}

//출력
void User::display() const{
    std::cout << "ID: " << id;
    std::cout << " Name: " << name;
    std::cout << " Email: " << email << std::endl;;
}

//연산자 오버로딩
std::ostream& operator<<(std::ostream& os, const User& u) {
    os  << std::setw(5) << std::to_string(u.id) + ". "
        << std::setw(12) <<  u.name << u.email;
    return os;
}

