#include "Movie.h"
#include "MovieManager.h"
#include <algorithm>
#include <sstream>
#include <fstream>

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
    

void MovieManager::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, ',');
        int id = std::stoi(token);
        std::getline(ss, token, ',');
        std::string title = token;
        std::getline(ss, token, ',');
        std::string genre = token;
        std::getline(ss, token, ',');
        int releaseYear = std::stoi(token);
        std::getline(ss, token, ',');
        double totalRating = std::stod(token);
        std::getline(ss, token, ',');
        int ratingCount = std::stoi(token);
        movies.push_back(Movie(id, title, genre, releaseYear, totalRating, ratingCount));
    }
    file.close();
}
void MovieManager::saveToFile(const std::string& filename){
    std::ofstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error: " << filename << " 저장 실패" << std::endl;
        return;
    }
    file << "id,title,genre,rating" << std::endl;
    for(const auto& m : movies){
        file << m.getId()     << ","
             << m.getTitle()  << ","
             << m.getGenre()   << ","
             << m.getRatingCount() << std::endl;
    }
    file.close();
}

