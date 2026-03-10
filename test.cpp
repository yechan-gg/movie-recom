#include <iostream>
#include <string>

using namespace std;

struct human{
    int age;
    string name;

    int getage(){ return age; }
    string getname(){ return name; }
};

int main(){
    human Kim, Park;
    string tmp;

    Kim.age = 10;
    Kim.name = "yechan";

    tmp = Kim.getname();
    cout << tmp << endl;
    return 0;
}