#include <iostream>

#include "TreasureMap.h"
#include "TreasureTree.h"

//TODO create a struct with debug messages on copy and move constructors and get through the map

int main()
{
    dvd::TreasureTree<int, std::string> numbers{ {8, "Eight"} , {9, "Nine"} };

    numbers.insert(3, "Three");
    numbers.insert(2, "Two");
    numbers.insert(5, "Five");
    numbers.insert(4, "Four");
    numbers.insert(6, "Six");
    numbers.insert(7, "Seven");

    numbers.erase(3);
    numbers.erase(4); //I don't know why it works, but it works perfectly

    std::cin.get();
}
