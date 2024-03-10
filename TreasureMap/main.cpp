#include <iostream>

#include "TreasureMap.h"
#include "TreasureTree.h"

//TODO create a struct with debug messages on copy and move constructors and get through the map

int main()
{


    dvd::TreasureTree<std::string, std::string> colors{ {"BLACK", "#000000"} , {"WHITE", "#FFFFFF"} };

    //insert works
    colors.insert("GREEN", "#00FF00");

    //Try to take value that is not stored 
    std::string blackColor = colors["RED"];

    //Try to take value
    blackColor = colors["BLACK"];

    // colors.emplace("RED", "#FF0000");

    //Overwrite value
    colors.insert({ "WHITE", "#00FF00" });

    colors.printOut();
    
    colors.erase("GREEN");

    colors.printOut();


    std::cin.get();
}
