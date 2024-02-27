#pragma once

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

    std::unique_ptr<Node> root;

public:
    void insert(const KeyType& key, const ValueType& value)
    {

    }

    void insert(const std::pair<KeyType, ValueType>& pair)
    {
        insert(pair.first, pair.second);
    }

    void erase(const KeyType& key)
    {

    }

    ValueType& operator[](const KeyType& key)
    {

    }
};