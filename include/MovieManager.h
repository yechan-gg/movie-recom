#pragma once
#include <iostream>
#include <vector>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager{
private:
    std::vector<Movie> movies;
public:
    MovieManager();

    std::vector<Movie> getMovies() const;

    void addMovie(const Movie& movie);
    void addRating(int movieId, double score);
    void removeMovie(const std::string& title);
    Movie* findByTitle(const std::string& title);
    Movie* findById(int id);
    void sortByRating();
    void sortById();
    void showAll() const;

    void loadFromFile(const std::string& filename) override;
    void loadRating(const std::string& filename);
    void saveToFile(const std::string& filename) const override;
    
    int size() const override;
};