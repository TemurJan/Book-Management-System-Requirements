#pragma once  
#include <iostream>  
#include <string>  
#include "../../include/json.hpp"

class Genre
{
private:
    std::string genre;
public:
    Genre() = default;

    Genre(std::string genre);

    const std::string getGenre()const;

    void inputGenre();

    bool operator==(const Genre& other) const;

    friend void to_json(nlohmann::json& j, const Genre& g) 
    {
        j = nlohmann::json{ {"genre", g.genre} };
    }

    friend void from_json(const nlohmann::json& j, Genre& g) 
    {
        j.at("genre").get_to(g.genre);
    }
};


