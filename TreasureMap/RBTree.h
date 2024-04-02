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

        std::shared_ptr<Node> findMinNodeInSubTree(std::shared_ptr<Node> x) const
        {
            while (x->left) x = x->left;
            return x;
        }

        void leftRotate(std::shared_ptr<Node>& x)
        {
            assert(x && "Pointer passed is not valid");

            std::shared_ptr<Node> y = x->right;

            assert(y && "Can't perform left rotation as right child is not valid");

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
            assert(y && "Pointer passed is not valid");

            std::shared_ptr<Node> x = y->left;

            assert(x && "Can't perform left rotation as left child is not valid");

            y->left = x->right;

            if (x->right != nullptr) x->right->parent = y;

            x->parent = y->parent;
            
            if (y->parent.lock() == nullptr) m_Root = x;
            else if (y == y->parent.lock()->right) y->parent.lock()->right = x;
            else y->parent.lock()->left = x;
            
            x->right = y;
            y->parent = x;
        }

        void insertFixup(std::shared_ptr<Node> z)
        {
            while (z->parent.lock() != nullptr && z->parent.lock()->color == Color::Red)
            {

                std::shared_ptr<Node> parent = z->parent.lock();
                std::shared_ptr<Node> grandparent = parent->parent.lock();
         
                //If parent is left child of grandparent
                if (parent == grandparent->left)
                {
                    std::shared_ptr<Node> uncle = grandparent->right;

                    //Uncle is red
                    if (uncle != nullptr && uncle->color == Color::Red)
                    {
                        parent->color = Color::Black;
                        uncle->color = Color::Black;
                        grandparent->color = Color::Red;
                        z = grandparent;
                    }
                    
                    //Uncle is black
                    else
                    {
                        if (z == parent->right)
                        {
                            z = parent;
                            leftRotate(z);

                            //reassign after rotation
                            parent = z->parent.lock();
                            grandparent = parent->parent.lock();
                        }

                        assert(parent && grandparent && "Parent and Grandparent are not valid");

                        parent->color = Color::Black;
                        grandparent->color = Color::Red;
                        rightRotate(grandparent);
                    }
                }

                //If parent is right child of grandparent
                else
                {
                    std::shared_ptr<Node> uncle = grandparent->left;

                    //Uncle is red
                    if (uncle != nullptr && uncle->color == Color::Red)
                    {
                        parent->color = Color::Black;
                        uncle->color = Color::Black;
                        grandparent->color = Color::Red;
                        z = grandparent;
                    }

                    //Uncle is black
                    else
                    {
                        if (z == parent->left)
                        {
                            z = parent;
                            rightRotate(z);

                            //reassign after rotation
                            parent = z->parent.lock();
                            grandparent = parent->parent.lock();
                        }

                        assert(parent && grandparent && "Parent and Grandparent are not valid");

                        parent->color = Color::Black;
                        grandparent->color = Color::Red;
                        leftRotate(grandparent);
                    }

                }
            }

            m_Root->color = Color::Black;
        }

        // Erase section

        void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v)
        {
            assert(u && v && "Not valid pointers provided to transplant method");

            if (u->parent.lock() == nullptr) // u is root
                m_Root = v;
            else if (u == u->parent.lock()->left)
                u->parent.lock()->left = v;
            else
                u->parent.lock()->right = v;

            v->parent = u->parent;
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
        
        void erase(const KeyType& key)
        {
            std::shared_ptr<Node> z = find(key);
            if (!z) 
            {
                debug::Log("Key not found");
                return;
            }

            std::shared_ptr<Node> x, y = z;
            Color yOriginalColor = y->color;

            if (!z->left)
            {
                x = z->right;
                transplant(z, z->right);
            }
            if (!z->right)
            {
                x = z->left;
                transplant(z, z->left)
            }
            else
            {
                y = findMinNodeInSubTree(z->right);
                yOriginalColor = y->color;
                x = y->right;

                if (y->parent.lock() == z)
                {
                    if (x) x->parent = y;
                }
                else
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    if (y->right) y->right->parent = y;
                }

                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }

            if (yOriginalColor == Color::Black)
                //fix up x

            --m_Size;
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
            std::cout << std::endl;
        }
    };
}