#include "Rating.h"
#include <string>

Rating::Rating()
    :userId(0), movieId(0), score(0)
    {}
Rating::Rating(int userId, int movieId, double score)
    :userId(userId), movieId(movieId), score(score)
    {   
        if(this->score < 0.0 || this->score > 5.0)         //유효성 검사
            this->score = 0;
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

std::ostream& operator<<(std::ostream& os, const Rating& r){
    os << "유저 ID: " << r.userId << " 영화 ID: " << r.movieId << " 평점: " << r.score;
    return os;
}