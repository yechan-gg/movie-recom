#pragma once
#include <string>

class User{
private:
    int id;
    std::string name;
    std::string email;

public:
    //생성자
    User();
    User(int id, const std::string& name, const std::string& email);

    //getter
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    
    //출력
    void display() const;

    //연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const User& u);
};