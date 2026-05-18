#pragma once
#include <iostream>
#include <vector>
#include "Movie.h"

class MovieManager{
private:
    std::vector<Movie> movies;
public:
    MovieManager();
    void addMovie(const Movie& movie);
    void addRating(int movieId, double score);
    void removeMovie(const std::string& title);
    Movie* findByTitle(const std::string& title);
    Movie* findById(int id);
    void sortByRating();
    void showAll() const;

    void loadFromFile(const std::string& filename);
    void loadRating(const std::string& filename);
    void saveToFile(const std::string& filename);
};