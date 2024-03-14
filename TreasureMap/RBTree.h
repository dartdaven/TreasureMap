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
            
            //Should be shared pointer?
            Node* parent;

            //TODO define default color here
            Node(const KeyType& k, const ValueType& v) : key(k), value(v), parent(nullptr) {}

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
            for (const auto& [k, v] : initList)
            {
                insert(k, v);
            }
        }

        //Without recursion
        void insert(const KeyType& key, const ValueType& value)
        {
            std::unique_ptr<Node> newNode = std::make_unique<Node>(key, value);

            if (!m_Root)
            {
                m_Root = std::move(newNode);
                m_Root->color = Color::Black;
                ++m_Size;

                return;
            }

            Node* nodeToAttachTo = nullptr;
            Node* iterator = m_Root.get();

            //Searching for suitable place
            while (iterator)
            {
                nodeToAttachTo = iterator;
                
                if (key < iterator->key) iterator = iterator->left.get();
                else if (key > iterator->key) iterator = iterator->right.get();
                else
                {
                    iterator->value = value; //Update the value in node
                    return;
                }
            }

            if (key < nodeToAttachTo->key) nodeToAttachTo->left = std::move(newNode);
            else nodeToAttachTo->right = std::move(newNode);
        }

    };
}