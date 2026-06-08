#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "BaseManager.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h" 
#include "Recommend.h"


void showMainStatus();
void showSubStatus(int command);
void addMovie(MovieManager& movieManager);
Movie* findMovie(MovieManager& movieManager, std::string title);
User* findUser(UserManager& userManager, std::string name);
void searchMovie(MovieManager& movieManager);
void showMovie(const MovieManager& movieManager);
void addUser(UserManager& userManager);
void showUser(const UserManager& userManager);
void addRating(MovieManager& movieManager, UserManager& userManager, RatingManager& ratingManager);
void showRatings(MovieManager& movieManager, RatingManager& ratingManager);
std::vector<std::pair<int, double>> userInquiry(User* target, Recommend& recommend, UserManager& userManager);
void showSimilarUser(double selfSimilarity, const std::vector<std::pair<int, double>>& similarUser, UserManager& userManager);
void recommendMovie(const std::vector<std::pair<int,double>>& resultMovie, MovieManager& movieManager);
void showFiltered(const std::vector<std::pair<int,double>>& resultMovie, Recommend& recommend, MovieManager& movieManager);

int main() {
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;
    movieManager.loadFromFile("data/movies.csv");
    movieManager.loadRating("data/ratings.csv");
    userManager.loadFromFile("data/users.csv");
    ratingManager.loadFromFile("data/ratings.csv");
    
    int command;
    do{
        showMainStatus();
        std::cin >> command; 
        
        switch(command){
            case 1:{
                int order;
                do{
                    showSubStatus(command);
                    std::cin >> order;
                    switch(order){
                        case 1:
                            addMovie(movieManager);
                            break;
                        case 2:
                            searchMovie(movieManager);
                            break;
                        case 4:
                            movieManager.sortByRating();
                        case 3:
                            showMovie(movieManager);
                            break;
                        case 0:
                            break;
                        default:
                            std::cout << "0 에서 4 사이의 정수를 입력해주세요." << std::endl;
                    }
                }while(order != 0);
                break;}
            case 2:{
                int order;
                do{
                    showSubStatus(command);
                    std::cin >> order;
                    switch (order){
                    case 1:
                        addUser(userManager);
                        break;
                    case 2:
                        showUser(userManager);
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "0 에서 2 사이의 정수를 입력해주세요." << std::endl;
                    }
                }while(order != 0);
                break;}
            case 3:{
                
                int order;
                do{
                    showSubStatus(command);
                    std::cin >> order;
                    switch (order){
                    case 1:
                        addRating(movieManager, userManager, ratingManager);
                        break;
                    case 2:
                        showRatings(movieManager, ratingManager);
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "0 에서 2 사이의 정수를 입력해주세요." << std::endl;
                    }
                }while(order != 0);
                break;}
            case 4:{
                int order;
                std::string userName;
                std::cout << "유저 이름 or Id: ";
                std::cin.ignore();
                std::getline(std::cin, userName);
                User* user = findUser(userManager, userName);
                Recommend recommend(movieManager.getMovies(), ratingManager.getRatings(), ratingManager.getUIds());
                double selfSimilarity = recommend.findSelfSimilarity(user->getId());
                std::vector<std::pair<int, double>> similarUser = userInquiry(user, recommend, userManager);
                std::vector<std::pair<int, double>> resultMovie = recommend.recommendMovie(user->getId(), similarUser);
                std::cout << "유저 조회 완료.\n" << std::endl;
                if(similarUser.empty()){
                    std::cout << "사용자의 평점 수가 너무 적습니다. 평점을 추가해주세요.\n" << std::endl;
                    break;
                }
                do{
                    showSubStatus(command);
                    std::cin >> order;
                    switch(order){
                    case 1:
                        showSimilarUser(selfSimilarity, similarUser, userManager);
                        break;
                    case 2:
                        recommendMovie(resultMovie, movieManager);
                        break;
                    case 3:
                        showFiltered(resultMovie, recommend, movieManager);
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "0 에서 3 사이의 정수를 입력해주세요." << std::endl;
                    }
                }while(order != 0);
                break;
            }
            case 0:
                std::cout << "프로그램 종료" << std::endl;
                break;
            default:
                std::cout << "0 에서 8 사이의 정수를 입력해주세요." << std::endl;
        }
    }while(command != 0);

    movieManager.sortById();    // 정렬해서 저장
    ratingManager.sortByUId();
    movieManager.saveToFile("data/movies.csv");
    userManager.saveToFile("data/users.csv");
    ratingManager.saveToFile("data/ratings.csv");
    return 0;
}


void showMainStatus(){
    std::cout << "=== Movie Recommender ===\n" << std::endl;
    std::cout << "1. [ 영화 ]" << std::endl;
    std::cout << " 영화 추가\n" <<
                 " 제목으로 검색\n" <<
                 " 전체 목록 출력\n" <<
                 " 평점순 정렬 출력\n" << std::endl;

    std::cout << "2. [ 사용자 ]" << std::endl;
    std::cout << " 사용자 추가\n" <<
                 " 사용자 목록 출력\n" << std::endl;

    std::cout << "3. [ 평점 ]" << std::endl;
    std::cout << " 평점 입력\n" <<
                 " 영화별 평점 보기\n" << std::endl;
    
    std::cout << "4. [ 추천 ]" << std::endl;
    std::cout << " 유사 사용자 목록 출력\n" <<
                 " 영화 추천\n" << 
                 " 장르별 영화 추천\n" << std::endl;            

    std::cout << "0. [ 종료 ]\n" << 
                 "선택 > "; 
}
void showSubStatus(int command){
    switch (command){
    case 1:
        std::cout << "\n [ 영화 ]" << std::endl;
        std::cout << "1. 영화 추가\n" <<
                     "2. 제목으로 검색\n" <<
                     "3. 전체 목록 출력\n" <<
                     "4. 평점순 정렬 출력\n" << 
                     "0. 이전\n" <<
                     "선택 > "; 
        break;
    case 2:
        std::cout << "\n [ 사용자 ]" << std::endl;
        std::cout << "1. 사용자 추가\n" <<
                     "2. 사용자 목록 출력\n" << 
                     "0. 이전\n" <<
                     "선택 > "; 
        break;
    case 3:
        std::cout << "\n [ 평점 ]" << std::endl;
        std::cout << "1. 평점 입력\n" <<
                     "2. 영화별 평점 보기\n" << 
                     "0. 이전\n" <<
                     "선택 > "; 
        break;
    case 4:
        std::cout << "\n [ 추천 ]" << std::endl;
        std::cout << "1. 유사 사용자 목록 출력\n" <<
                     "2. 영화 추천\n" << 
                     "3. 장르별 영화 추천\n" << 
                     "0. 이전\n" <<
                     "선택 > "; 
    default:
        break;
    }
    
}

void addMovie(MovieManager& movieManager){
    int movieId, movieYear;
    std::string movieTitle, movieGenre;

    std::cout << "\n영화를 입력합니다\n" << std::endl;
    while(1){
        std::cout << "영화 ID: ";
        std::cin >> movieId;
        if(movieManager.findById(movieId) != NULL){     //중복 ID 처리
            std::cout << "중복되는 ID입니다. 다시 입력해주세요." << std::endl;
        }
        else break;
    }
    std::cout << "영화 제목: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);
    std::replace(movieTitle.begin(), movieTitle.end(), ',', ' ');   // title의 , 제거
    std::cout << "장르: ";
    std::getline(std::cin, movieGenre);
    std::replace(movieGenre.begin(), movieGenre.end(), ',', ' ');
    std::cout << "개봉년도: ";
    std::cin >> movieYear;

    movieManager.addMovie(Movie(movieId, movieTitle, movieGenre, movieYear));

    std::cout << std::endl;
}
Movie* findMovie(MovieManager& movieManager, std::string title){
    int movieId;    
    try{
        movieId = std::stoi(title);
        if(std::to_string(movieId) == title)
            return movieManager.findById(movieId);
    }
    catch(const std::invalid_argument& e){
    }
    return movieManager.findByTitle(title);     
}
User* findUser(UserManager& userManager, std::string name){
    int userId;    
    try{
        userId = std::stoi(name);
        if(std::to_string(userId) == name)
            return userManager.findById(userId);
    }
    catch(const std::invalid_argument& e){
    }
    return userManager.findByName(name);     
}
void searchMovie(MovieManager& movieManager){
    std::string movieTitle;

    std::cout << "\n영화의 정보를 출력합니다\n" << std::endl;
    std::cout << "영화 제목 or ID: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);

    Movie* target = findMovie(movieManager, movieTitle);
    if(target == NULL)
        std::cout << "해당하는 영화를 찾지 못했습니다.\n" << std::endl;       
    else{
        std::cout << "--------------영화 정보--------------" << std::endl;
        target->display();
        std::cout << "-------------------------------------" << std::endl;
    }
}
void showMovie(const MovieManager& movieManager){
    std::cout << "\n영화 목록 출력\n\n" << std::endl;
    std::cout << "순위      영화 제목 (개봉년도)                         장르         평점 평점수" << std::endl;
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
    movieManager.showAll();
    std::cout << "-------------------------------------------------------------------------------\n" << std::endl;
}

void addUser(UserManager& userManager){
    int userId;
    std::string userName, userEmail;

    std::cout << "\n사용자를 추가합니다\n" << std::endl;
    while(1){
        std::cout << "유저 ID: ";
        std::cin >> userId;
        if(userManager.findById(userId) != NULL){     //중복 ID 처리
            std::cout << "중복되는 ID입니다. 다시 입력해주세요." << std::endl;
        }
        else break;
    }       
    std::cout << "유저 이름: ";
    std::cin.ignore();
    std::getline(std::cin, userName);
    std::replace(userName.begin(), userName.end(), ',', ' ');
    std::cout << "Email: ";
    std::getline(std::cin, userEmail);
    std::replace(userEmail.begin(), userEmail.end(), ',', ' ');
    
    userManager.addUser(User(userId, userName, userEmail));

    std::cout << std::endl;
}
void showUser(const UserManager& userManager){
    std::cout << "\n전체 유저 목록 출력\n\n" << std::endl;
    std::cout << "UID  이름     Email" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    userManager.showAll();
    std::cout << "---------------------------------------\n" << std::endl;
}

void addRating(MovieManager& movieManager, UserManager& userManager, RatingManager& ratingManager){
    std::string userName, movieTitle;
    int userId, movieId, score;
    std::cout << "\n평점을 입력합니다\n" << std::endl;

    std::cout << "유저 이름 or ID: ";
    std::cin.ignore();
    std::getline(std::cin, userName);
    User* targetUser = findUser(userManager, userName);
    if(targetUser == NULL){
        std::cout << "해당하는 유저를 찾지 못했습니다.\n" << std::endl;
        return;
    }
    else{
        userId = targetUser->getId();
    }

    std::cout << "영화 제목 or ID: ";
    std::getline(std::cin, movieTitle);
    Movie* targetMovie = findMovie(movieManager, movieTitle);
    if(targetMovie == NULL){
        std::cout << "해당하는 영화를 찾지 못했습니다.\n" << std::endl;
        return;
    }
    else{
        movieId = targetMovie->getId();
    }        
    std::cout << "평점: ";
    std::cin >> score;

    ratingManager.addRating(Rating(userId, movieId, score));
    movieManager.addRating(movieId, score);
}
void showRatings(MovieManager& movieManager, RatingManager& ratingManager){
    std::string movieTitle;
    std::cout << "\n영화의 평점 목록을 출력합니다\n" << std::endl;
    std::cout << "영화 제목 or ID: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);

    Movie* targetMovie = findMovie(movieManager, movieTitle);
    if(targetMovie == NULL)
        std::cout << "해당하는 영화를 찾지 못했습니다.\n" << std::endl;
    else{
        std::cout << "--------------영화 정보--------------" << std::endl;
        targetMovie->display();
        std::cout << "-------------------------------------" << std::endl;
        ratingManager.showByMovieId(targetMovie->getId());
    }  
}

std::vector<std::pair<int, double>> userInquiry(User* target, Recommend& recommend, UserManager& userManager){
    std::cout << "\n유저 정보를 조회합니다.\n" << std::endl;
    if(target == NULL){
        std::cout << "해당하는 유저를 찾지 못했습니다.\n" << std::endl;  
        return {};  
    }   
    else{
        int N;    
        std::cout << "유사도 상위 N명을 검색합니다. N: ";
        std::cin >> N; 
        return recommend.findSimilarUsers(target->getId(), N);
    }
}
void showSimilarUser(double selfSimilarity, const std::vector<std::pair<int, double>>& similarUser, UserManager& userManager){
    int i = 1;
    std::cout << "\n---유사한 유저---" << std::endl;
    for(std::pair<int, double> s : similarUser)
        std::cout << std::to_string(i++) + ". " << userManager.findById(s.first)->getName() << ": " << 
        std::fixed << std::setprecision(1) << (s.second / selfSimilarity) * 100<< "%" << std::endl;  
}
void recommendMovie(const std::vector<std::pair<int,double>>& resultMovie, MovieManager& movieManager){
    int M, i =0;
    std::cout << "\n\n추천 영화 수: ";
    std::cin >> M;
    if(M > (int) resultMovie.size())
        std::cout << "추천 영화의 수가 적으므로 " << resultMovie.size() << "개 영화만 출력합니다" << std::endl;
    std::cout << "\n추천 영화\n\n";
    std::cout << "순위      영화 제목 (개봉년도)                         장르         평점 평점수" << std::endl;
    std::cout << "-------------------------------------------------------------------------------" << std::endl;

    std::cout << std::left;
    for(const std::pair<int, double>& r : resultMovie){
        if(i++ >= M)
            break;
        std::cout << std::setw(10) << std::to_string(i) + ". " << *(movieManager.findById(r.first)) << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------------\n" << std::endl;
}
void showFiltered(const std::vector<std::pair<int,double>>& resultMovie, Recommend& recommend, MovieManager& movieManager){
    int M, i = 0;
    std::string genre;
    std::cout << "\n\n추천 영화 수: ";
    std::cin >> M;
    std::cout << "장르: ";
    std::cin.ignore();
    std::getline(std::cin, genre);
    std::vector<std::pair<int, double>> filtered = recommend.filterByGenre(resultMovie, genre);
    if(M > (int) filtered.size())
        std::cout << "추천 영화의 수가 적으므로 " << filtered.size() << "개 영화만 출력합니다" << std::endl;
    std::cout << "\n추천 영화\n\n";
    std::cout << "순위      영화 제목 (개봉년도)                         장르         평점 평점수" << std::endl;
    std::cout << "-------------------------------------------------------------------------------" << std::endl;

    std::cout << std::left;
    for(const std::pair<int, double>& r : filtered){
        if(i++ >= M)
            break;
        std::cout << std::setw(10) << std::to_string(i) + ". " << *(movieManager.findById(r.first)) << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------------\n" << std::endl;
}

