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

    numbers.leftRotate(5);
}

void test2()
{
    dvd::RBTree<int, std::string> numbers{ {10, "Ten"}, { 15, "Fifteen" } };

    numbers.insert(5, "Five");
    numbers.insert(2, "Two");
    numbers.insert(7, "Seven");
    numbers.insert(6, "Six");
    numbers.insert(8, "Eight");

    numbers.leftRotate(5);

    numbers.rightRotate(7);

    std::cin.get();
}

int main()
{
    test2();

    std::cin.get();
}
