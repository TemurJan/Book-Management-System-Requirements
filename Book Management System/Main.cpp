#include "User.h"
#include <string>
#include <cstddef>
#include "BMS.h"
#include <iostream>
#include <cstdio>

//
///**
//void printJsonFile(const std::string& filename)
//{
//    std::ifstream file(filename);
//
//    if (!file.is_open())
//    {
//        std::cerr << "Could not open file: " << filename << std::endl;
//        return;
//    }
//
//    nlohmann::json jsonData;
//    file >> jsonData;  // Load the JSON data from the file
//    file.close();
//
//    std::cout << jsonData.dump(4) << std::endl;  // Print JSON with indentation
//}
//*/
//
//
//int main() 
//{
//    std::string filename1 = "users.json";
//    std::vector<User> users = load_users(filename1);
//    std::string filename2 = "book.json";
//    std::vector<Book> library = BMS().load_books(filename2);
//
//    //printJsonFile(filename2);
//    
//    std::cout << "          Welcome to the online library!\n";
//    std::cout << "  If you want to LOGIN to our website, please select 1\n";
//    std::cout << "  If you want to SIGN UP for our website, please select 2\n";
//    std::string symbol{};
//    std::cout << "Your input:     ";
//    std::cin >> symbol;
//
//    bool flag = false;
//    do 
//    {
//            flag = false;
//            if (symbol[0] == '1' and symbol.size() == 1)
//            {
//                std::pair<int, std::string> login_call = login(users);
//                while (login_call.first == -1)
//                {
//                    char temp{};
//                    std::cout << "Your input:     ";
//                    std::cin >> temp;
//                    if (temp == '2')
//                    {
//                        std::cout << "              Have a nice day!" << std::endl;
//                        return 0;
//                    }
//                    login_call = login(users);
//                }
//                if (login_call.first == 1)
//                {
//                    std::cout << "          Hi dear " + login_call.second + " welcome our website as admin" << std::endl;
//                    do
//                    {
//                        flag = false;
//                        std::cout << "    If you want to add a book please select 1" << std::endl;
//                        std::cout << "    If you want to remove a book please select 2" << std::endl;
//                        std::cout << "    If you want to view the library select 3" << std::endl;
//                        std::cout << "    If you want to search a book in the library select 4" << std::endl;
//                        std::cout << "Your input:     ";
//                        std::cin >> symbol;
//                        if (symbol[0] == '1' && symbol.size() == 1)
//                        {
//                            //Book obj1("To Kill a Mockingbird", "This novel is set in the Depression-era South and follows young Scout Finch and her brother, Jem, as their father, lawyer Atticus Finch, defends a black man accused of raping a white woman. It addresses themes of racial injustice, moral growth, and compassion.",
//                                //Genre({ "Fiction", "Classic", "Historical" }), Authors({ "Harper Lee" }), 1960);
//                            BMS().AddBook(library);
//                        }
//                        else if (symbol[0] == '2' && symbol.size() == 1)
//                        {
//                            BMS().RemoveBook(library);
//                        }
//                        else if (symbol[0] == '3' && symbol.size() == 1)
//                        {
//                            BMS().ViewBooks(library);
//                        }
//                        else if (symbol[0] == '4' && symbol.size() == 1)
//                        {
//                            BMS().SearchBooks(library);
//                        }
//                        else
//                        {
//                            flag = true;
//                        }
//                    } while (flag);
//                }
//                else
//                {
//                    std::cout << "          Hi dear " + login_call.second + " welcome our website as user" << std::endl;
//                    do
//                    {
//                        flag = false;
//                        std::cout << "    If you want to view the library select 1" << std::endl;
//                        std::cout << "    If you want to search a book in the library select 2" << std::endl;
//                        std::cout << "    If you want to add a faviorite book in your favlist select 3" << std::endl;
//                        std::cout << "Your input:     ";
//                        std::cin >> symbol;
//                        if (symbol[0] == '1' && symbol.size() == 1)
//                        {
//                            BMS().ViewBooks(library);
//                        }
//                        else if (symbol[0] == '2' && symbol.size() == 1)
//                        {
//                            BMS().SearchBooks(library);
//                        }
//                        else if (symbol[0] == '3' && symbol.size() == 1)
//                        {
//                            /*BMS().AddToFavorites(users, library);*/
//                        }
//                        else
//                        {
//                            flag = true;
//                        }
//                    } while (flag);
//                }
//            }
//            else if (symbol[0] == '2' and symbol.size() == 1)
//            {
//                sign_up(users);
//            }
//            else
//            { 
//                flag = true;
//                std::cout << "\nYour input isn't correct. Please input the number 1 or 2: ";
//                std::cin >> symbol;
//            }
//    } while (flag);
//
//    save_users(users, filename1);
//    BMS().save_books(library, filename2);
//
//    std::cout << "End...\n";
//    return 0;
//}
//
//
//*/
int main()
{
    std::string filename1 = "users.json";
    std::vector<User> users = load_users(filename1);
    std::string filename2 = "book.json";
    std::vector<Book> library = BMS().load_books(filename2);

    std::cout << "          Welcome to the online library!\n";
    std::cout << "  If you want to LOGIN to our website, please select 1\n";
    std::cout << "  If you want to SIGN UP for our website, please select 2\n";
    std::string symbol{};
    std::cout << "Your input:     ";
    std::cin >> symbol;

    bool flag = false;
    do
    {
        flag = false;
        if (symbol[0] == '1' && symbol.size() == 1)
        {
            std::pair<int, std::string> login_call = login(users);
            while (login_call.first == -1)
            {
                char temp{};
                std::cout << "Your input:     ";
                std::cin >> temp;
                if (temp == '2')
                {
                    std::cout << "              Have a nice day!" << std::endl;
                    return 0;
                }
                login_call = login(users);
            }

            // Find the logged-in user
            User* loggedInUser = nullptr;
            for (auto& user : users)
            {
                if (user.getUsername() == login_call.second)
                {
                    loggedInUser = &user;
                    break;
                }
            }

            if (login_call.first == 1)
            {
                std::cout << "          Hi dear " + login_call.second + " welcome to our website as admin" << std::endl;
                do
                {
                    flag = false;
                    std::cout << "    If you want to add a book, please select 1" << std::endl;
                    std::cout << "    If you want to remove a book, please select 2" << std::endl;
                    std::cout << "    If you want to view the library, select 3" << std::endl;
                    std::cout << "    If you want to search for a book in the library, select 4" << std::endl;
                    std::cout << "Your input:     ";
                    std::cin >> symbol;
                    if (symbol[0] == '1' && symbol.size() == 1)
                    {
                        BMS().AddBook(library);
                    }
                    else if (symbol[0] == '2' && symbol.size() == 1)
                    {
                        BMS().RemoveBook(library);
                    }
                    else if (symbol[0] == '3' && symbol.size() == 1)
                    {
                        BMS().ViewBooks(library);
                    }
                    else if (symbol[0] == '4' && symbol.size() == 1)
                    {
                        BMS().SearchBooks(library);
                    }
                    else
                    {
                        flag = true;
                    }
                } while (flag);
            }
            else if (loggedInUser != nullptr)
            {
                std::cout << "          Hi dear " + login_call.second + " welcome to our website as a user" << std::endl;
                do
                {
                    flag = false;
                    std::cout << "    If you want to view the library, select 1" << std::endl;
                    std::cout << "    If you want to search for a book in the library, select 2" << std::endl;
                    std::cout << "    If you want to add a book to your favorites list, select 3" << std::endl;
                    std::cout << "Your input:     ";
                    std::cin >> symbol;
                    if (symbol[0] == '1' && symbol.size() == 1)
                    {
                        BMS().ViewBooks(library);
                    }
                    else if (symbol[0] == '2' && symbol.size() == 1)
                    {
                        BMS().SearchBooks(library);
                    }
                    else if (symbol[0] == '3' && symbol.size() == 1)
                    {
                        BMS().AddToFavorites(*loggedInUser, library); 
                    }
                    else
                    {
                        flag = true;
                    }
                } while (flag);
            }
        }
        else if (symbol[0] == '2' && symbol.size() == 1)
        {
            sign_up(users);
        }
        else
        {
            flag = true;
            std::cout << "\nYour input isn't correct. Please input the number 1 or 2: ";
            std::cin >> symbol;
        }
    } while (flag);

    save_users(users, filename1);
    BMS().save_books(library, filename2);

    std::cout << "End...\n";
    return 0;
}
