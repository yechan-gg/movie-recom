#pragma once
#include <vector>

#include "MovieManager.h"
#include "RatingManager.h"



class Recommend{
private:
    std::vector<Movie> movies;
    std::vector<Rating> ratings;
    std::vector<int> uIds;
public:
    Recommend();
    Recommend(const std::vector<Movie>& movies, const std::vector<Rating>& ratings, const std::vector<int>& uIds);

    std::vector<Rating> findByUser(int userId);
    double calculate(const std::vector<Rating>& user1, const std::vector<Rating>& user2);
    std::vector<std::pair<int, double>> findSimilarUsers(int target, int usersNum); 
    
    std::vector<int> recommendMovie(int target, const std::vector<std::pair<int, double>>& similarUsers, int moviesNum);
};