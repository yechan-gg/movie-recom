#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "BaseManager.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h" 
#include "Recommend.h"

void showStatus();
void addMovie(MovieManager& movieManager);
Movie* findMovie(MovieManager& movieManager, std::string title);
User* findMovie(UserManager& userManager, std::string name);
void searchMovie(MovieManager& movieManager);
void showMovie(const MovieManager& movieManager);
void addUser(UserManager& userManager);
void showUser(const UserManager& userManager);
void addRating(MovieManager& movieManager, UserManager& userManager, RatingManager& ratingManager);
void showRatings(MovieManager& movieManager, RatingManager& ratingManager);
void recommendMovie(MovieManager& movieManager, RatingManager& ratingManager);

int main() {
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;
    int command;
    bool isContinued = true;
    movieManager.loadFromFile("data/movies.csv");
    movieManager.loadRating("data/ratings.csv");
    userManager.loadFromFile("data/users.csv");
    ratingManager.loadFromFile("data/ratings.csv");
    while(true){
        if(!isContinued)
            break;

        showStatus();
        std::cin >> command; 
        switch(command){
            case 1:
                addMovie(movieManager);
                break;
            case 2:
                searchMovie(movieManager);
                break;
            case 3:
                showMovie(movieManager);
                break;
            case 4:
                movieManager.sortByRating();
                showMovie(movieManager);
                break;
            case 5:
                addUser(userManager);
                break;
            case 6:
                showUser(userManager);
                break;
            case 7:
                addRating(movieManager, userManager, ratingManager);
                break;
            case 8:
                showRatings(movieManager, ratingManager);
                break;
            case 9:{
                recommendMovie(movieManager, ratingManager);
                break;
            }
                
            case 0:
                std::cout << "프로그램 종료" << std::endl;
                isContinued = false;
                break;
            default:
                std::cout << "0 에서 8 사이의 정수를 입력해주세요." << std::endl;
        }
    }
    movieManager.sortById();    // 정렬해서 저장
    ratingManager.sortByUId();
    movieManager.saveToFile("data/movies.csv");
    userManager.saveToFile("data/users.csv");
    ratingManager.saveToFile("data/ratings.csv");
    return 0;
}


void showStatus(){
    std::cout << "=== Movie Recommender ===\n" << std::endl;
    std::cout << "[ 영화 ]" << std::endl;
    std::cout << " 1. 영화 추가\n" <<
                " 2. 제목으로 검색\n" <<
                " 3. 전체 목록 출력\n" <<
                " 4. 평점순 정렬 출력\n" << std::endl;

    std::cout << "[ 사용자 ]" << std::endl;
    std::cout << " 5. 사용자 추가\n" <<
                " 6. 사용자 목록 출력\n" << std::endl;

    std::cout << "[ 평점 ]" << std::endl;
    std::cout << " 7. 평점 입력\n" <<
                " 8. 영화별 평점 보기\n" <<
                " 9. 영화 추천\n\n" <<
                " 0. 종료\n\n" <<
                "선택 > ";    
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

    std::cout << "\n영화의 평점 목록을 출력합니다\n" << std::endl;
    std::cout << "영화 제목 or ID: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);

    Movie* target = findMovie(movieManager, movieTitle);
    if(target == NULL)
        std::cout << "해당하는 영화를 찾지 못했습니다.\n" << std::endl;       
    else
        target->display();

    std::cout << std::endl;
}
void showMovie(const MovieManager& movieManager){
    std::cout << "\n영화 목록 출력\n\n\n" << std::endl;
    movieManager.showAll();
    std::cout << "\n\n\n\n" << std::endl;
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
    std::cout << "\n전체 유저 목록 출력\n\n\n" << std::endl;
    userManager.showAll();
    std::cout << "\n\n\n\n" << std::endl;
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
        ratingManager.showByMovieId(targetMovie->getId());
    }  
    std::cout << "\n" << std::endl;
}
void recommendMovie(MovieManager& movieManager, RatingManager& ratingManager){
    int userId;
    std::vector<std::pair<int, double>> similarUser;
    Recommend recommend(movieManager.getMovies(), ratingManager.getRatings(), ratingManager.getUIds());
    std::cout << "\n===영화를 추천합니다===\n" << std::endl;
    std::cout << "유저 ID: ";
    std::cin >> userId;
    
    int N;    
    std::cout << "유사도 상위 N명을 검색합니다. N: ";
    std::cin >> N; 
    similarUser = recommend.findSimilarUsers(userId, N);
    if((int) similarUser.size() == 0){
        std::cout << "사용자의 평점 수가 너무 적습니다. 평점을 추가해주세요.\n" << std::endl;
    }
    else{
        std::cout << "---유사도가 높은 상위 " << N <<"명의 유저---" << std::endl;
        for(std::pair<int, double> i : similarUser){
            std::cout << "user " << i.first << " ";
        }
        std::cout << "\n\n";

        int M;
        std::cout << "추천받을 영화의 수: ";
        std::cin >> M;
        std::cout << "\n===추천 영화===\n";
        for(int i : recommend.recommendMovie(userId, similarUser, M)){
            std::cout << *(movieManager.findById(i)) << std::endl;
        }
        std::cout << std::endl;
    }
    
}

