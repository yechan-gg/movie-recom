#include "RatingManager.h"


RatingManager::RatingManager(){

};

void RatingManager::addRating(const Rating& rating, MovieManager& movies){
    ratings.push_back(rating);
    movies.findById(rating.getMovieId())->addRating(rating.getScore());
}

void RatingManager::showAll() const{
    for(const Rating& r : ratings){
        std::cout << r << std::endl;
    }
}