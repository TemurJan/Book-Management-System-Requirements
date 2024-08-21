#include "Book.h" 

Book::Book(std::string title, std::string description, std::vector<Genre> genre, std::vector<Author> authors, std::size_t year)
	: title(title)
	, description(description)
	, genre(std::move(genre))
	, authors(std::move(authors))
	, year(year) {}


std::string Book::getTitle()const
{
	return title;
}

std::vector<Genre> Book::getGener() const
{
	return genre;
}

std::vector<Author> Book::getAuthors() const
{
	return authors;
}

std::size_t Book::getYear() const
{
	return year;
}

std::string Book::getDescription()const
{
	return description;
}

bool Book::empty() const
{
	return genre.size() == 0;
}

void Book::printBook() const
{
	std::cout << "Title: " << title << "\n" << "Description: " << description << "\n";
	for (auto& elem : genre)
		std::cout << elem.getGenre() << " ";
	std::cout << "\n";

	for (auto& elem : authors)
		std::cout << elem.getName() << " ";
	std::cout << "\n";
	std::cout << "Year: " << year << "\n";
	std::cout << std::endl;
}