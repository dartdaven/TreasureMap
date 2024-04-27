#include <iostream>

#include <map>

#include "TreasureMap.h"
#include "TreasureTree.h"
#include "RBTree.h"

struct Entity
{
    int x{}, y{}, z{};

    Entity() {};
    Entity(int x, int y, int z) : x(x), y(y), z(z) {};
    Entity(int scalar) : x(scalar), y(scalar), z(scalar) {};

    Entity(const Entity& other) : x(other.x), y(other.y), z(other.z)
    {
        debug::Log("Copy constructor");
    }

    Entity& operator=(const Entity& other)
    {
        debug::Log("Copy");
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Entity(Entity&& other) noexcept : x(other.x), y(other.y), z(other.z)
    {
        debug::Log("Move constructor");
    }

    Entity& operator=(Entity&& other) noexcept
    {
        debug::Log("Move");
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    ~Entity()
    {
        debug::Log("Entity Destroyed");
    }
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

void treasureTreeEraseTest()
{
    dvd::TreasureTree<int, std::string> numbers{ {8, "Eight"}, {5, "Five"} };

    numbers.insert(15, "Fifteen");
    numbers.erase(8); //case 4-1
    numbers.erase(8);
    numbers.insert(12, "Twelve");
    numbers.insert(19, "Nineteen");
    numbers.insert(9, "Nine");
    numbers.insert(4, "Four");
    numbers.insert(10, "Ten");
    numbers.erase(5); //case 4-2
    numbers.insert(13, "Thirteen");
    numbers.insert(23, "Twenty Three");

    std::cout << numbers.size() << std::endl;

}

void UBTest()
{
    dvd::TreasureTree<int, std::string> numbers{ {8, "Eight"}, {5, "Five"} };

    numbers.insert(11, "Eleven");
    numbers.insert(14, "Fourteen");
    numbers.insert(13, "Thirteen");
    numbers.insert(15, "Fifteen");

    numbers.erase(11);
    
}

void treasureMapTreeAccessingTest()
{
    dvd::TreasureTree<int, std::string> numbers{ {8, "Eight"}, {5, "Five"} };

    //inserting existing
    numbers.insert(8, "Eight");
    numbers.emplace(8, "Eight");

    //accessing non-existing
    std::cout << numbers[10] << std::endl;
    numbers[11] = "Eleven";

    dvd::TreasureMap<int, std::string> mnumbers{ {8, "Eight"}, {5, "Five"} };

    //inserting existing
    mnumbers.insert(8, "Eight");
    mnumbers.emplace(8, "Eight");

    //accessing non-existing
    std::cout << mnumbers[10] << std::endl;
    mnumbers[11] = "Eleven";
}

void moveCopyTreasureMapInsertTest()
{
    dvd::TreasureMap<int, Entity> numbers{};
    std::unordered_map<int, Entity> stdNumbers{};

    //rvalue pair
    numbers.insert({ 8, Entity(8) });
    stdNumbers.insert({ 8, Entity(8) });

    numbers.insert(std::make_pair(4, Entity(4)));
    stdNumbers.insert(std::make_pair(4, Entity(4)));

    std::pair<int, Entity> pair{ 9, Entity(1, 2, 3) };
    
    //lvalue pair
    numbers.insert(pair);
    stdNumbers.insert(pair);

    //rvalue key, value
    numbers.insert(5, Entity(5));
    //stdNumbers.insert(5, Entity(5)); //Compiler error, accepts pairs only
    stdNumbers.emplace(5, Entity(5));

    int a{ 6 };
    Entity e{ 6 };

    //lvalue key,value
    numbers.insert(a, e);
}

void moveCopyTreasureTreeInsertTest()
{
    dvd::TreasureTree<int, Entity> numbers{};
    std::map<int, Entity> stdNumbers{};

    //rvalue pair
    numbers.insert({ 8, Entity(8) });
    stdNumbers.insert({ 8, Entity(8) });

    numbers.insert(std::make_pair(4, Entity(4)));
    stdNumbers.insert(std::make_pair(4, Entity(4)));

    std::pair<int, Entity> pair{ 9, Entity(1, 2, 3) };

    //lvalue pair
    numbers.insert(pair);
    stdNumbers.insert(pair);

    //rvalue key, value
    numbers.insert(5, Entity(5));
    //stdNumbers.insert(5, Entity(5)); //Compiler error, accepts pairs only
    stdNumbers.emplace(5, Entity(5));

    int a{ 6 };
    Entity e{ 6 };

    //lvalue key,value
    numbers.insert(a, e);
}

void nilCaseTestForRBTree()
{
    dvd::RBTree<int, Entity> numbers{};

    numbers[1] = Entity(1);
    numbers.emplace(0, 0);

    dvd::RBTree<std::string, Entity> stringNumbers{};

    stringNumbers.insert("One", 1);
    stringNumbers.emplace("", 0);
}

int main()
{
    nilCaseTestForRBTree();

    std::cin.get();
}
