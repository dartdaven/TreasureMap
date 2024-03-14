#pragma once

namespace dvd
{
    template<typename KeyType, typename ValueType>
    class TreasureTree
    {
        struct Node
        {
            KeyType key;
            ValueType value;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;

            Node(const KeyType& k, const ValueType& v) : key(k), value(v) {}

            //Debug
            ~Node()
            {
                debug::Log("Node Destroyed");
            }
        };

        std::unique_ptr<Node> m_Root;

        size_t m_Size;

        // ------- Utilities -------
        //TODO get rid of recursion

        void realInsert(std::unique_ptr<Node>& node, const KeyType& key, const ValueType& value)
        {
            if (!node)
            {
                node = std::make_unique<Node>(key, value);
                ++m_Size;
            }
            else if (key < node->key) realInsert(node->left, key, value);
            else if (key > node->key) realInsert(node->right, key, value);
            else node->value = value; //Update the value in node
        }

        template<typename... Args>
        void realEmplace(std::unique_ptr<Node>& node, const KeyType& key, Args&&... args)
        {
            if (!node)
            {
                node = std::make_unique<Node>(key, std::forward<Args>(args)...);
                ++m_Size;
            }
            else if (key < node->key) realEmplace(node->left, key, std::forward<Args>(args)...);
            else if (key > node->key) realEmplace(node->right, key, std::forward<Args>(args)...);
            else node->value = ValueType(std::forward<Args>(args)...);
        }

        std::unique_ptr<Node>& find(std::unique_ptr<Node>& node, const KeyType& key)
        {
            if (!node) return node; //nullptr
            else if (key < node->key) find(node->left, key);
            else if (key > node->key) find(node->right, key);
            else return node;
        }

        //In-Order traversal
        void realPrintOut(std::unique_ptr<Node>& node)
        {
            if (!node) return;

            realPrintOut(node->left);
            std::cout << node->key << " : " << node->value << std::endl;
            realPrintOut(node->right);
        }

        std::unique_ptr<Node>& findMinNodeInSubTree(std::unique_ptr<Node>& node)
        {
            if (!node->left) return node;
            else findMinNodeInSubTree(node->left);            
        }

        //Overload that takes reference
        void erase(std::unique_ptr<Node>& node)
        {
            if (!node->left && !node->right) node.reset();
            else if (!node->left) node = std::move(node->right);
            else if (!node->right) node = std::move(node->left);
            else
            {
                std::unique_ptr<Node>& replacementNode = findMinNodeInSubTree(node->right);

                node->key = replacementNode->key;
                node->value = replacementNode->value;
                erase(replacementNode);
            }
        }

    public:
        TreasureTree(std::initializer_list<std::pair<KeyType, ValueType>> initList)
        {
            for (const auto& [k, v] : initList)
            {
                realInsert(m_Root, k, v);
            }
        }

        size_t size() const { return m_Size; }

        void insert(const KeyType& key, const ValueType& value)
        {
            realInsert(m_Root, key, value);
        }

        void insert(const std::pair<KeyType, ValueType>& pair)
        {
            realInsert(m_Root, pair.first, pair.second);
        }

        template<typename... Args>
        void emplace(const KeyType& key, Args&&... args)
        {
            realEmplace(m_Root, key, std::forward<Args>(args)...);
        }

        void erase(const KeyType& key)
        {
            erase(find(m_Root, key));
        }

        ValueType& operator[](const KeyType& key)
        {
            std::unique_ptr<Node>& node = find(m_Root, key);
            
            if (node) return node->value;
            else debug::Log("Nothing to access found");
        }

        void printOut()
        {
            realPrintOut(m_Root);
        }

        bool contains(const KeyType& key)
        {
            if (find(m_Root, key) != nullptr) return true;
            else return false;
        }
    };
}