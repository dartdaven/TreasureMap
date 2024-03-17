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
            std::shared_ptr<Node> left;
            std::shared_ptr<Node> right;
            Color color;
            
            std::weak_ptr<Node> parent;

            Node(const KeyType& k, const ValueType& v, Color c = Color::Red, std::weak_ptr<Node> p = std::weak_ptr<Node>()) 
                : key(k), value(v), color(c), parent(p) {}

            //Debug
            ~Node()
            {
                debug::Log("Node Destroyed");
            }
        };

        std::shared_ptr<Node> m_Root;

        size_t m_Size;

        //Utilities

        std::shared_ptr<Node> find(const KeyType& key) const
        {
            std::shared_ptr<Node> iterator = m_Root;

            while (iterator)
            {
                if (key == iterator->key) return iterator;
                else if (key < iterator->key) iterator = iterator->left;
                else iterator = iterator->right;
            }

            return nullptr;
        }

        void leftRotate(std::shared_ptr<Node>& x)
        {
            std::shared_ptr<Node> y = x->right;

            x->right = y->left;

            if (y->left != nullptr) y->left->parent = x;

            y->parent = x->parent;

            if (x->parent.lock() == nullptr) m_Root = y;
            else if (x == x->parent.lock()->left) x->parent.lock()->left = y;
            else x->parent.lock()->right = y;

            y->left = x;
            x->parent = y;
        }

        void rightRotate(std::shared_ptr<Node>& y)
        {
            std::shared_ptr<Node> x = y->left;

            y->left = x->right;

            if (x->right != nullptr) x->right->parent = y;

            x->parent = y->parent;
            
            if (y->parent.lock() == nullptr) m_Root = x;
            else if (y == y->parent.lock()->right) y->parent.lock()->right = x;
            else y->parent.lock()->left = x;
            
            x->right = y;
            y->parent = x;
        }

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
            if (!m_Root)
            {
                m_Root = std::make_shared<Node>(key, value, Color::Black);
                ++m_Size;

                return;
            }

            std::shared_ptr<Node> nodeToAttachTo;
            std::shared_ptr<Node> iterator = m_Root;

            //Searching for suitable place
            while (iterator)
            {
                nodeToAttachTo = iterator;
                
                if (key < iterator->key) iterator = iterator->left;
                else if (key > iterator->key) iterator = iterator->right;
                else
                {
                    debug::Log("Node with this key already exists");
                    return;
                }
            }

            if (key < nodeToAttachTo->key)
            {
                nodeToAttachTo->left = std::make_shared<Node>(key, value, Color::Red, nodeToAttachTo);
            }
            else nodeToAttachTo->right = std::make_shared<Node>(key, value, Color::Red, nodeToAttachTo);
            
            ++m_Size;
        }
        
        //debug
        void leftRotate(const KeyType& key)
        {
            std::shared_ptr<Node> nodeToRotate = find(key);
            if (nodeToRotate)
                leftRotate(nodeToRotate);
        }

        void rightRotate(const KeyType& key)
        {
            std::shared_ptr<Node> nodeToRotate = find(key);
            if (nodeToRotate)
                rightRotate(nodeToRotate);
        }


    };
}