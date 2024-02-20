#pragma once

#include <vector>
#include <list>
#include <utility> //for pair
#include <functional> //for custom hash function

#include "Debug.h"

namespace dvd 
{
	template<typename KeyType, typename ValueType>
	class TreasureMap 
	{
	private:
		std::vector<std::list<std::pair<KeyType, ValueType>>> m_Table;
		
		/* Number of elemebts contained */
		size_t m_Size;

		std::function<size_t(const KeyType&)> m_HashFunction; //I believe that the argument is wrong here

	public: 
		//TODO something with default constructor
		TreasureMap() : m_Table(8), m_Size(0)
		{
			debug::Log("No CustomHashFunction specified, using std::hash");

			m_HashFunction = [this](const KeyType& key) {	return std::hash<KeyType>{}(key) % m_Table.size(); };

		}

		TreasureMap(std::initializer_list<std::pair<KeyType, ValueType>> initList) : TreasureMap() //Why i can't use reference here
		{
			for (const auto& pair : initList) 
			{
				insert(pair.first, pair.second);
			}
		}
		
		size_t bucket_count() const { return m_Table.size(); }

		size_t size() const { return m_Size; }

		/*
		Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
		TODO increases table size if size is more than number of buckets
		*/
		void insert(const KeyType& key, const ValueType& value)
		{
			size_t index = m_HashFunction(key);

			//TODO replace with iterators
			if (m_Table[index].empty())
			{
				m_Table[index].emplace_back(key, value);
				++m_Size;
			}
			else
			{
				bool contains{ false };

				for (const auto& kv : m_Table[index])
				{
					if (key == kv.first) contains = true;
				}

				if (contains)
				{
					debug::Log("Element with this key already exists in this map");
				}
				else
				{
					m_Table[index].emplace_back(key, value);
					++m_Size;
				}
			}
		}

		void insert(const std::pair<KeyType, ValueType>& pair) //Why it does not work without const
		{
			insert(pair.first, pair.second);
		}
		
		void erase(const KeyType& key)
		{
			size_t index = m_HashFunction(key);

			if (!m_Table[index].empty())
			{
				for (auto it = m_Table[index].begin(); it != m_Table[index].end(); ++it)
				{
					if (key == it->first)
					{
						m_Table[index].erase(it);
						--m_Size;

						return;
					}
				}
				debug::Log("Nothing to erase found");
			}
		}

		ValueType& operator[](const KeyType& key)
		{
			size_t index = m_HashFunction(key);

			if (!m_Table[index].empty())
			{
				for (auto it = m_Table[index].begin(); it != m_Table[index].end(); ++it)
				{
					if (key == it->first)
					{
						return it->second;
					}
				}

				debug::Log("Nothing to access found");
			}
		}

		bool contains(const KeyType& key)
		{
			size_t index = m_HashFunction(key);

			if (!m_Table[index].empty())
			{
				for (auto it = m_Table[index].begin(); it != m_Table[index].end(); ++it)
				{
					if (key == it->first)
					{
						return true;
					}
				}

				return false;
			}
		}

		bool contains_by_value(const ValueType& value)
		{

		}

		void printOut()
		{
			for (const auto& list : m_Table)
			{
				if (!list.empty())
				{
					for (const auto& pair : list)
					{
						std::cout << pair.first << ", " << pair.second << " | ";
					}
					std::cout << std::endl;
				}
			}
		}
	};

}