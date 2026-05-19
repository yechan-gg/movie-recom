#pragma once
#include <iostream>

class Rating{
private:
    int userId;
    int movieId;
    double score;

public:
    //생성자
    Rating();
    Rating(int userId, int movieId, double score);

    //getter
    int getUserId() const;
    int getMovieId() const;
    int getScore() const;
    
    //출력
    void display() const;

    //연산자 오버로딩
    bool operator<(const Rating& other) const; 
    friend std::ostream& operator<<(std::ostream& os, const Rating& r);
};