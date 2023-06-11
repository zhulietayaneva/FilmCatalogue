#include "MovieCatalog.h"
#include <cstring>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>



const bool MovieCatalog::fileExists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void MovieCatalog::setCinemaName(const std::string& val)
{
    if (val.empty())
    {
        throw std::invalid_argument("Invalid input argument: Empty cinema name.");

    }
    else
    {
        _cinemaName = val;
    }
}

MovieCatalog::MovieCatalog(const std::string& fileName) {
   
        std::ifstream f(fileName);
    if (fileExists(fileName) && f.is_open()) {
        
        this->deserialize(f);
        f.close();
    }
    else{
        _cinemaName = fileName.substr(0, fileName.find_last_of("."));
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);
       _projectionDate.year= localTime->tm_year + 1900;
       _projectionDate.month= localTime->tm_mon + 1;
       _projectionDate.day= localTime->tm_mday;
    }
}
MovieCatalog::~MovieCatalog() {
    std::ofstream file(_cinemaName + ".txt", std::ios::binary);
    if (file.is_open()) {
        serialize(file);
        file.close();
    }
}


 void MovieCatalog::addMovie(const Movie& movie) {
    _movies.push_back(movie);
}
 void MovieCatalog::removeMovie(const std::string& movieTitle) {
   
     for (size_t i = 0; i < _movies.size(); i++)
     {
         if (&_movies[i]==findMovie(movieTitle))
         {
             _movies.erase(_movies.begin() + i);
             break; 
         }
     }
}

Movie* MovieCatalog::findMovie(const std::string& movieTitle) {
    
    for (auto& m : _movies)
    {
        if (m.getTitle()._Equal(movieTitle))
        {
            return &m;
        }
    }

    return nullptr;
}



void MovieCatalog::changeCinemaName(const std::string& name)
{
    this->setCinemaName(name);

}

bool MovieCatalog::isMovieInTimeInterval(const Movie& movie, const Time& start, const Time& end) {
    
    int startTimeMinutes = start.hours * 60 + start.minutes;
    int endTimeMinutes = end.hours * 60 + end.minutes;
    
    int movieStartTimeMinutes = movie.getStartTime().hours * 60 + movie.getStartTime().minutes;
    int movieEndTimeMinutes = movie.getStartTime().hours * 60 + movie.getStartTime().minutes + movie.getDuration();

    return (movieStartTimeMinutes >= startTimeMinutes) &&
           (movieEndTimeMinutes <= endTimeMinutes);


}
int MovieCatalog::getMoviesCountInTimeInterval(const Time& startTime, const Time& endTime) {
    int count = 0;

    for (const Movie& movie : _movies) {
        if (isMovieInTimeInterval(movie, startTime, endTime)) {
            count++;
            //std::cout << movie;
        }
    }
      
    return count;
}
const std::string MovieCatalog::getCinemaName() const
{
    return _cinemaName;
}
const Date MovieCatalog::getDate() const
{
    return _projectionDate;
}
const std::vector<Movie> MovieCatalog::getMovies() const
{
    return _movies;
}
const int MovieCatalog::getMoviesCount() const
{
    return (int)_movies.size();
}


std::istream& operator>>(std::istream& in, Date& time) {
    in >> time.day >> time.month>> time.year;
    return in;
}
std::istream& operator>>(std::istream& in, MovieCatalog& obj)
{   
    in >> obj._cinemaName;
    in.ignore();
    in >> obj._projectionDate;
    in.ignore();
    for (auto& movie : obj._movies) {
        in >> movie;
        in.ignore();
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, const Date& obj)
{
    out << obj.day << "." << obj.month << "." << obj.year << std::endl;
    return out;
}
std::ostream& operator<< (std::ostream& out, const MovieCatalog& obj)
{
    out << obj.getCinemaName() << "\n" << obj.getDate() << std::endl;
    
    for (size_t i = 0; i < obj.getMovies().size() ; i++)
    {
        out << obj.getMovies()[i] << std::endl;
    }

    return out;
}


const void MovieCatalog::serialize(std::ofstream& file) const {
    if (!file.is_open()) {
        throw std::runtime_error("File is not open.");
    }

    file << _cinemaName << std::endl;
    file << _projectionDate << std::endl;
    for  (auto& m : _movies)
    {
        m.serialize(file);
    }
    file.close();
}
const void MovieCatalog::deserialize(std::ifstream& file)
{
   
    std::string line;

    std::getline(file, line);
    _cinemaName = line;   

    std::getline(file, line);
    
    std::istringstream dateStream(line);
    int day, month, year;
    char dot1, dot2;
    dateStream >> day >> dot1 >> month >> dot2 >> year;
    _projectionDate = { day, month, year };
    
    while (std::getline(file, line)) {
        if (line.empty() ||line._Equal("\r") ||line._Equal("\r\n") || line._Equal("\r\r")) {
            continue;  
        }
        
        Movie movie; 
        movie.deserialize(file); 

        _movies.push_back(movie);
        
    }
}

