#ifndef CRUD_HPP
#define CRUD_HPP

#include <iostream>
#include <string>
#include <fstream>

class Crud{
private:
    int id = 0;
    std::string nom = "test nom";
    std::string prenom = "test prenom";
    std::string email;
    std::string cin;

public:
    std::string urlDecode(const std::string &src); 
    int getUrlId(const char* queryString);
    int getId();
    std::string getParam(const char* queryString);
    void insertData(const std::string &filePath);
    void readData(const std::string &filePath);
    void deleteData(const std::string &filePath, const char* queryString);
    void updateData(const std::string &filePath, int id);
    void getData(const std::string &filePath, const char* queryString);
    void parseQueryString(const char* queryString);
    void renderCreate() const;
    void renderEdit() const;
    void setId(int newId);
    std::string getValue(const char* queryString, const char* data);

};

#endif    
