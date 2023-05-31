#include "MovieCatalog.h"
#include <cstring>
#include <iostream>
#include <ctime>

const bool MovieCatalog::fileExists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

MovieCatalog::MovieCatalog(const std::string& fileName) {
   
    if (fileExists(fileName)) {
        
        std::ifstream f(fileName);
        f.open(fileName);
        deserialize(f);
        f.close();
    }
    else {
        _cinemaName = fileName.substr(0, fileName.find_last_of("."));
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);
       _projectionDate.year= localTime->tm_year + 1900;
       _projectionDate.month= localTime->tm_mon + 1;
       _projectionDate.day= localTime->tm_mday;
    }
}

MovieCatalog::~MovieCatalog() {
    std::ofstream file(_cinemaName + ".txt");
    if (file.is_open()) {
        serialize(file);
        file.close();
    }
}

 void MovieCatalog::addMovie(const Movie& movie) {
    _movies.push_back(movie);
}

 void MovieCatalog::removeMovie(const std::string& movieTitle) {
    auto it = std::find_if(_movies.begin(), _movies.end(), [&movieTitle](const Movie& movie) {
        return movie.getTitle() == movieTitle;
        });

    if (it != _movies.end()) {
        _movies.erase(it);
    }
}

Movie* MovieCatalog::findMovie(const std::string& movieTitle) {
    auto it = std::find_if(_movies.begin(), _movies.end(), [&movieTitle](const Movie& movie) {
        return movie.getTitle() == movieTitle;
        });

    if (it != _movies.end()) {
        return &(*it);
    }

    return nullptr;
}

int MovieCatalog::getMoviesCountInTimeInterval(const Time& startTime, const Time& endTime) {
    int count = 0;

    for (const Movie& movie : _movies) {
        if (isMovieInTimeInterval(movie, startTime, endTime)) {
            count++;
        }
    }

    return count;
}

const void MovieCatalog::serialize(std::ofstream& file) const {
    if (!file.is_open()) {
        throw std::runtime_error("File is not open.");
    }

    file << _cinemaName << '\n';
}

const void MovieCatalog::deserialize(std::ifstream& file)
{
    if (!file.is_open()) {
        throw std::runtime_error("File is not open.");
    }

    std::getline(file, _cinemaName);

    file.read(reinterpret_cast<char*>(&_projectionDate), sizeof(Date));

    int moviesCount;
    file.read(reinterpret_cast<char*>(&moviesCount), sizeof(int));
    _movies.clear();
    for (int i = 0; i < moviesCount; i++) {
        Movie movie();
        movie.deserialize(file);
        _movies.push_back(movie);
    }
}
