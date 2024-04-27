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

            template<typename... Args>
            Node(const KeyType& k, Args&&... args)
                : key(k), value(std::forward<Args>(args)...) {}

            //Debug
            ~Node()
            {
                debug::Log("Node Destroyed");
            }
        };

        std::unique_ptr<Node> m_Root;

        size_t m_Size;

        
        // ------- Utilities -------

        void realInsert(std::unique_ptr<Node>& node, const KeyType& key, const ValueType& value)
        {
            if (!node)
            {
                node = std::make_unique<Node>(key, value);
                ++m_Size;
            }
            else if (key < node->key) realInsert(node->left, key, value);
            else if (key > node->key) realInsert(node->right, key, value);
            else
            {
                debug::Log("Element with this key already exists");
                return;
            }
        }

        void realInsert(std::unique_ptr<Node>& node, KeyType&& key, ValueType&& value)
        {
            if (!node)
            {
                node = std::make_unique<Node>(std::move(key), std::move(value));
                ++m_Size;
            }
            else if (key < node->key) realInsert(node->left, std::move(key), std::move(value));
            else if (key > node->key) realInsert(node->right, std::move(key), std::move(value));
            else
            {
                debug::Log("Element with this key already exists");
                return;
            }
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
            else
            {
                debug::Log("Element with this key already exists");
                return;
            }
        }

        std::unique_ptr<Node>& find(std::unique_ptr<Node>& node, const KeyType& key)
        {
            if (!node)
            {
                debug::Log("There's  no node with such key");
                return node; //nullptr
            }
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

        void transplant(std::unique_ptr<Node>& u, std::unique_ptr<Node>& v)
        {
            std::unique_ptr<Node> tmp = std::move(v);
            u = std::move(tmp);
        }

        void erase(std::unique_ptr<Node>& node)
        {
            if (!node->left && !node->right) node.reset();
            else if (!node->left) transplant(node, node->right);
            else if (!node->right) transplant(node, node->left);
            else
            {
                std::unique_ptr<Node>& replacementNode = findMinNodeInSubTree(node->right);

                node->key = replacementNode->key;
                node->value = replacementNode->value;
                erase(replacementNode);
                return;
            }

            --m_Size;
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

        void insert(KeyType&& key, ValueType&& value)
        {
            realInsert(m_Root, std::move(key), std::move(value));
        }

        void insert(const std::pair<KeyType, ValueType>& pair)
        {
            realInsert(m_Root, pair.first, pair.second);
        }

        void insert(std::pair<KeyType, ValueType>&& pair)
        {
            realInsert(m_Root, std::move(pair.first), std::move(pair.second));
        }

        template<typename... Args>
        void emplace(const KeyType& key, Args&&... args)
        {
            realEmplace(m_Root, key, std::forward<Args>(args)...);
        }

        void erase(const KeyType& key)
        {
            std::unique_ptr<Node>& node = find(m_Root, key);

            if (!node) return;

            erase(node);
        }

        ValueType& operator[](const KeyType& key)
        {
            std::unique_ptr<Node>& node = find(m_Root, key);
            
            if (node) return node->value;
            else
            {
                debug::Log("Inserting non-existed element");
                realInsert(m_Root, key, ValueType());

                return find(m_Root, key)->value;
            }
        }

        bool contains(const KeyType& key) const
        {
            if (find(m_Root, key) != nullptr) return true;
            else return false;
        }
       
        //Debug
        void printOut()
        {
            realPrintOut(m_Root);
        }
    };
}