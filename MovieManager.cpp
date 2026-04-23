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
    return NULL;
}
Movie* MovieManager::findById(int id){
    for(Movie& m: movies){
        if(m.getId() == id)
            return &m;              //왜 &를 쓰는지 알아보자.
    }
    return NULL;
}
void MovieManager::sortByRating(){
    sort(movies.begin(), movies.end(), 
    [](const Movie& a, const Movie& b){
        if(a.getAverageRating() != b.getAverageRating())
            return a.getAverageRating() > b.getAverageRating();
        return a.getTitle() < b.getTitle();
    });
}
void MovieManager::showAll() const{
    for(const Movie& m : movies){
        std::cout << m << std::endl;
    }
}
    

