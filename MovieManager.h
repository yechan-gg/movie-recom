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
    void removeMovie(const std::string& title);
    Movie* findByTitle(const std::string& title);
    void sortByRating();
    void display() const;
};