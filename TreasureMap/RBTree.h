#pragma once

#include <queue>

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

        //TODO solve weak_ptr problem
        void insertFixup(std::shared_ptr<Node>& z)
        {
            while (z->parent.lock() != nullptr && z->parent.lock()->color == Color::Red)
            {
                //If parent is left child of grandparent
                if (z->parent == z->parent->parent->left)
                {
                    std::shared_ptr<Node> uncle = z->parent->parent->right;

                    //Uncle is red
                    if (uncle != nullptr && uncle->color == Color::Red)
                    {
                        z->parent->color = Color::Black;
                        uncle->color = Color::Black;
                        z->parent->parent->color = Color::Red;
                        z = z->parent->parent;
                    }
                    
                    //Uncle is black
                    else
                    {
                        if (z == z->parent->right)
                        {
                            z = z->parent;
                            leftRotate(z);
                        }

                        z->parent->color = Color::Black;
                        z->parent->parent->color = Color::Red;
                        rightRotate(z->parent->parent);
                    }
                }

                //If parent is right child of grandparent
                else
                {
                    std::shared_ptr<Node> uncle = z->parent->parent->right;

                    //Uncle is red
                    if (uncle != nullptr && uncle->color == Color::Red)
                    {
                        z->parent->color = Color::Black;
                        uncle->color = Color::Black;
                        z->parent->parent->color = Color::Red;
                        z = z->parent->parent;
                    }

                    //Uncle is black
                    else
                    {
                        if (z == z->parent->left)
                        {
                            z = z->parent;
                            rightRotate(z);
                        }

                        z->parent->color = Color::Black;
                        z->parent->parent->color = Color::Red;
                        leftRotate(z->parent->parent);
                    }

                }
            }

            m_Root->color = Color::Black;
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
                insertFixup(nodeToAttachTo->left);
            }
            else
            {
                nodeToAttachTo->right = std::make_shared<Node>(key, value, Color::Red, nodeToAttachTo);
                insertFixup(nodeToAttachTo->right);
            }
            ++m_Size;
        }
        
        //Debug
        void printBFS() const
        {
            if (!m_Root)
            {
                std::cout << "Tree is empty." << std::endl;
                return;
            }

            std::queue<std::shared_ptr<Node>> q;
            q.push(m_Root);

            while (!q.empty())
            {
                size_t levelSize = q.size();
                
                for (size_t i = 0; i < levelSize; ++i)
                {
                    std::shared_ptr<Node> current = q.front();
                    q.pop();

                    std::cout << current->key << "(" << (current->color == Color::Red ? "Red" : "Black") << ") ";

                    if (current->left) q.push(current->left);
                    if (current->right) q.push(current->right);
                }

                std::cout << std::endl;
            }
        }
    };
}