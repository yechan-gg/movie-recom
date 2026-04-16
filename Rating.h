#pragma once
#include <iostream>

class Rating{
private:
    int userId;
    int movieId;
    double score;
public:
    Rating();
    Rating(int userId, int movieId, double score);
    int getUserId() const;
    int getMovieId() const;
    int getScore() const;
    void display() const;
    friend std::ostream& operator<<(std::ostream& os, const Rating& r);
};