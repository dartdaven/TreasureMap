#include <iostream>

#include "TreasureMap.h"
#include "TreasureTree.h"
#include "RBTree.h"

//TODO create a struct with debug messages on copy and move constructors and get through the map

struct Entity
{
    int x{}, y{}, z{};

    Entity() {};
    Entity(int x, int y, int z) : x(x), y(y), z(z) {};
    Entity(int scalar) : x(scalar), y(scalar), z(scalar) {};
};

void RBtest()
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

    if (numbers.contains(13)) debug::Log("Contains work");
    if (numbers.contains(0)) debug::Log("Contains does not work"); //NIL case
    if (!numbers.contains(23)) debug::Log("Contains work");

    std::cout << numbers[13] << std::endl;
    std::cout << numbers[23] << std::endl;

    numbers.printBFS();

}

void emplaceRBTest()
{
    dvd::RBTree<int, Entity> numbers{};

    numbers.emplace(8, 1, 2, 3);
    numbers.insert(5, 5);
    numbers.emplace(15, 15);
    numbers.emplace(12);
    numbers.emplace(19, 3, 4, 6);
    numbers.emplace(9, 5, 3, 2);
    numbers.emplace(13, 13);
    numbers.emplace(23, 1, 2, 3);
    numbers.emplace(10);

    numbers.printBFS();

    numbers.erase(12);
    numbers.printBFS();
}

int main()
{
    emplaceRBTest();

    std::cin.get();
}
