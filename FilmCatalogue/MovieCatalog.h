#pragma once
#include "Serializeable.h"
#include "Movie.h"
#include <vector>

struct Date {
    int day;
    int month;
    int year;
};

class MovieCatalog : public Serializeable {
private:
    std::string _cinemaName;
    Date _projectionDate;
    std::vector<Movie> _movies;

   const bool fileExists(const std::string& name);
   const std::string getCinemaNameFromFileName(const std::string& fileName);
   const bool isMovieInTimeInterval(const Movie& movie, const Time& startTime, const Time& endTime);
   const Time calculateEndTime(const Time& startTime, int duration);

public:
    MovieCatalog(const std::string& fileName);
    ~MovieCatalog();
  
    void addMovie(const Movie& movie);
    void removeMovie(const std::string& movieTitle) ;
    Movie* findMovie(const std::string& movieTitle);
    int getMoviesCountInTimeInterval(const Time& startTime, const Time& endTime);

    const void serialize(std::ofstream& file) const override;
    const void deserialize(std::ifstream& file) override;
};


