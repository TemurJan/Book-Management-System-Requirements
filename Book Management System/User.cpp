#include "User.h"  
#include <fstream>  
#include <iostream>  
#include "../../include/json.hpp"
#include <regex>

using json = nlohmann::json;

std::vector<User> load_users(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<User> users;
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();
        users = j.get<std::vector<User>>();
    }
    else {
        std::cerr << "Could not open file for reading." << std::endl;
    }
    return users;
}

void save_users(const std::vector<User>& users, const std::string& filename)
{
    std::ofstream file(filename);
    if (file.is_open()) {
        json j = users;
        file << j.dump(4); // Pretty print with 4 spaces  
        file.close();
    }
    else
    {
        std::cerr << "Could not open file for writing." << std::endl;
    }
}

std::pair<int, std::string> login(const std::vector<User>& users)
{
    std::string username, password;
    std::cout << "  Enter your email: ";
    std::cin >> username;
    std::cout << "  Enter your password: ";
    std::cin >> password;

    for (const auto& user : users)
    {
        if (user.email == username && user.password == password)
        {
            std::cout << "  Login successful!" << std::endl;
            if (user.role == Admin)
                return { 1,user.username };
            return { 0,user.username };
        }
    }
    std::cout << " Invalid username or password." << std::endl;
    std::cout << " If you want go outside select 2 else any symbol from your keyboard" << std::endl;
    return { -1,"Nan" };
}

std::pair<int, std::string> sign_up(std::vector<User>& users)
{
    std::string username, email, password;
    std::cout << "Create a username: ";
    std::cin >> username;
    std::cout << "Enter your email: ";
    std::cin >> email;
    const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    while(!std::regex_match(email, pattern))
    {
        std::cout << "Your input isn't password, try again:  ";
        std::cin >> email;
        const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    } 

    std::cout << " Create a password: ";
    std::cin >> password;
    while (password.size() < 8)
    {
        std::cout << " Password must have 8 symbols, try again:  ";
        std::cin >> password;
    } 

    for (const auto& user : users)
    {
        if (user.email == email)
        {
            std::cout << "Username already exists." << std::endl;
            return{ 1,"Nan" };
        }
    }

    users.emplace_back(username, email, password);
    std::cout << "Sign up successful!" << std::endl;
    return{ 1,"Nan" };
}