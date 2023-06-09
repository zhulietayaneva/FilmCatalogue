#include "Movie.h"
#include <fstream> 
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>


void Movie::setTitle(std::string val) {
	if (val.length() < 101)
	{
		_title = val;
	}
	else
	{
		throw std::length_error("Title length exceeds the maximum allowed length.");
	}
}

Movie::Movie(const std::string& title, const std::string& director, int releaseYear, const Time& startTime, int duration) : _director(director), _releaseYear(releaseYear), _startTime(startTime), _duration(duration) {
	setTitle(title);
}

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

std::istream& operator>>(std::istream& input, Time& time) {
	input >> time.hours >> time.minutes;
	return input;
}
std::istream& operator>>(std::istream& in, Movie& obj)
{

	in >> obj._title;
	in >> obj._director;
	in >> obj._releaseYear;
	in >> obj._startTime;
	in >> obj._duration;

	return in;
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
	os << "Title: " << movie.getTitle() << std::endl;
	os << "Director: " << movie.getDirector() << std::endl;
	os << "Year: " << movie.getReleaseYear() << std::endl;
	std::string min = movie.getStartTime().minutes < 10 ? "0" : "";
	os << "Start Time: " << movie.getStartTime().hours << ":" << min << movie.getStartTime().minutes << std::endl;
	os << "Duration: " << movie.getDuration() << " minutes" << std::endl;

	return os;
}

const void Movie::serialize(std::ofstream& file) const
{
	if (!file.is_open()) {
		throw std::runtime_error("File is not open.");
	}
	file << "Release Year: " << this->getReleaseYear()<< std::endl;	
	file << "Title: " << this->getTitle() << std::endl;
	file << "Director: " << this->getDirector() << std::endl;
	file << "Start Time: " << this->getStartTime().hours << ':' << this->getStartTime().minutes << std::endl;
	file << "Duration: " << this->getDuration() << std::endl;
	file <<  std::endl;
}
const void Movie::deserialize(std::ifstream& file)
{
	if (!file.is_open()) {
		throw std::runtime_error("File is not open.");
	}
	
	std::string line;
	std::string title, director;
	int year, startHour, startMinute, duration;

	
	file.seekg(file.tellg());
	std::getline(file, line);
	year = std::stoi(line.substr(line.find(": ") + 2));


	std::getline(file, line);
	title = line.substr(line.find(": ") + 2);

	std::getline(file, line);
	director = line.substr(line.find(": ") + 2);

	std::getline(file, line);
	std::stringstream timeStream(line.substr(line.find(": ") + 2));
	timeStream >> startHour >> startMinute;
	
	std::getline(file, line);
	duration = std::stoi(line.substr(line.find(": ") + 2));



}


