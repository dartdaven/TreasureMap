#include <iostream>

#include "TreasureMap.h"
#include "TreasureTree.h"

int main()
{
    //Copy hash function problem is solved

    dvd::TreasureMap<std::string, std::string> colors(2);

    dvd::TreasureMap<std::string, std::string> printables = colors;

    printables.resizeTable(10);

    printables.insert("1", "one");
    printables.insert("2", "two");
    printables.insert("3", "three");
    printables.insert("4", "four");
    printables.insert("5", "five");
    printables.insert("6", "six");

    printables.printOut();
    
    
    //Custom hash function working
    
    std::function<size_t(const std::string&)> badHashFunction = [](const std::string& string) { return 3; };
    dvd::TreasureMap<std::string, std::string> strings(badHashFunction);

    strings.insert("1", "one");
    strings.insert("2", "two");
    strings.insert("3", "three");
    strings.insert("4", "four");
    strings.insert("5", "five");
    strings.insert("6", "six");
    
    strings.printOut();

    std::cin.get();
}
