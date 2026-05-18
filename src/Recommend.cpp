#include "Recommend.h"
#include <map>
#include <set>

Recommend::Recommend(){}
Recommend::Recommend(const std::vector<Movie>& movies, const std::vector<Rating>& ratings, const std::vector<int>& uIds)
    : movies(movies), ratings(ratings), uIds(uIds){}

std::vector<Rating> Recommend::findByUser(int userId){
    std::vector<Rating> ratingOfUser;
    for(const Rating& r : ratings){
        if(userId == r.getUserId())
            ratingOfUser.push_back(r);
    }
    return ratingOfUser;
}


double Recommend::calculate(const std::vector<Rating>& user1, const std::vector<Rating>& user2){
    int commonCount = 0;
    int scoreDiffSum = 0;

    for(const Rating& r1: user1){
        for(const Rating& r2: user2){
            if(r1.getMovieId() == r2.getMovieId()){
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }
    if(commonCount == 0)
        return -100;
    return commonCount * 10 - scoreDiffSum;
}

std::vector<std::pair<int, double>> Recommend::findSimilarUsers(int target, int usersNum){
    std::vector<std::pair<int, double>> similarity; 
    std::vector<std::pair<int, double>> answer; 
    if(findByUser(target).size() == 0){
        std::cout << "사용자의 평점이 없습니다. 평점을 추가해주세요." << std::endl;
        return answer;
    }

    for(int i : uIds){
        if(target == i) continue;
        similarity.push_back({i, calculate(findByUser(target), findByUser(i))});
    }
    sort(similarity.begin(), similarity.end(),
    [](const std::pair<int, double>& a, const std::pair<int, double>& b){
        return a.second > b.second;
    });

    int limit = std::min(usersNum, (int) similarity.size());
    for(int i = 0; i < limit; i++){
        answer.push_back(similarity[i]);
    }
    return answer;
}

std::vector<int> Recommend::recommendMovie(int target, const std::vector<std::pair<int, double>>& similarUsers, int moviesNum){
    std::set<int> myMovies;
    std::map<int, double> movieScores;
    for(const Rating& r : findByUser(target)){
        myMovies.insert(r.getMovieId());
    }
    for(const std::pair<int, double>& s : similarUsers){
        for(const Rating& r : findByUser(s.first)){
            if(myMovies.find(r.getMovieId()) == myMovies.end())
                movieScores[r.getMovieId()] += s.second * r.getScore();
        }
    }

    std::vector<std::pair<int,double>> sorted(movieScores.begin(), movieScores.end());
    sort(sorted.begin(), sorted.end(),[](auto& a, auto& b){ return a.second > b.second; });

    std::vector<int> answer;
    int limit = std::min(moviesNum, (int) sorted.size());
    for(int i = 0; i < limit; i++){
        answer.push_back(sorted[i].first);
    }
    return answer;
}