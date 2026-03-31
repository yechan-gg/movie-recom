#pragma once

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
};