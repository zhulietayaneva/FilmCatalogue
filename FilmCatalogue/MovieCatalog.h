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
    std::string _cinemaName = "Default Name";
    Date _projectionDate = { 0,0 };
    std::vector<Movie> _movies;

   const bool fileExists(const std::string& name);
   void setCinemaName(const std::string& val);

public:
    MovieCatalog() = default;
    MovieCatalog(const std::string& fileName);
    ~MovieCatalog();
  
    void addMovie(const Movie& movie);
    void removeMovie(const std::string& movieTitle);

    Movie* findMovie(const std::string& movieTitle);

    void changeCinemaName(const std::string& name);
    bool isMovieInTimeInterval(const Movie& movie, const Time& start, const Time& end);
    int getMoviesCountInTimeInterval(const Time& startTime, const Time& endTime);
    const std::string getCinemaName() const;
    const Date getDate() const;
    const std::vector<Movie> getMovies() const;
    const int getMoviesCount() const;

    friend std::istream& operator>> (std::istream& in, MovieCatalog& obj);
    friend std::ostream& operator<<(std::ostream& os, const Date& obj);
    friend std::ostream& operator<< (std::ostream& out, const MovieCatalog& obj);
    const void serialize(std::ofstream& file) const override;
    const void deserialize(std::ifstream& file) override;
};


