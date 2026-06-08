#include "RatingManager.h"
#include <sstream>
#include <fstream>
#include <algorithm>

//생성자
RatingManager::RatingManager(){};

//getter
std::vector<Rating> RatingManager::getRatings() const{ return ratings; }
std::vector<int> RatingManager::getUIds() const{ return uIds; }

//평점 정보 관리
void RatingManager::addRating(const Rating& rating){
    auto it = std::find(uIds.begin(), uIds.end(), rating.getUserId());
        if(it == uIds.end())
            uIds.push_back(rating.getUserId());
    ratings.push_back(rating);
}

//정렬
void RatingManager::sortByUId(){
    sort(uIds.begin(), uIds.end());
    sort(ratings.begin(), ratings.end());
}

//출력
void RatingManager::showByMovieId(int movieId) const{
    std::cout << std::right;
    for(const Rating& r : ratings){
        if(r.getMovieId() == movieId)
            std::cout << r << std::endl;
    }
}
void RatingManager::showAll() const{
    for(const Rating& r : ratings){
        std::cout << r << std::endl;
    }
}

//파일 입출력
void RatingManager::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);
        return;
    }
    std::string line;
    std::getline(file, line);
    int lineNum = 0;
    while(std::getline(file, line)){
        try{
            std::stringstream ss(line);
            std::string token;
            std::getline(ss, token, ',');
            int uId = std::stoi(token);
            std::getline(ss, token, ',');
            int mId = std::stoi(token);
            std::getline(ss, token, ',');
            double rating = std::stod(token);
            addRating(Rating(uId, mId, rating));
        }
        catch (const std::invalid_argument& e){
            std::cout << "Error Line: " << lineNum << " Invalid Argument" << std::endl;   
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error Line " << lineNum << ": 데이터 값이 자료형 변수 범위를 초과했습니다. (" << line << ")" << std::endl;
        }
        lineNum++;
    }
    file.close();
}
void RatingManager::saveToFile(const std::string& filename) const{
    std::ofstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("저장 실패: " + filename);
        return;
    }
    file << "userId,movieId,score" << std::endl;
    for(const auto& r : ratings){
        file << r.getUserId()     << ","
             << r.getMovieId()  << ","
             << r.getScore() << std::endl;
    }
    file.close();
}

int RatingManager::size() const{
    return ratings.size();
}