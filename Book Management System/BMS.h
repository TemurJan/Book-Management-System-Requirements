#pragma once
#include "../../include/json.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include "Book.h"
#include "Genre.h"
#include "Author.h"

class BMS
{
public:
    
    std::vector<Book> load_books(const std::string& filename)
    {
        std::ifstream file(filename);
        std::vector<Book> books;
        if (file.is_open())
        {
            nlohmann::json j;
            file >> j;
            file.close();
            books.reserve(j.size());
            for (const auto& bookData : j)
            {
                Book book;
                bookData.get_to(book);
                books.emplace_back(std::move(book));
            }
        }
        else
        {
            std::cerr << "Could not open file for reading." << std::endl;
        }
        return books;
    }
    

    void save_books(const std::vector<Book>& books, const std::string& filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            nlohmann::json j = books;
            file << j.dump(4);
            file.close();
        }
        else
        {
            std::cerr << "Could not open file for writing." << std::endl;
        }
    }

    void RemoveBook(std::vector<Book>& books)
    {
        std::string title;
        std::size_t year;
        std::vector<Author> authors;
        std::string authorName;
        char addMore = 'n';

        std::cout << " Enter the title of the book to remove: ";
        std::getline(std::cin >> std::ws, title);

        do
        {
            std::cout << " Enter an author's of the book to remove: ";
            std::getline(std::cin >> std::ws, authorName);
            authors.emplace_back(authorName);

            std::cout << " Would you like to add another author? (y/n): ";
            std::cin >> addMore;
        } while (tolower(addMore) == 'y');

        std::cout << " Enter the publication year of the book to remove: ";
        std::cin >> year;

        auto it = std::remove_if(books.begin(), books.end(), [&title, year, &authors](const Book& book) {
            return  book.getTitle() == title &&
                    book.getYear() == year &&
                    book.getAuthors() == authors;
            });

        if (it != books.end())
        {
            books.erase(it, books.end());
            std::cout << "  Book removed successfully!" << std::endl;
        }
        else
        {
            std::cout << "  Book not found in the collection." << std::endl;
        }
    }


    void AddBook(std::vector<Book>& books)
    {
        std::string title, description;
        std::cout << "Enter the book title: ";
        std::getline(std::cin >> std::ws, title);
        std::cout << "Enter the book description: ";
        std::getline(std::cin >> std::ws, description);

        std::vector<Genre> genreSet;
        std::string genreInput;
        char addMore = 'n';
        do
        {
            std::cout << "Enter a genre: ";
            std::getline(std::cin >> std::ws, genreInput);
            genreSet.emplace_back(genreInput);

            std::cout << "Would you like to add another genre? (y/n): ";
            std::cin >> addMore;
        } while (tolower(addMore) == 'y');

        std::vector<Author> authorSet;
        std::string authorName;
        do
        {
            std::cout << "Enter author's name: ";
            std::getline(std::cin >> std::ws, authorName);
            authorSet.emplace_back(authorName);

            std::cout << "Would you like to add another author? (y/n): ";
            std::cin >> addMore;
        } while (tolower(addMore) == 'y');

        std::size_t year;
        std::cout << "Enter the publication year: ";
        std::cin >> year;

        Book newBook(title, description, genreSet, authorSet, year);

        bool bookExists = false;
        for (const auto& book : books)
        {
            if (book.getTitle() == newBook.getTitle() &&
                book.getYear() == newBook.getYear() &&
                book.getGener() == newBook.getGener() &&
                book.getAuthors() == newBook.getAuthors())
            {
                bookExists = true;
                break;
            }
        }

        if (bookExists)
        {
            std::cout << "This book already exists in the collection." << std::endl;
        }
        else
        {
            books.emplace_back(std::move(newBook));
            std::cout << "Book added successfully!" << std::endl;
        }
    }

    void ViewBooks(const std::vector<Book>& books) const
    {
        if (books.empty())
        {
            std::cout << "No books available in the collection." << std::endl;
            return;
        }

        for (const auto& book : books)
        {
            std::cout << "Title: " << book.getTitle() << std::endl;
            std::cout << "Description: " << book.getDescription() << std::endl;
            std::cout << "Publication Year: " << book.getYear() << std::endl;

            std::cout << "Genres: ";
            for (const auto& genre : book.getGener())
            {
                std::cout << genre.getGenre() << " "; 
            }
            std::cout << std::endl;

            std::cout << "Authors: ";
            for (const auto& author : book.getAuthors())
            {
                std::cout << author.getName() << " "; 
            }
            std::cout << std::endl;

            std::cout << "----------------------------" << std::endl;
        }
    }

    void SearchBooks(const std::vector<Book>& books) const
    {
        std::string searchOption;
        std::cout << "Search by: 1) Title, 2) Author, 3) Genre: ";
        std::cin >> searchOption;

        std::cin.ignore(); // Clear the input buffer

        if (searchOption[0] == '1' and searchOption.size() == 1)
        {
            std::string title;
            std::cout << "Enter the title: ";
            std::getline(std::cin, title);

            for (const auto& book : books)
            {
                if (book.getTitle().find(title) != std::string::npos)
                {
                    displayBook(book);
                }
            }
        }
        else if (searchOption[0] == '2' and searchOption.size() == 1)
        {
            std::string authorName;
            std::cout << "Enter the author's name: ";
            std::getline(std::cin, authorName);

            for (const auto& book : books)
            {
                for (const auto& author : book.getAuthors())
                {
                    if (author.getName().find(authorName) != std::string::npos)
                    {
                        displayBook(book);
                        break; 
                    }
                }
            }
        }
        else if (searchOption[0] == '3' and searchOption.size() == 1)
        {
            std::string genreName;
            std::cout << "Enter the genre: ";
            std::getline(std::cin, genreName);

            for (const auto& book : books)
            {
                for (const auto& genre : book.getGener())
                {
                    if (genre.getGenre().find(genreName) != std::string::npos)
                    {
                        displayBook(book);
                        break; 
                    }
                }
            }
        }
        else
        {
            std::cout << "Invalid option selected." << std::endl;
        }
    }

    void displayBook(const Book& book) const
    {
        std::cout << "Title: " << book.getTitle() << std::endl;
        std::cout << "Description: " << book.getDescription() << std::endl;
        std::cout << "Publication Year: " << book.getYear() << std::endl;

        std::cout << "Genres: ";
        for (const auto& genre : book.getGener())
        {
            std::cout << genre.getGenre() << " ";
        }
        std::cout << std::endl;

        std::cout << "Authors: ";
        for (const auto& author : book.getAuthors())
        {
            std::cout << author.getName() << " ";
        }
        std::cout << std::endl;

        std::cout << "----------------------------" << std::endl;
    }

    void AddToFavorites(User& user, const std::vector<Book>& library)
    {
        std::string title;
        std::cout << "Enter the title of the book to add to favorites: ";
        std::getline(std::cin >> std::ws, title);

        auto it = std::find_if(library.begin(), library.end(), [&title](const Book& book) {
            return book.getTitle() == title;
            });

        if (it != library.end())
        {
            user.addToFavorites(*it);
            std::cout << "Book added to favorites!" << std::endl;
        }
        else
        {
            std::cout << "Book not found in the library." << std::endl;
        }
    }

    void ViewFavorites(User& user)
    {
        auto& favorites = user.getFavorites();
        if (favorites.empty())
        {
            std::cout << "Your favorites list is empty." << std::endl;
            return;
        }

        std::cout << "Your favorite books:\n";
        for (const auto& book : favorites)
        {
            std::cout << book.getTitle() << " by ";
            for (const auto& author : book.getAuthors())
            {
                std::cout << author.getName() << " ";
            }
            std::cout << " (" << book.getYear() << ")\n";
        }
    }

    void RemoveFromFavorites(User& user)
    {
        std::string title;
        std::cout << "Enter the title of the book to remove from favorites: ";
        std::getline(std::cin >> std::ws, title);

        auto& favorites = user.getFavorites();
        auto it = std::remove_if(favorites.begin(), favorites.end(), [&title](const Book& book) {
            return book.getTitle() == title;
            });

        if (it != favorites.end())
        {
            favorites.erase(it, favorites.end());
            std::cout << "Book removed from favorites!" << std::endl;
        }
        else
        {
            std::cout << "Book not found in your favorites list." << std::endl;
        }
    }
};


