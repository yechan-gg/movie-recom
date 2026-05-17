#pragma once
#include <string>

class Movie {
private:
    int         id;
    std::string title;
    std::string genre;
    int         releaseYear;
    double      totalRating; 
    int         ratingCount;    

public:
    Movie();                  
    Movie(int id, const std::string& title, const std::string& genre, int year);
    Movie(int id, const std::string& title, const std::string& genre, int year, double totalRating, int ratingCount);
    
    int         getId()              const;
    std::string getTitle()           const;
    std::string getGenre()           const;
    int         getReleaseYear()     const;  
    double      getTotalRating()     const;
    int         getRatingCount()     const;
    double      getAverageRating()   const;  
      

    void addRating(double r);               
    void display()               const;

    bool operator==(const Movie& other) const;  //연산자 오버로딩
    bool operator!=(const Movie& other) const;
    bool operator<(const Movie& other) const;   
    bool operator>(const Movie& other) const;
    bool operator<=(const Movie& other) const;
    bool operator>=(const Movie& other) const;

    
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);
};