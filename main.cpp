#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
int main() {

    MovieManager movieManager;
    UserManager userManager;
    movieManager.addMovie(Movie(1, "기생충", "드라마", 2019));
    movieManager.addMovie(Movie(2, "인터스텔라", "SF", 2014));
    movieManager.showAll();
    std::cout << std::endl;
    
    movieManager.findByTitle("인터스텔라")->display();
    std::cout << std::endl;

    movieManager.removeMovie("인터스텔라");
    movieManager.showAll();
    std::cout << std::endl;

    userManager.addUser(User(1, "Kim", "kkk@sadasa.com"));
    userManager.addUser(User(2, "Park", "PPP@weqeqw.com"));
    userManager.showAll();
    std::cout << std::endl;

    userManager.findByName("Park")->display();
    std::cout << std::endl;

    userManager.removeUser("Kim");
    userManager.showAll();
    std::cout << std::endl;

    return 0;
}