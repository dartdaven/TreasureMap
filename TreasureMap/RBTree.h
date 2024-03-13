#pragma once

#include "Debug.h"

enum class Color {Black, Red};

namespace dvd
{
    template<typename KeyType, typename ValueType>
    class RBTree
    {
        struct Node
        {
            KeyType key;
            ValueType value;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;
            Color color;

            //TODO define default color here
            Node(const KeyType& k, const ValueType& v) : key(k), value(v) {}

            //Debug
            ~Node()
            {
                debug::Log("Node Destroyed");
            }
        };

        std::unique_ptr<Node> m_Root;

        size_t m_Size;

    public:
        RBTree(std::initializer_list<std::pair<KeyType, ValueType>> initList)
        {

        }

        void incert(const KeyType& key, const ValueType& value)
        {

        }

    };
}