#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h" 

void showStatus();
void command1_AddMovie(MovieManager& movieManager);
void command2_FindMovie(MovieManager& movieManager);
void command3_ShowMovie(const MovieManager& movieManager);
void command4_SortAndShow(MovieManager& movieManager);
void command5_AddUser(UserManager& userManager);
void command6_ShowUser(const UserManager& userManager);
void command7_AddRating(MovieManager& movieManager, UserManager& userManager, RatingManager& ratingManager);
void command8_ShowRatings(MovieManager& movieManager, RatingManager& ratingManager);

int main() {
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;
    int command;
    bool isContinued = true;
    
    while(true){
        if(!isContinued)
            break;

        showStatus();
        std::cin >> command; 
        switch(command){
            case 1:
                command1_AddMovie(movieManager);
                break;
            case 2:
                command2_FindMovie(movieManager);
                break;
            case 3:
                command3_ShowMovie(movieManager);
                break;
            case 4:
                command4_SortAndShow(movieManager);
                break;
            case 5:
                command5_AddUser(userManager);
                break;
            case 6:
                command6_ShowUser(userManager);
                break;
            case 7:
                command7_AddRating(movieManager, userManager, ratingManager);
                break;
            case 8:
                command8_ShowRatings(movieManager, ratingManager);
                break;
            case 0:
                std::cout << "프로그램 종료" << std::endl;
                isContinued = false;
                break;
            default:
                std::cout << "0 에서 8 사이의 정수를 입력해주세요." << std::endl;
        }
    }
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
                " 8. 영화별 평점 보기\n\n" <<
                " 0. 종료\n\n" <<
                "선택 > ";    
}
void command1_AddMovie(MovieManager& movieManager){
    int movieId, movieYear;
    std::string movieTitle, movieGenre;

    std::cout << "\n===영화를 입력합니다===\n" << std::endl;
    std::cout << "영화 ID: ";
    std::cin >> movieId;
                
    std::cout << "영화 제목: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);

    std::cout << "장르: ";
    std::getline(std::cin, movieGenre);

    std::cout << "개봉년도: ";
    std::cin >> movieYear;
    std::cout << std::endl;

    movieManager.addMovie(Movie(movieId, movieTitle, movieGenre, movieYear));
}
void command2_FindMovie(MovieManager& movieManager){
    std::string movieTitle;

    std::cout << "\n찾으려는 영화의 제목을 입력하세요: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);
    if(movieManager.findByTitle(movieTitle) == NULL)
        std::cout << "해당하는 영화를 찾지 못했습니다.\n" << std::endl;       
    else
        movieManager.findByTitle(movieTitle)->display();
    std::cout << std::endl;
}
void command3_ShowMovie(const MovieManager& movieManager){
    std::cout << "\n===전체 영화 목록 출력=====\n" << std::endl;
    movieManager.showAll();
    std::cout << "\n===========================\n" << std::endl;
}
void command4_SortAndShow(MovieManager& movieManager){
    std::cout << "\n===평점순 영화 목록 출력(내림차순)===\n" << std::endl;    
    movieManager.sortByRating();
    movieManager.showAll();
    std::cout << "\n====================================\n" << std::endl;
}
void command5_AddUser(UserManager& userManager){
    int userId;
    std::string userName, userEmail;
    std::cout << "\n===사용자를 추가합니다\n" << std::endl;
    std::cout << "유저 ID: ";
    std::cin >> userId;
                
    std::cout << "유저 이름: ";
    std::cin.ignore();
    std::getline(std::cin, userName);

    std::cout << "Email: ";
    std::getline(std::cin, userEmail);
    std::cout << std::endl;

    userManager.addUser(User(userId, userName, userEmail));
}
void command6_ShowUser(const UserManager& userManager){
    std::cout << "\n===전체 유저 목록 출력===\n" << std::endl;
    userManager.showAll();
    std::cout << "\n========================\n" << std::endl;
}
void command7_AddRating(MovieManager& movieManager, UserManager& userManager, RatingManager& ratingManager){
    std::string userName, movieTitle;
    int userId, movieId, score;

    std::cout << "\n====평점을 입력합니다===\n" << std::endl;
    std::cout << "유저 이름: ";
    std::cin.ignore();
    std::getline(std::cin, userName);
    if(userManager.findByName(userName) != NULL)
        userId = userManager.findByName(userName) -> getId();
    else{
        std::cout << "해당하는 유저를 찾지 못했습니다.\n" << std::endl;
        return;
    }
    std::cout << "영화 제목: ";
    std::getline(std::cin, movieTitle);
    if(movieManager.findByTitle(movieTitle) != NULL)
        movieId = movieManager.findByTitle(movieTitle) -> getId();
    else{
        std::cout << "해당하는 영화를 찾지 못했습니다.\n" << std::endl;
        return;
    }
                
    std::cout << "평점: ";
    std::cin >> score;
    ratingManager.addRating(Rating(userId, movieId, score), movieManager);
}
void command8_ShowRatings(MovieManager& movieManager, RatingManager& ratingManager){
    std::string movieTitle;
    std::cout << "\n===영화의 평점 목록을 출력합니다===\n" << std::endl;
    std::cout << "영화 제목: ";
    std::cin.ignore();
    std::getline(std::cin, movieTitle);
    ratingManager.showByMovieId(movieManager.findByTitle(movieTitle) -> getId());
    std::cout << "\n==================================\n" << std::endl;
}
