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

            //lvalue constructor
            Node(const KeyType& k, const ValueType& v, Color c = Color::Red, std::weak_ptr<Node> p = std::weak_ptr<Node>(), std::shared_ptr<Node> l = nullptr, std::shared_ptr<Node> r = nullptr)
                : key(k), value(v), color(c), parent(p), left(l), right(r) {}

            //rvalue constructor
            Node(KeyType&& k, ValueType&& v, Color c = Color::Red, std::weak_ptr<Node> p = std::weak_ptr<Node>(), std::shared_ptr<Node> l = nullptr, std::shared_ptr<Node> r = nullptr)
                : key(std::move(k)), value(std::move(v)), color(c), parent(p), left(l), right(r) {}

            //emplace constructor
            template<typename... Args>
            Node(const KeyType& k, Color c, std::weak_ptr<Node> p, std::shared_ptr<Node> l, std::shared_ptr<Node> r, Args&&... args)
                : key(k), color(c), parent(p), left(l), right(r), value(std::forward<Args>(args)...) {}

            //NIL constructor
            Node() : key(), color(Color::Black) {};

            //Debug
            ~Node()
            {
                debug::Log("Node Destroyed");
            }
        };

        //Sentinel node
        std::shared_ptr<Node> m_NIL = std::make_shared<Node>();
        
        std::shared_ptr<Node> m_Root = m_NIL;

        size_t m_Size;

        //Utilities

        std::shared_ptr<Node> find(const KeyType& key) const
        {
            std::shared_ptr<Node> iterator = m_Root;

            while (iterator != m_NIL)
            {
                if (key == iterator->key) return iterator;
                else if (key < iterator->key) iterator = iterator->left;
                else iterator = iterator->right;
            }

            return m_NIL;
        }

        std::shared_ptr<Node> findMinNodeInSubTree(std::shared_ptr<Node> x) const
        {
            while (x->left != m_NIL) x = x->left;
            return x;
        }

        void leftRotate(std::shared_ptr<Node> x)
        {
            std::shared_ptr<Node> y = x->right;

            x->right = y->left;

            if (y->left != m_NIL) y->left->parent = x;

            y->parent = x->parent;

            if (x->parent.lock() == m_NIL) m_Root = y;
            else if (x == x->parent.lock()->left) x->parent.lock()->left = y;
            else x->parent.lock()->right = y;

            y->left = x;
            x->parent = y;
        }

        void rightRotate(std::shared_ptr<Node> y)
        {
            std::shared_ptr<Node> x = y->left;

            y->left = x->right;

            if (x->right != m_NIL) x->right->parent = y;

            x->parent = y->parent;
            
            if (y->parent.lock() == m_NIL) m_Root = x;
            else if (y == y->parent.lock()->right) y->parent.lock()->right = x;
            else y->parent.lock()->left = x;
            
            x->right = y;
            y->parent = x;
        }

        void insertFixup(std::shared_ptr<Node> z)
        {
            while (z->parent.lock()->color == Color::Red)
            {

                std::shared_ptr<Node> parent = z->parent.lock();
                std::shared_ptr<Node> grandparent = parent->parent.lock();
         
                //If parent is left child of grandparent
                if (parent == grandparent->left)
                {
                    std::shared_ptr<Node> uncle = grandparent->right;

                    //Uncle is red
                    if (uncle->color == Color::Red)
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
                    if (uncle->color == Color::Red)
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

                        parent->color = Color::Black;
                        grandparent->color = Color::Red;
                        leftRotate(grandparent);
                    }
                }
            }

            m_Root->color = Color::Black;
        }

        void transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v)
        {
            if (u->parent.lock() == m_NIL) // u is root
                m_Root = v;
            else if (u == u->parent.lock()->left)
                u->parent.lock()->left = v;
            else
                u->parent.lock()->right = v;

            v->parent = u->parent;
        }

        void eraseFixup(std::shared_ptr<Node> x)
        {
            while (x != m_Root && x->color == Color::Black)
            {
                if (x == x->parent.lock()->left)
                {
                    std::shared_ptr<Node> w = x->parent.lock()->right;

                    if (w->color == Color::Red)
                    {
                        w->color = Color::Black;
                        x->parent.lock()->color = Color::Red;
                        leftRotate(x->parent.lock());
                        w = x->parent.lock()->right;
                    }

                    if (w->left->color == Color::Black && w->right->color == Color::Black)
                    {
                        w->color = Color::Red;
                        x = x->parent.lock();
                    }
                    else
                    {
                        if (w->right->color == Color::Black)
                        {
                            w->left->color = Color::Black;
                            w->color = Color::Red;
                            rightRotate(w);
                            w = x->parent.lock()->right;
                        }

                        w->color = x->parent.lock()->color;
                        x->parent.lock()->color = Color::Black;
                        w->right->color = Color::Black;
                        leftRotate(x->parent.lock());
                        x = m_Root;
                    }
                }
                else
                {
                    std::shared_ptr<Node> w = x->parent.lock()->left;

                    if (w->color == Color::Red)
                    {
                        w->color = Color::Black;
                        x->parent.lock()->color = Color::Red;
                        rightRotate(x->parent.lock());
                        w = x->parent.lock()->left;
                    }

                    if (w->right->color == Color::Black && w->left->color == Color::Black)
                    {
                        w->color = Color::Red;
                        x = x->parent.lock();
                    }
                    else
                    {
                        if (w->left->color == Color::Black)
                        {
                            w->right->color = Color::Black;
                            w->color = Color::Red;
                            leftRotate(w);
                            w = x->parent.lock()->left;
                        }

                        w->color = x->parent.lock()->color;
                        x->parent.lock()->color = Color::Black;
                        w->left->color = Color::Black;
                        rightRotate(x->parent.lock());
                        x = m_Root;
                    }
                }
            }

            x->color = Color::Black;
        }

    public:
        RBTree(std::initializer_list<std::pair<KeyType, ValueType>> initList)
        {
            for (const auto& [k, v] : initList)
            {
                insert(k, v);
            }
        }

        void insert(const KeyType& key, const ValueType& value)
        {
            if (m_Root == m_NIL)
            {
                m_Root = std::make_shared<Node>(key, value, Color::Black, m_NIL, m_NIL, m_NIL);
                ++m_Size;

                return;
            }

            std::shared_ptr<Node> nodeToAttachTo = m_NIL;
            std::shared_ptr<Node> iterator = m_Root;

            while (iterator != m_NIL)
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
                nodeToAttachTo->left = std::make_shared<Node>(key, value, Color::Red, nodeToAttachTo, m_NIL, m_NIL);
                insertFixup(nodeToAttachTo->left);
            }
            else
            {
                nodeToAttachTo->right = std::make_shared<Node>(key, value, Color::Red, nodeToAttachTo, m_NIL, m_NIL);
                insertFixup(nodeToAttachTo->right);
            }

            ++m_Size;
        }

        void insert(KeyType&& key, ValueType&& value)
        {
            if (m_Root == m_NIL)
            {
                m_Root = std::make_shared<Node>(std::move(key), std::move(value), Color::Black, m_NIL, m_NIL, m_NIL);
                ++m_Size;

                return;
            }

            std::shared_ptr<Node> nodeToAttachTo = m_NIL;
            std::shared_ptr<Node> iterator = m_Root;

            while (iterator != m_NIL)
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
                nodeToAttachTo->left = std::make_shared<Node>(key, value, Color::Red, nodeToAttachTo, m_NIL, m_NIL);
                insertFixup(nodeToAttachTo->left);
            }
            else
            {
                nodeToAttachTo->right = std::make_shared<Node>(key, value, Color::Red, nodeToAttachTo, m_NIL, m_NIL);
                insertFixup(nodeToAttachTo->right);
            }

            ++m_Size;
        }

        template<typename... Args>
        void emplace(const KeyType& key, Args&&... args)
        {
            if (m_Root == m_NIL)
            {
                m_Root = std::make_shared<Node>(key, Color::Black, m_NIL, m_NIL, m_NIL, std::forward<Args>(args)...);

                ++m_Size;

                return;
            }

            std::shared_ptr<Node> nodeToAttachTo = m_NIL;
            std::shared_ptr<Node> iterator = m_Root;

            while (iterator != m_NIL)
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
                nodeToAttachTo->left = std::make_shared<Node>(key, Color::Red, nodeToAttachTo, m_NIL, m_NIL, std::forward<Args>(args)...);
                nodeToAttachTo->left->left = nodeToAttachTo->left->right = m_NIL;

                insertFixup(nodeToAttachTo->left);
            }
            else
            {
                nodeToAttachTo->right = std::make_shared<Node>(key, Color::Red, nodeToAttachTo, m_NIL, m_NIL, std::forward<Args>(args)...);
                nodeToAttachTo->right->left = nodeToAttachTo->left->right = m_NIL;

                insertFixup(nodeToAttachTo->right);
            }

            ++m_Size;
        }
        
        void erase(const KeyType& key)
        {
            std::shared_ptr<Node> z = find(key);
            
            if (z == m_NIL) 
            {
                debug::Log("Key not found");
                return;
            }

            std::shared_ptr<Node> y = z;
            std::shared_ptr<Node> x;

            Color yOriginalColor = y->color;

            if (z->left == m_NIL)
            {
                x = z->right;
                transplant(z, z->right);
            }
            else if (z->right == m_NIL)
            {
                x = z->left;
                transplant(z, z->left);
            }
            else
            {
                y = findMinNodeInSubTree(z->right);
                yOriginalColor = y->color;
                x = y->right;

                if (y->parent.lock() == z)
                {
                    x->parent = y;
                }
                else
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }

                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }

            if (yOriginalColor == Color::Black) eraseFixup(x);

            --m_Size;
        }

        bool contains(const KeyType& key) const
        {
            if (find(key) != m_NIL) return true;
            else return false;
        }

        size_t size() const { return m_Size; }

        ValueType& operator[](const KeyType& key)
        {
            std::shared_ptr<Node> node = find(key);

            if (node != m_NIL) return node->value;
            else
            {
                emplace(key);
                return find(key)->value;
            }
        }

        //Debug
        void printBFS() const
        {
            if (m_Root == m_NIL)
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

                    if (current->left != m_NIL) q.push(current->left);
                    if (current->right != m_NIL) q.push(current->right);
                }

                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    };
}