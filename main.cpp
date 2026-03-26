#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Movie> movies;
    std::vector<User> users;
    std::vector<Rating> rates;
    
    movies.emplace_back(1, "기생충", "드라마", 2019);
    movies.emplace_back(2, "인터스텔라", "SF", 2014);
   
    users.emplace_back(1, "KIM", "yeyechan1234");
    users.emplace_back(2, "PARK", "parkpark123");
   
    rates.emplace_back(1, 1, 3);
    rates.emplace_back(1, 2, 4);
    rates.emplace_back(2, 1, 3.5);
    rates.emplace_back(2, 2, 100);
   
    movies[0].addRating(4.5);
    movies[0].addRating(3.2);
 
    movies[1].addRating(5.0);
    movies[1].addRating(6.0);   //유효성 검사

    for(const Movie&m: movies){
        m.display();
    }
    for(const User&u: users){
        u.display();
    }
    for(const Rating&r: rates){
        r.display();
    }

    return 0;
}