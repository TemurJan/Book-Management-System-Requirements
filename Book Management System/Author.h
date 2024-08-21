#pragma once  
#include <string>  
#include "../../include/json.hpp"

class Author
{
private:
    std::string name;
public:
    Author(std::string name);

    Author() = default;

    const std::string getName() const;

    bool operator==(const Author& other) const;

    friend void to_json(nlohmann::json& j, const Author& a) 
    {
        j = nlohmann::json{ {"name", a.name} };
    }

    friend void from_json(const nlohmann::json& j, Author& a) 
    {
        j.at("name").get_to(a.name);
    }
};



