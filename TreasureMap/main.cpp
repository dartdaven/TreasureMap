#include <iostream>

#include "TreasureMap.h"
#include "TreasureTree.h"

//TODO create a struct with debug messages on copy and move constructors and get through the map

int main()
{
    {

        dvd::TreasureTree<std::string, std::string> colors{ {"BLACK", "#000000"} , {"WHITE", "#FFFFFF"} };

        colors.insert("GREEN", "#000000");

        //std::string blackColor = colors["BLACK"];

        // colors.emplace("RED", "#FF0000");

        colors.insert({ "WHITE", "#00FF00" });

        colors.erase("GREEN");

    }

    //colors.printOut();

    std::cin.get();
}
