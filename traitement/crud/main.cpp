
#include "./header/Crud.hpp"
#include <iostream>

int main() {
    std::cout << "Content-Type: text/html\n\n";
    Crud myCrud;
    std::string param;
    std::string route;
    const char* query_string = "";
    // const char* query_string = getenv("QUERY_STRING");
    // const char* content_string = getenv("CONTENT_LENGTH");
    std::string get;
    std::getline(std::cin, get);
    query_string = get.c_str();

    param = myCrud.getParam(query_string);
    route = myCrud.getRoute(getenv("QUERY_STRING"));


    if (route == "create")
    {
        myCrud.renderCreate();
    }
    else if (route == "readAll")
    {
        myCrud.readData("../../data/bd.txt");
    }
    

    if(param == "delete"){
        myCrud.deleteData("../../data/bd.txt",query_string);
        myCrud.readData("../../data/bd.txt");
    }
    else if (param == "edit")
    {
        myCrud.setId(myCrud.getUrlId(query_string));
        myCrud.getData("../../data/bd.txt", query_string);
        myCrud.renderEdit();
    }
    else if (param == "update")
    {   
        query_string = getenv("QUERY_STRING");
        myCrud.setId(myCrud.getUrlId(query_string));
        std::cout << myCrud.getId() ;
        myCrud.parseQueryString(query_string);
        myCrud.updateData("../../data/bd.txt", myCrud.getId());
        myCrud.readData("../../data/bd.txt");
    }

    else if (param == "create"){
        myCrud.parseQueryString(query_string);

        if (myCrud.validInput())
        {
            myCrud.insertData("../../data/bd.txt");
            myCrud.readData("../../data/bd.txt");
        }
  
    }

    return 0;
}
