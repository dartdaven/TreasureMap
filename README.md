# TreasureMap

The objectives of this exercise are:
1. familiarize with data structures such as hash tables, trees, and their variations
2. learn to make data structures from scratch
3. learn templates
4. get hands-on move semantics and rvalues

#### Hashmap

Create an associative container that contains key-value pairs with unique keys. Search, insertion, and removal of elements should have average constant-time complexity. Having multiple elements per one key is not allowed, but don't forget about resolving collisions.

You can use [std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map) as an example of such a container.

Supported operations:
* access element by key
* insert element
* emplace element
* remove element
* check element number
* check if an element exists in the container
* set custom hash function


#### Tree
Create a sorted associative container that contains key-value pairs with unique keys. Search, removal, and insertion operations should have logarithmic complexity on average. Having multiple elements per one key is not allowed.
You can use [std::map](https://en.cppreference.com/w/cpp/container/map) as an example of such a container.

Supported operations:
* access element by key
* insert element
* emplace element
* remove element
* check element number
* check if an element exists in the container


#### Useful C++ tools
* templates
* rvalue references
* std::function
* lambdas
* smart pointers
* enum class

### Additional challenge
* create self-balanced recursion-less tree
* Make iterators for your custom containers

#### Resources used
[Learn Hash Tables in 13 minutes](https://youtu.be/FsfRsGFHuv4)  
[VECTOR/DYNAMIC ARRAY - Making DATA STRUCTURES in C++](https://youtu.be/ryRf4Jh_YC0)  
[Learn Tree traversal in 3 minutes](https://youtu.be/b_NjndniOqY)  
[Red-Black Trees - Michael Sambol playlist](https://www.youtube.com/playlist?list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin)  
[Red-Black Trees - Codesdope](https://www.codesdope.com/course/data-structures-red-black-trees/)
