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
    int command = 1;

    while(command){
        showStatus();
        std::cin >> command;
    }

    // movieManager.addMovie(Movie(1, "기생충", "드라마", 2019));
    // movieManager.addMovie(Movie(2, "인터스텔라", "SF", 2014));
    
    // userManager.addUser(User(1, "Kim", "kkk@sadasa.com"));
    // userManager.addUser(User(2, "Park", "PPP@weqeqw.com"));
    
    // ratingManager.addRating(Rating(1, 1, 3), movieManager);
    // ratingManager.addRating(Rating(1, 2, 4), movieManager);
    // ratingManager.addRating(Rating(2, 1, 1), movieManager);
    // ratingManager.addRating(Rating(2, 2, 2), movieManager);  
    
    // ratingManager.showAll();
    // movieManager.showAll();




    return 0;
}