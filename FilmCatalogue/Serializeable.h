#pragma once
#include <iostream>

class Serializeable
{
public:
	const virtual void serialize(std::ofstream& file) const = 0;
	const virtual void deserialize(std::ifstream& file, int line=0) = 0;
};

