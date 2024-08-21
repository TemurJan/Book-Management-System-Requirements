#include <vector>
#include <string>
#include "Book.h"
#include <fstream>

using json = nlohmann::json;
/*
std::vector<Book> load_books(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<Book> users;
    if (file.is_open()) 
    {
        json j;
        file >> j;
        file.close();
        users = j.get<std::vector<Book>>();
    }
    else 
    {
        std::cerr << "Could not open file for reading." << std::endl;
    }
    return users;
}*/

