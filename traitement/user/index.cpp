#include "./header/User.hpp"
#include "../crud/header/Crud.hpp"
#include <iostream>
int main() {
    std::cout << "Content-Type: text/html\n\n";
    User user;
    Crud crud;

    if (!user.loadCredentials("../../data/data.txt")) {
        return 1;
    }

    const char* query_string;
    std::string get;
    getline(std::cin, get);
    query_string = get.c_str();
    
    if (query_string) {
        user.parseQueryString(query_string);
        if (user.authenticate()) {
           crud.readData("../../data/bd.txt");
        }
    } else {
        user.renderLoginPage();
    }

    return 0;
}
