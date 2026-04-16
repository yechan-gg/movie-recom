#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
int main() {

    MovieManager movieManager;

    movieManager.addMovie(Movie(1, "기생충", "드라마", 2019));
    movieManager.addMovie(Movie(2, "인터스텔라", "SF", 2014));
    movieManager.display();
    movieManager.findByTitle("인터스텔라")->display();
    movieManager.removeMovie("인터스텔라");
    movieManager.display();


    return 0;
}