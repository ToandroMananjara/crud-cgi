#ifndef USER_CPP
#define USER_CPP

#include "../header/User.hpp"
#include <iostream>
#include <sstream>
#include <string>

std::string User::urlDecode(const std::string &src) {
    std::string result;
    for (size_t i = 0; i < src.length(); i++) {
        if (src[i] == '+') {
            result += ' ';
        } else if (src[i] == '%' && i + 2 < src.length()) {
            int hex = stoi(src.substr(i + 1, 2), nullptr, 16); // Convertir le nombre hexadécimal en décimal
            result += static_cast<char>(hex); // Convertir le nombre décimal en caractère
            i += 2;
        } else {
            result += src[i];
        }
    }
    return result;
}

bool User::loadCredentials(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return false;
    }

    file >> adminUsername >> adminPassword;
    if (file.fail()) {
        std::cerr << "Erreur lors de la lecture du fichier." << std::endl;
        return false;
    }

    file.close();
    return true;
}

void User::parseQueryString(const std::string &queryString) {
    size_t userPos = queryString.find("username=");
    size_t passPos = queryString.find("&password=");
    if (userPos != std::string::npos && passPos != std::string::npos) {
        username = queryString.substr(userPos + 9, passPos - (userPos + 9));
        password = queryString.substr(passPos + 10);
    }
}

// Authenticate the user 
bool User::authenticate() const {
    return adminUsername == username && adminPassword == password;
}

// Render of the login page
void User::renderLoginPage() const {  
    std::cout << R"(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<link rel="stylesheet" href="../../css/style.css">
<title>Login page</title>
</head>
<body>
<div id="root">
    <div class="container">
        <div class="form-container">
            <div class="form">
                <h1>Login</h1>
                <form action="index.cgi" method="post">
                    <label for="username">Username:</label><br>
                    <input type="text" name="username" id="username" class="input" placeholder="Entrer username" required><br>
                    <label for="password">Password:</label><br>
                    <div class="password-container">
                        <input type="password" name="password" id="password" class="input" placeholder="Entrer password"  required><br>
                        <div class="icon">
                            <i class="fa fa-eye" aria-hidden="true"></i>
                        </div>
                    </div>
                    <input type="submit" id="login" value="log in">
                </form>
            </div>
        </div>
    </div>
</div>
</body>
</html>
    )";
}

#endif