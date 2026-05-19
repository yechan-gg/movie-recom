#pragma once
#include <vector>
#include <algorithm>
#include "Rating.h"
#include "BaseManager.h"

class RatingManager : public BaseManager{
private:
    std::vector<Rating> ratings;
    std::vector<int> uIds;

public:
    //생성자
    RatingManager();

    //getter
    std::vector<Rating> getRatings() const;
    std::vector<int> getUIds() const;
    
    //평점 정보 관리
    void addRating(const Rating& rating);

    //정렬
    void sortByUId();
     
    //출력
    void showByMovieId(int movieId) const;
    void showAll() const;
    
    //파일 입출력
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;

    int size() const override;
};