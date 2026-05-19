#pragma once
#include <iostream>
#include <vector>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager{
private:
    std::vector<Movie> movies;

public:
    //생성자
    MovieManager();

    //getter
    std::vector<Movie> getMovies() const;

    //영화, 평점 정보 관리
    void addMovie(const Movie& movie);
    void addRating(int movieId, double score);
    void removeMovie(const std::string& title);

    //영화 검색
    Movie* findByTitle(const std::string& title);
    Movie* findById(int id);

    //정렬
    void sortByRating();
    void sortById();

    //출력
    void showAll() const;

    //파일 입출력
    void loadFromFile(const std::string& filename) override;
    void loadRating(const std::string& filename);
    void saveToFile(const std::string& filename) const override;
    
    int size() const override;
};