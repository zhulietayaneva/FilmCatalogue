#pragma once
#include "Serializeable.h"
#include <fstream>
#include <string>
#include <stdexcept>

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

    void setTitle(std::string val);

public:

    Movie() = default;
    Movie(const std::string& title, const std::string& director, int releaseYear, const Time& startTime, int duration);
       
    const std::string getTitle() const;
    const std::string getDirector() const;
    const int getReleaseYear() const;
    const Time getStartTime() const;
    const int getDuration() const;

    friend std::istream& operator>>(std::istream& input, Time& time);
    friend std::istream& operator>>(std::istream& in, Movie& obj);
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    const void serialize(std::ofstream& file)const override;
    const void deserialize(std::ifstream& file) override;


};

