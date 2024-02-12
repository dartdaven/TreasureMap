#include <iostream>

#include "TreasureMap.h"
#include "TreasureTree.h"

int main()
{
    //Writing like it's already exist to display what is needed to be done
    dvd::TreasureMap<std::string, std::string> colors{ {"BLACK", "#000000"} , {"WHITE", "#FFFFFF"} };

    std::string blackColor = colors["BLACK"];

    colors["BLUE"] = "0000FF";
    
    colors.insert({ "RED", "#FF0000" });
    colors.emplace("GREEN", "#00FF00");

    colors.erase("RED");

    if (colors.contains("GREEN")) std::cout << "contains\n";

    std::cout << "size of the colors: " << colors.size() << std::endl;

    for (const auto& kv : colors)
    {
        std::cout << kv.first << " is " << kv.second << std::endl;
    }

    std::cin.get();
}
