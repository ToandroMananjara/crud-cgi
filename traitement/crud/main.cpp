
#include "./header/Crud.hpp"
#include <iostream>

int main() {
    std::cout << "Content-Type: text/html\n\n";
    Crud myCrud;
    std::string param;

    const char* query_string = getenv("QUERY_STRING");
    std::string get;
    
    param = myCrud.getParam(query_string);

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
        // getline(std::cin, get);
        // query_string = get.c_str();
        query_string = getenv("QUERY_STRING");
        myCrud.setId(myCrud.getUrlId(query_string));
        std::cout << myCrud.getId() ;
        myCrud.parseQueryString(query_string);
        myCrud.updateData("../../data/bd.txt", myCrud.getId());
        myCrud.readData("../../data/bd.txt");
    }
    
    else {
        getline(std::cin, get);
        query_string = get.c_str();
        myCrud.parseQueryString(query_string);
        
    }

    return 0;
}
