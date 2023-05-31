#pragma once
#include "Serializeable.h"
#include <fstream>
#include <string>

struct Time {
    int hours;
    int minutes;
};

class Movie: public Serializeable
{
private:
    std::string _title;
    std::string _director;
    int _releaseYear;
    Time _startTime;
    int _duration;
public:

    Movie() = default;
    Movie(const std::string& title, const std::string& director, int releaseYear, const Time& startTime, int duration)
        : _title(title), _director(director), _releaseYear(releaseYear), _startTime(startTime), _duration(duration) {}
    const std::string getTitle() const;
    const std::string getDirector() const;
    const int getReleaseYear() const;
    const Time getStartTime() const;
    const int getDuration() const;
    
    const void serialize(std::ofstream& file)const override;
    const void deserialize(std::ifstream& file) override;


};

