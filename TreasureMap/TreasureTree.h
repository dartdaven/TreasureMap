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

            Node(const Key& k, const Value& v) : key(k), value(v) {}
        }

        std::unique_ptr<Node> m_Root;

        void realInsert(std::unique_ptr<Node>& node, const KeyType& key, const ValueType& value)
        {
            if (!node) node = std::make_unique<Node>(key, value);
            else if (key < node->key) realInsert(node->left, key, value);
            else if (key > node->key) realInsert(node->right, key, value);
            else node->value = value; //Update the value in node
        }


    public:
        TreasureTree(std::initializer_list<std::pair<KeyType, ValueType>> initList)
        {
            for (const auto& pair : initList)
            {
                insert(pair.first, pair.second);
            }
        }

        void insert(const KeyType& key, const ValueType& value)
        {
            realInsert(root, key, value);
        }

        void insert(const std::pair<KeyType, ValueType>& pair)
        {
            realInsert(root, pair.first, pair.second);
        }

        void erase(const KeyType& key)
        {

        }

        ValueType& operator[](const KeyType& key)
        {

        }
    };
}