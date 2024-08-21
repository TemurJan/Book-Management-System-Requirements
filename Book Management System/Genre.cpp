#include "Genre.h"

Genre::Genre(std::string genre) :genre(genre) {}

const std::string Genre::getGenre() const 
{
	return genre;
}

bool Genre::operator==(const Genre& other) const 
{
    return genre == other.genre;
}

void Genre::inputGenre()
{
    std::string input;
    std::cin >> input;
    genre = input;
}

