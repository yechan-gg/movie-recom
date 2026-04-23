#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

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


int main() {
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;
    int command;
    bool keepGoing = 1;
    int movieId, movieYear, userId, score;
    std::string movieTitle, movieGenre, userName, userEmail;

    while(keepGoing){
        showStatus();
        std::cin >> command; 
        switch(command){
            case 1:
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
                break;
            case 2:
                std::cout << "\n찾으려는 영화의 제목을 입력하세요: ";
                std::cin.ignore();
                std::getline(std::cin, movieTitle);
                movieManager.findByTitle(movieTitle)->display();
                std::cout << std::endl;
                break;
            case 3:
                std::cout << "\n===전체 영화 목록 출력=====\n" << std::endl;
                movieManager.showAll();
                std::cout << "\n===========================\n" << std::endl;
                break;
            case 4:
                std::cout << "\n===평점순 영화 목록 출력(내림차순)===\n" << std::endl;    
                movieManager.sortByRating();
                movieManager.showAll();
                std::cout << "\n====================================\n" << std::endl;
                break;
            case 5:
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
                break;
            case 6:
                std::cout << "\n===전체 유저 목록 출력===\n" << std::endl;
                userManager.showAll();
                std::cout << "\n========================\n" << std::endl;
                break;
            case 7:
                std::cout << "\n====평점을 입력합니다===\n" << std::endl;
                std::cout << "유저 ID: ";
                std::cin >> userId;
                
                std::cout << "영화 ID: ";
                std::cin >> movieId;

                std::cout << "평점: ";
                std::cin >> score;
                ratingManager.addRating(Rating(userId, movieId, score), movieManager);
                break;
            case 8:
                std::cout << "\n===영화의 평점 목록을 출력합니다===\n" << std::endl;
                std::cout << "영화 제목: ";
                std::cin.ignore();
                std::getline(std::cin, movieTitle);
                ratingManager.showByMovieId(movieManager.findByTitle(movieTitle) -> getId());
                std::cout << "\n==================================\n" << std::endl;
                break;
            case 0:
                std::cout << "프로그램 종료" << std::endl;
                keepGoing = 0;
                break;
            default:
                std::cout << "0 에서 8 사이의 정수를 입력해주세요." << std::endl;
        }
    }
    return 0;
}