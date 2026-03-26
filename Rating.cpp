#include "Rating.h"
#include <iostream>
#include <string>

Rating::Rating(){
    userId = 0; 
    movieId = 0;
    score = 0;
}
Rating::Rating(int uId, int mId, double s){
    userId = uId; 
    movieId = mId;
    if(s < 0.0 || s > 5.0){
        std::cout << "0과 5사이의 평점을 입력하세요." << std::endl;
        score = 0;
    }
    else score = s;  
}
int Rating::getUserId() const{
    return userId;
}
int Rating::getMovieId() const{
    return movieId;
}
int Rating::getScore() const{
    return score;
}
void Rating::display() const{
    std::cout << "UserID: " << userId;
    std::cout << " MovieID: " << movieId;
    std::cout << " Score: " << score << std::endl;;
}