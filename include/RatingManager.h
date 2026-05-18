#pragma once
#include <vector>
#include <algorithm>
#include "Rating.h"
#include "MovieManager.h"

class RatingManager{
private:
    std::vector<Rating> ratings;
    std::vector<int> uIds;
public:
    RatingManager();

    std::vector<int> getUIds() const;
    void addRating(const Rating& rating);
    void sortByUId();
     
    void showByMovieId(int movieId) const;
    void showAll() const;
    std::vector<Rating> findByUser(int userId);

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};