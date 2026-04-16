#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

int main() {
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;

    movieManager.addMovie(Movie(1, "기생충", "드라마", 2019));
    movieManager.addMovie(Movie(2, "인터스텔라", "SF", 2014));
    
    userManager.addUser(User(1, "Kim", "kkk@sadasa.com"));
    userManager.addUser(User(2, "Park", "PPP@weqeqw.com"));
    
    ratingManager.addRating(Rating(1, 1, 3), movieManager);
    ratingManager.addRating(Rating(1, 2, 4), movieManager);
    ratingManager.addRating(Rating(2, 1, 1), movieManager);
    ratingManager.addRating(Rating(2, 2, 2), movieManager);  
    
    ratingManager.showAll();
    movieManager.showAll();

    return 0;
}