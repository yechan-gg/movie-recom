#include "Rating.h"
#include <string>
#include <iomanip>

//생성자
Rating::Rating()
    :userId(0), movieId(0), score(0){}
Rating::Rating(int userId, int movieId, double score)
    :userId(userId), movieId(movieId), score(score){   
        if(this->score < 0.0 || this->score > 5.0)         
            this->score = 0;
    }

//getter
int Rating::getUserId() const{ return userId; }
int Rating::getMovieId() const{ return movieId; }
int Rating::getScore() const{ return score; }
void Rating::display() const{
    std::cout << "UserID: " << userId;
    std::cout << " MovieID: " << movieId;
    std::cout << " Score: " << score << std::endl;;
}

//연산자 오버로딩
bool Rating::operator<(const Rating& other) const{
    if(userId != other.userId) return userId < other.userId;
    return movieId < other.movieId;
}
std::ostream& operator<<(std::ostream& os, const Rating& r){
    os << "UID: " << std::setw(5) << r.userId << " / " << r.score << "점";
    return os;
}
