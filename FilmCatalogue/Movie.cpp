#include "Movie.h"
#include <fstream> 
#include <cstring>
#include <iostream>


const std::string Movie::getTitle() const
{
    return _title;
}

const std::string Movie::getDirector() const
{
    return _director;
}

const int Movie::getReleaseYear() const
{
    return _releaseYear;
}

const Time Movie::getStartTime() const
{
    return _startTime;
}

const int Movie::getDuration() const
{
    return _duration;
}

const void Movie::serialize(std::ofstream& file) const
{
    if (!file.is_open()) {
        throw std::runtime_error("File is not open.");
    }
    file << this->getReleaseYear() << '\n';
    file << this->getTitle() << '\n';
    file << this->getDirector() << '\n';
    file << this->getStartTime().hours << ':' << this->getStartTime().minutes << '\n';
    file << this->getDuration() << '\n';
}

const void Movie::deserialize(std::ifstream& file)
{
    if (!file.is_open()) {
        throw std::runtime_error("File is not open.");
    }

    file >> _releaseYear;
    file.ignore(); // Ignore the newline character

    std::getline(file, _title);
    std::getline(file, _director);

    file >> _startTime.hours >> _startTime.minutes;
    file.ignore(); // Ignore the newline character

    file >> _duration;
    file.ignore();
}


