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

void test2()
{
    dvd::RBTree<int, std::string> numbers{ { 20, "Twenty" }, { 11, "Eleven" } };

    numbers.insert(40, "Fourty");
    numbers.insert(10, "Ten");
    numbers.insert(15, "Fifteen");
    numbers.insert(30, "Thirty");
    numbers.insert(5, "Five");
    numbers.insert(12, "Twelve");
    numbers.insert(18, "Eighteen");
    numbers.insert(28, "Twenty Eight");
    numbers.insert(35, "Thirty Five");
    numbers.insert(2, "Two");
    numbers.insert(6, "Six");
    numbers.insert(13, "Thirteen");
    numbers.insert(31, "Thirty One");
    numbers.insert(38, "Thirty Eight");

    numbers.printBFS();

    std::cin.get();
}


int main()
{
    test2();

    std::cin.get();
}
