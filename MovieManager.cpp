#include "Movie.h"
#include "MovieManager.h"
#include <algorithm>

MovieManager::MovieManager(){
}
void MovieManager::addMovie(const Movie& movie){
    movies.push_back(movie);
}
void MovieManager::removeMovie(const std::string& title){
    for(size_t i = 0; i < movies.size(); i++){
        if(movies[i].getTitle() == title){
            movies.erase(movies.begin() + i);
            break;
        }
    }
}
Movie* MovieManager::findByTitle(const std::string& title){
    for(Movie& m: movies){
        if(m.getTitle() == title)
            return &m;              //왜 &를 쓰는지 알아보자.
    }
    std::cout << "해당하는 영화를 찾지 못했습니다." << std::endl;
    return NULL;
}
void MovieManager::sortByRating(){
    sort(movies.begin(), movies.end());
}
void MovieManager::showAll() const{
    for(const Movie& m : movies){
        std::cout << m << std::endl;
    }
}
    

