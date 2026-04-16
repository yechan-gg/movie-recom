#pragma once
#include <vector>
#include "Rating.h"
#include "MovieManager.h"

class RatingManager{
private:
    std::vector<Rating> ratings;
public:
    RatingManager();
    void addRating(const Rating& rating, MovieManager& movies);
    void showAll() const;
};