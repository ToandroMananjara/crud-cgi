#ifndef CRUD_CPP
#define CRUD_CPP

#include "../header/Crud.hpp"
#include <iostream>
#include <cstring>
#include <regex> 
#include <vector>
#include <sstream>
#include <string>

// Setter for id
void Crud::setId(int newId){
    id = newId;
}

// Getter for id
int Crud::getId(){
    return id;
}

// Get the value on the url 
std::string Crud::getValue(const char* query_string, const char* data) {
    const char* temp = std::strstr(query_string, data);
    if (temp) {
        temp += std::strlen(data);
        std::string nom_str(temp);
        size_t pos = nom_str.find("&");
        if (pos != std::string::npos) {
            nom_str = nom_str.substr(0, pos);
        }
        return nom_str;
    }
    else
        return "";
}

// Extract and stock the value in every attribute
void Crud::parseQueryString(const char* queryString) {
    nom = getValue(queryString, "nom=");
    nom = urlDecode(nom);
    prenom = getValue(queryString, "prenom=");
    prenom = urlDecode(prenom);
    email = getValue(queryString, "email=");
    email = urlDecode(email);
    dateNaissance = getValue(queryString, "dateNaissance=");
    dateNaissance = urlDecode(dateNaissance);  
}

// Get the action using from removing or editing
std::string Crud::getParam(const char* queryString){
    std::string param;
    param = getValue(queryString,"action=");
    return param;
}

std::string Crud::getRoute(const char* queryString){
    std::string route;
    route = getValue(queryString,"route=");
    return route;
}
// Get id in the url from removing or editing the data
int Crud::getUrlId(const char* queryString){
    int id = 0;
    std::string myId;
    myId = getValue(queryString, "id=");
    myId = urlDecode(myId);
    id = std::stoi(myId);
    return id;
}

// Encoded the data on utf-8 before stocked in the database
std::string Crud::urlDecode(const std::string &src) {
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



std::string Crud::trim(const std::string &s) {
    size_t start = s.find_first_not_of(' ');
    size_t end = s.find_last_not_of(' ');
    
    // If the string is only spaces or empty, return an empty string
    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }
    
    return s.substr(start, end - start + 1);
}
bool Crud::isNotBlank(const std::string &s) {
    return !trim(s).empty();  // Return true if the trimmed string is not empty
}
bool Crud::validInput(){
    std::regex nomPattern("^[A-Za-zÀ-ÿ '-]+$");
    std::regex prenomPattern("^[A-Za-zÀ-ÿ '-]+$");
    std::regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    std::regex dobPattern("^\\d{4}-\\d{2}-\\d{2}$");
    // std::regex agePattern("^([1-9]|[1-9][0-9]|1[0-9]{2})$"); 
    // std::regex adressePattern("^[A-Za-z0-9À-ÿ ,'-]+$");

    if (!isNotBlank(nom) || !isNotBlank(prenom) || !isNotBlank(email) || !isNotBlank(dateNaissance)) {
        return false;  // Invalid if any input is blank
    }
    
    bool isNomValid = std::regex_match(nom, nomPattern);
    bool isPrenomValid = std::regex_match(prenom, prenomPattern);
    bool isEmailValid = std::regex_match(email, emailPattern);
    bool isDobValid = std::regex_match(dateNaissance, dobPattern);

    return isNomValid && isPrenomValid && isEmailValid && isDobValid ;
}
// Create data in database txt
void Crud::insertData(const std::string &filePath) {
    std::ofstream file(filePath, std::ios::app | std::ios::binary); // Ajout du mode binaire pour UTF-8
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }
    else {
        file << nom << ";" << prenom << ";" << email << ";" << dateNaissance ;
        file << "\n";
    }
    file.close();    
}
// Read data from the database txt
void Crud::readData(const std::string &filePath){
    int id = 0;
    std::string line;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }
    else{
        std::cout << R"(
            <!DOCTYPE html>
            <html lang="en">
            <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
            <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css">
            <link rel="stylesheet" href="../../css/style-accueil.css">
            <title>Welcome</title>
            </head>
            <body>
            <div>
                <header>
                    <div class="header">
                        <div class="logo">Logo</div>

                        <nav class="navbar-container">
                            <ul>
                                <li><a href="/monsite/traitement/crud/crud.cgi?route=create">Add new</a></li>
                                <li><a href="/monsite/traitement/crud/crud.cgi?route=readAll">Lists</a></li>
                            </ul>
                        </nav>
                    </div>
                </header>
            </div>
            <div class=" d-flex justify-content-center">
                <table class="table ">
                <thead class="w-100 table-dark">
                    <tr>
                        <th scope="col" class="table-title text-center" data-name="id"># <i class="fa-solid fa-caret-down"></i></th>
                        <th scope="col" class="table-title text-center" data-name="nom">Nom<i class="fa-solid fa-caret-down"></i></th>
                        <th scope="col" class="table-title text-center" data-name="prenom">Prenom<i class="fa-solid fa-caret-down"></i></th>
                        <th scope="col" class="table-title text-center" data-name="email">Email<i class="fa-solid fa-caret-down"></i></th>
                        <th scope="col" class="table-title text-center" data-name="dateNaissance">Date de Naissance<i class="fa-solid fa-caret-down"></i></th>
                        <th scope="col" class="text-center" >Action</th>
                    </tr>
                </thead>
                <tbody class="tbody-table">
                )";
                while (std::getline(file, line)) {
                    std::istringstream ss(line);
                    std::string nom, prenom, email, dateNaissance;
                    std::getline(ss, nom, ';');
                    std::getline(ss, prenom, ';');
                    std::getline(ss, email, ';');
                    std::getline(ss, dateNaissance);

                    if (!line.empty()) {
                        std::cout << "<tr class=\"row-table\">"
                                << "<th scope=\"row\" class=\"text-center\">" << id << "</th>"
                                << "<td class=\"text-center\">" << nom << "</td>"
                                << "<td class=\"text-center\">" << prenom << "</td>"
                                << "<td class=\"text-center\">" << email << "</td>"
                                << "<td class=\"text-center\">" << dateNaissance << "</td>"
                                << "<td class=\"text-center d-flex gap-3 justify-content-center\">"
                                << "<a href=\"\" class=\"btn btn-primary\"><i class=\"fa-regular fa-eye\"></i></a>"
                                //<< "<a href=\"?id=" << id << "\" class=\"btn btn-success\"><i class=\"fa-regular fa-pen-to-square\"></i></a>"
                                << "<form action=\"../crud/crud.cgi\" method=\"post\">"
                                << "<input type=\"hidden\" name=\"id\" value=\"" << id << "\"/>"
                                << "<input type=\"hidden\" name=\"action\" value=\"edit\"/>"
                                << "<button type=\"submit\" class=\"btn btn-success\"><i class=\"fa-regular fa-pen-to-square\"></i></button>"
                                << "</form>"                               
                                << "<form action=\"../crud/crud.cgi\" method=\"post\">"
                                << "<input type=\"hidden\" name=\"id\" value=\"" << id << "\"/>"
                                << "<input type=\"hidden\" name=\"action\" value=\"delete\"/>"
                                << "<button type=\"submit\" class=\"btn btn-danger\"><i class=\"fa-solid fa-trash\"></i></button>"
                                << "</form>"
                                << "</td>"
                                << "</tr>";
                    }
                    id++;
                }

            file.close();
            std::cout << R"(
            </table>
            </div>
            </body>
            </html>
            )";  
        }
}

// Delete data in database txt
void Crud::deleteData(const std::string &filePath, const char* queryString) {
    int count = 0;
    std::ifstream file(filePath); // Ouvre le fichier en lecture
    if (!file) {
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
    }
    std::vector<std::string> lines; // Vecteur pour stocker les lignes du fichier
    std::string line;

    // Lire le fichier ligne par ligne
    while (std::getline(file, line)) {
        if (getUrlId(queryString) != count )
        {
            lines.push_back(line); 
        }
        count++;
    }

    file.close(); // Ferme le fichier

    std::ofstream outFile(filePath, std::ios::trunc); // Open the file in write mode, truncating it
    if (!outFile) {
        std::cerr << "Error opening the file for writing" << std::endl;
        return;
    }

    for (const auto& l : lines) {
        outFile << l << std::endl; // Write each remaining line to the file
    }
    outFile.close(); // Close the file
}

// get data to edit in the database txt
void Crud::getData(const std::string &filePath, const char* queryString) {
    int count = 0;
    std::ifstream file(filePath); // Ouvre le fichier en lecture
    if (!file) {
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
    }
    std::vector<std::string> lines; // Vecteur pour stocker les lignes du fichier
    std::string line;

    // Lire le fichier ligne par ligne
    while (std::getline(file, line)) {
        if (getUrlId(queryString) == count )
        {   
            insertData(filePath);
            lines.push_back(line); 
            
        }
        count++;
    }
    for (const auto& l : lines) {
        //std::cout << l << std::endl;
        std::string part;
        std::istringstream stream(l);
        if (std::getline(stream, part, ';')) {
            nom = part;
        }
        if (std::getline(stream, part, ';')) {
            prenom = part;
        }
        if (std::getline(stream, part, ';')) {
            email = part;
        }
        if (std::getline(stream, part, ';')) {
            dateNaissance = part;
        }
    }
    file.close(); // Ferme le fichier
}

// Edit data in the database
void Crud::updateData(const std::string &filePath, int id){
    int count = 0;
    std::ifstream file(filePath); // Ouvre le fichier en lecture
    if (!file) {
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
    }
    std::vector<std::string> lines; // Vecteur pour stocker les lignes du fichier
    std::string line; 

    // Lire le fichier ligne par ligne
    while (std::getline(file, line)) {
        if (count != id )
        {
            lines.push_back(line); 
        }
        else {
            line = nom + ";" + prenom + ";" + email + ";" + dateNaissance;
            lines.push_back(line);
        }
        count++;
    }

    file.close(); // Ferme le fichier
    std::ofstream outFile(filePath, std::ios::trunc); // Open the file in write mode, truncating it
    if (!outFile) {
        std::cerr << "Error opening the file for writing" << std::endl;
        return;
    }

    for (const auto& l : lines) {
        outFile << l << std::endl; // Write each remaining line to the file
    }
    outFile.close(); // Close the file
}

// Render for create data 
void Crud::renderCreate() const {
    std::cout << R"(
        <!DOCTYPE html>
        <html lang="en">

        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet"
                integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
            <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css">
            <link rel="stylesheet" href="../../../css/style-accueil.css">
            <title>Document</title>
        </head>

        <body>
            <main class="mt-4">
                <div class="container p-5" style="box-shadow: 0em .5em 1em  #b8b4b4;width:fit-content;border-radius:1em;">
                    <div class="container">
                        <div class="text-center mb-5">
                            <h3>Add new user</h3>
                            <p class="text-muted">
                                Complete the form below to add new user
                            </p>
                        </div>
                    </div>

                    <div class="container d-flex justify-content-center">
                        <form action="../crud/crud.cgi" method="post" style="width:50vw; min-width:300px;" accept-charset="UTF-8">
                            
                            <div class="row mb-2">
                                <div class="col">
                                    <label for="nom" class="form-label">Nom:</label>
                                    <input type="text" class="form-control" name="nom" placeholder="Your first name" required>
                                </div>

                                <div class="col">
                                    <label for="prenom" class="form-label">Prenom:</label>
                                    <input type="text" class="form-control" name="prenom" placeholder="Your last name" required>
                                </div>
                            </div>

                            <div class="row mb-2">
                                <div class="col">
                                    <label for="email" class="form-label">Email:</label>
                                    <input type="email" class="form-control" name="email" placeholder="email@example.com" required>
                                </div>
                                <div class="col" style="width:50%">
                                    <label for="dateNaissance" class="form-label">Date de naissance:</label>
                                    <input type="date" class="form-control" name="dateNaissance" required>
                                </div>
                            </div>

                            <input type="hidden" name="action" value="create">
                            <div class="">
                                <button type="submit" class="btn btn-success" name="submit"
                                    style="padding-right:2em;padding-left:2em;">Ajouter</button>
                            </div>
                        </form>
                    </div>
                </div>
            </main>
        </body>

        </html>
    )";
}

// Render for edit data
void Crud::renderEdit() const {
    std::cout << R"(
        <!DOCTYPE html>
        <html lang="en">

        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet"
                integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
            <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.5.1/css/all.min.css">
            <link rel="stylesheet" href="../../../css/style-accueil.css">
            <title>Document</title>
        </head>

        <body>
            <main class="mt-4">
                <div class="container p-5" style="box-shadow: 0em .5em 1em  #b8b4b4;width:fit-content;border-radius:1em;">
                    <div class="container">
                        <div class="text-center mb-5">
                            <h3>Edit user </h3>
                            <p class="text-muted">
                                Complete the form below to edit user
                            </p>
                        </div>
                    </div>

                    <div class="container d-flex justify-content-center">
                        <form action="../crud/crud.cgi" method="get" style="width:50vw; min-width:300px;" accept-charset="UTF-8">
                            
                            <div class="row mb-2">
                                <div class="col">
                                    <input type="hidden" name="id" value= ")" + std::to_string(id) + R"( "/>
                                    <label for="nom" class="form-label">Nom:</label>
                                    <input type="text" class="form-control" name="nom" placeholder="Your first name" value= ")" + nom + R"( " required>
                                </div>

                                <div class="col">
                                    <label for="prenom" class="form-label">Prenom:</label>
                                    <input type="text" class="form-control" name="prenom" placeholder="Your last name" value= ")" + prenom + R"( " required>
                                </div>
                            </div>

                            <div class="row mb-2">
                                <div class="col">
                                    <label for="email" class="form-label">Email:</label>
                                    <input type="email" class="form-control" name="email" placeholder="email@example.com"  value= ")" + email + R"( " required>
                                </div>
                                <div class="col" style="width:50%">
                                    <label for="dateNaissance" class="form-label">Date de naissance:</label>
                                    <input type="date" class="form-control" name="dateNaissance"  value= ")" + dateNaissance + R"( " required>
                                </div>
                            </div>

                            <div class="">
                                <input type="hidden" name="action" value="update"/>
                                <button type="submit" class="btn btn-success" name="submit"
                                    style="padding-right:2em;padding-left:2em;">Modifier</button>

                            </div>
                        </form>
                    </div>
                </div>
            </main>
        </body>
        </html>
    )";
}


#endif