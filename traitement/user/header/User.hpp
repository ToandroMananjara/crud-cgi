#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include <fstream>

class User {
private:
    std::string adminUsername;
    std::string adminPassword;
    std::string username;
    std::string password;
 public:
    std::string urlDecode(const std::string &src); 
    bool loadCredentials(const std::string &filePath);
    void parseQueryString(const std::string &queryString);
    bool authenticate() const;
    void renderLoginPage() const;
    void renderWelcomePage(const std::string &filePath);
};

#endif // User_HPP    
