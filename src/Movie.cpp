#include "Movie.h"
#include <iostream>
#include <iomanip>

std::string slicingText(std::string target, int length){
    if((int) target.length() > length){
        return target.substr(0, length-3) + "...";
    }
    return target;
}

//생성자
Movie::Movie()
    : id(0), releaseYear(0), totalRating(0.0), ratingCount(0) {}
Movie::Movie(int id, const std::string& title, const std::string& genre, int year)
    : id(id), title(title), genre(genre), releaseYear(year), totalRating(0.0), ratingCount(0) {}

//getter
int         Movie::getId()           const { return id; }
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
double      Movie::getTotalRating()  const { return totalRating; }
int         Movie::getRatingCount()  const { return ratingCount; }
double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;
    return totalRating / ratingCount;
}

//평점 입력
void Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) return;
    totalRating += r;
    ratingCount++;
}

//출력
void Movie::display() const {           
    std::cout << id << ". " << title
              << " (" << releaseYear << ")"
              << "  평점: " << getAverageRating()
              << " (" << ratingCount << "건)"
              << std::endl;
}



//연산자 오버로딩
bool Movie::operator==(const Movie& other) const{ return title == other.title && releaseYear == other.releaseYear; }
bool Movie::operator!=(const Movie& other) const{ return !(*this == other); }
bool Movie::operator<(const Movie& other) const{
    if(getAverageRating() != other.getAverageRating()) return getAverageRating() < other.getAverageRating();
    return title < other.title;
}
bool Movie::operator>(const Movie& other) const{ return other < *this; }
bool Movie::operator<=(const Movie& other) const{ return !(other < *this); }
bool Movie::operator>=(const Movie& other) const{ return  !(*this < other); }
std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os  << std::setw(45) << slicingText(m.title + " (" + std::to_string(m.releaseYear) + ") " , 40)
        << std::setw(13) << m.genre
        << std::setw(5) << std::fixed << std::setprecision(1) << m.getAverageRating() 
        << std::setw(10) << m.ratingCount;
    return os;
}

