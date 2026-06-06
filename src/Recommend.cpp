#include "Recommend.h"
#include <set>

//생성자
Recommend::Recommend(){}
Recommend::Recommend(const std::vector<Movie>& movies, const std::vector<Rating>& ratings, const std::vector<int>& uIds)
    : movies(movies), ratings(ratings), uIds(uIds){}

//userId에 따른 Rating vector 리턴
//그대로 유사도 계산 함수에 사용
std::vector<Rating> Recommend::findByUser(int userId){
    std::vector<Rating> ratingOfUser;
    for(const Rating& r : ratings){
        if(userId == r.getUserId())
            ratingOfUser.push_back(r);
    }
    return ratingOfUser;
}

//return 타입 double (score가 double 타입) 나머진 그대로 가져감
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

//userId 1과 100이 유사하개 csv 파일의 데이터를 만들었습니다.
std::vector<std::pair<int, double>> Recommend::findSimilarUsers(int target, int usersNum){
    std::vector<std::pair<int, double>> similarity; 
    std::vector<std::pair<int, double>> answer; 

    //평점이 0개인 사용자는 빈 벡터 반환 
    if(findByUser(target).size() == 0){ return answer; }

    for(int i : uIds){
        if(target == i) continue;
        similarity.push_back({i, calculate(findByUser(target), findByUser(i))});
    }
    sort(similarity.begin(), similarity.end(),
    [](const std::pair<int, double>& a, const std::pair<int, double>& b){
        return a.second > b.second;
    });

    int limit = std::min(usersNum, (int) similarity.size());

    //유저 수가 적을 때
    if(limit == (int) similarity.size())
        std::cout << "유사한 유저 수가 적으므로 " << limit << "명만 출력합니다" << std::endl;
    for(int i = 0; i < limit; i++){
        answer.push_back(similarity[i]);
    }
    return answer;
}

//영화 추천 공식 : 유사도 * 평점
std::vector<std::pair<int,double>> Recommend::recommendMovie(int target, const std::vector<std::pair<int, double>>& similarUsers){
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

    return sorted;
}

std::vector<std::pair<int, double>> Recommend::filterByGenre(const std::vector<std::pair<int, double>>& sorted, const std::string& genre){
    std::vector<std::pair<int, double>> filtered;
    for (const std::pair<int, double>& pair : sorted) {
        int movieId = pair.first; // 영화 ID 추출
        auto it = std::find_if(movies.begin(), movies.end(), [movieId](const Movie& m) {
            return m.getId() == movieId;
        });

        if (it != movies.end() && it->getGenre() == genre) {
            filtered.push_back(pair);
        }
    }
    return filtered;
}