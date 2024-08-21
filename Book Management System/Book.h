#pragma once  
#include <string>  
#include "Author.h"  
#include "Genre.h"  
#include <set> 
#include "../../include/json.hpp"  

using json = nlohmann::json;

class Book
{
private:
    std::string title;
    std::string description;
    std::vector<Genre> genre;
    std::vector<Author> authors;
    std::size_t year;
public:
    Book(std::string title, std::string description, std::vector<Genre> genre, std::vector<Author> authors, std::size_t year);

    Book() = default;

    std::string getTitle()const;

    std::string getDescription()const;

    std::vector<Genre> getGener() const;

    std::vector<Author> getAuthors() const;

    std::size_t getYear() const;

    bool empty() const;

    void printBook() const;

    // Serialization and deserialization  
    friend void to_json(nlohmann::json& j, const Book& book)
    {
        j = nlohmann::json{ {"title", book.title}, 
                            {"description", book.description}, 
                            {"genre", book.genre}, 
                            {"authors", book.authors},
                            {"year",book.year}};
    }

    friend void from_json(const nlohmann::json& j, Book& book)
    {
        j.at("title").get_to(book.title);
        j.at("description").get_to(book.description);
        j.at("genre").get_to(book.genre);
        j.at("authors").get_to(book.authors);
        j.at("year").get_to(book.year);
    }


};