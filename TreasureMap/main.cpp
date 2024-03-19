#include <iostream>

#include "TreasureMap.h"
#include "TreasureTree.h"
#include "RBTree.h"

//TODO create a struct with debug messages on copy and move constructors and get through the map

void test1()
{
    dvd::RBTree<int, std::string> numbers{ { 5, "Five" }, { 2, "Two" } };

    numbers.insert(10, "Ten");
    numbers.insert(8, "Eight");
    numbers.insert(12, "Twelve");
    numbers.insert(6, "Six");
    numbers.insert(9, "Nine");

    numbers.printBFS();

    std::cin.get();
}


int main()
{
    test1();

    std::cin.get();
}
