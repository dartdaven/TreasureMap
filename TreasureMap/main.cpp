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

    //case 2 right null
    numbers.insert(1, "One");
    numbers.erase(5);
    numbers.printBFS();

    //--- Problematic cases -- 

    //case both is null
    numbers.erase(23);
    numbers.printBFS();

    //case 3 none null
    numbers.erase(12);
    numbers.printBFS(); 
}


int main()
{
    test3();

    std::cin.get();
}
