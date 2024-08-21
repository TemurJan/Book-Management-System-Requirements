#ifndef USER_H  
#define USER_H  

#include <string>  
#include <vector>   
#include "../../include/json.hpp"
#include <regex> 
#include <iostream> 
#include "Book.h"

enum Role { Users = 0, Admin = 1 };

class User
{
public:
    std::string username;
    std::string email;
    std::string password;
    Role role = Users;
    std::vector<Book> favoriteBooks;
    bool isEmail(const std::string& email)
    {
        const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
        return std::regex_match(email, pattern);
    }
public:
    User() = default;
    User(const std::string& user, const std::string& mail, const std::string& pass, const Role& role = Users)
        : username(user), email(mail), password(pass), role(role)
    {
        while (!isEmail(email))
        {
            std::cout << "Your input isn't  a valid email address ... Try again\n ";
            std::cin >> email;
        }
    }

    std::vector<Book>& getFavorites() 
    {
        return favoriteBooks;
    }

    void addFavorite(const Book& book)
    {
        favoriteBooks.push_back(book);
    }

    void removeFavorite(const std::string& title)
    {
        favoriteBooks.erase(std::remove_if(favoriteBooks.begin(), favoriteBooks.end(), [&title](const Book& book) {
            return book.getTitle() == title;
            }), favoriteBooks.end());
    }

    const std::string& getUsername() const
    {
        return username;
    }

    void addToFavorites(const Book& book)
    {
        for (const auto& favBook : favoriteBooks)
        {
            if (favBook.getTitle() == book.getTitle() &&
                favBook.getYear() == book.getYear() &&
                favBook.getAuthors() == book.getAuthors())
            {
                std::cout << "This book is already in your favorites list." << std::endl;
                return;
            }
        }
        favoriteBooks.emplace_back(book);
        std::cout << "Book added to your favorites list!" << std::endl;
    }

    friend void to_json(nlohmann::json& j, const User& user)
    {
        j = nlohmann::json{ {"username", user.username}, {"email", user.email}, {"password", user.password}, {"role", user.role} };
    }

    friend void from_json(const nlohmann::json& j, User& user)
    {
        j.at("username").get_to(user.username);
        j.at("email").get_to(user.email);
        j.at("password").get_to(user.password);
        j.at("role").get_to(user.role);
    }

};

std::vector<User> load_users(const std::string& filename);
void save_users(const std::vector<User>& users, const std::string& filename);
std::pair<int, std::string> login(const std::vector<User>& users);
std::pair<int, std::string> sign_up(std::vector<User>& users);

#endif // USER_H