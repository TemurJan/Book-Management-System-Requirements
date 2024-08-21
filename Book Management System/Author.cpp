#include "Author.h"

Author::Author(std::string name) :name(name) {}

const std::string Author::getName() const 
{
	return name;
}

bool Author::operator==(const Author& other) const 
{
    return name == other.name;
}