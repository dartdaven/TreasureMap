#include <iostream>

#include "TreasureMap.h"
#include "TreasureTree.h"
#include "RBTree.h"

//TODO create a struct with debug messages on copy and move constructors and get through the map

void test3()
{
    dvd::RBTree<int, std::string> numbers{ {8, "Eight"}, {5, "Five"} };

    numbers.insert(15, "Fifteen");
    numbers.insert(12, "Twelve");
    numbers.insert(19, "Nineteen");
    numbers.insert(9, "Nine");
    numbers.insert(13, "Thirteen");
    numbers.insert(23, "Twenty Three");
    numbers.insert(10, "Ten");

    numbers.printBFS();

    //case 1 left null
    numbers.erase(19);
    numbers.printBFS();

    //case 1.1 both is null
    numbers.erase(23);
    numbers.printBFS();

    //case 2 right null
    numbers.insert(1, "One");
    numbers.erase(5);
    numbers.printBFS();

    //case 3 none null
    numbers.erase(12);
    numbers.printBFS();

    //case 4 none null root is the parent
    numbers.erase(8);
    numbers.printBFS();
}

int main()
{
    test3();

    std::cin.get();
}
