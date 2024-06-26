#pragma once

#include <vector>
#include <list>
#include <utility> //for pair
#include <functional> //for custom hash function
#include <cassert>

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

		std::function<size_t(const KeyType&)> m_HashFunction;

		size_t hash(const KeyType& key) const
		{
			assert(m_HashFunction && "Hash function is absent");

			return m_HashFunction(key) % m_Table.size();
		}

	public: 
		TreasureMap() : m_Table(8), m_Size(0)
		{
			debug::Log("No CustomHashFunction specified, using std::hash");

			m_HashFunction = [](const KeyType& key) { return std::hash<KeyType>{}(key); };

		}

		TreasureMap(std::initializer_list<std::pair<KeyType, ValueType>> initList) : TreasureMap()
		{
			for (const auto& pair : initList) 
			{
				insert(std::move(pair));
			}
		}

		TreasureMap(std::function<size_t(const KeyType&)> customHashFunction) : m_Table(8), m_Size(0), m_HashFunction(customHashFunction)
		{
			debug::Log("CustomHashFunction is used");
		}
		
		size_t bucket_count() const { return m_Table.size(); }

		size_t size() const { return m_Size; }

		/*
		Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
		TODO increases table size if size is more than number of buckets
		*/
		void insert(const KeyType& key, const ValueType& value)
		{
			size_t index = hash(key);

			if (m_Table[index].empty())
			{
				m_Table[index].emplace_back(key, value);
				++m_Size;
			}
			else
			{
				for (auto& [k, v] : m_Table[index])
				{
					if (key == k)
					{
						debug::Log("Element with this key already exists");
						return;
					}
				}
				m_Table[index].emplace_back(key, value);
				++m_Size;
			}
		}

		//rvalue key value
		//This is actually emplace according to std::unordered map
		void insert(KeyType&& key, ValueType&& value)
		{
			size_t index = hash(key);

			if (m_Table[index].empty())
			{
				m_Table[index].emplace_back(std::move(key), std::move(value));
				++m_Size;
			}
			else
			{
				for (auto& [k, v] : m_Table[index])
				{
					if (key == k)
					{
						debug::Log("Element with this key already exists");
						return;
					}
				}
				m_Table[index].emplace_back(std::move(key), std::move(value));
				++m_Size;
			}
		}

		//lvalue pair
		void insert(const std::pair<KeyType, ValueType>& pair)
		{
			insert(pair.first, pair.second);
		}

		//rvalue pair
		void insert(std::pair<KeyType, ValueType>&& pair)
		{
			size_t index = hash(pair.first);

			if (m_Table[index].empty())
			{
				m_Table[index].push_back(std::move(pair));
				++m_Size;
			}
			else
			{
				for (auto& [k, v] : m_Table[index])
				{
					if (pair.first == k)
					{
						debug::Log("Element with this key already exists");
						return;
					}
				}
				m_Table[index].push_back(std::move(pair));
				++m_Size;
			}
		}

		template<typename... Args>
		void emplace(const KeyType& key, Args&&... args)
		{
			size_t index = hash(key);

			if (m_Table[index].empty())
			{
				m_Table[index].emplace_back(key, ValueType(std::forward<Args>(args)...));
				++m_Size;
			}
			else
			{
				for (const auto& [k, v] : m_Table[index])
				{
					if (key == k)
					{
						debug::Log("Element with this key already exists");
						return;
					}
				}

				m_Table[index].emplace_back(key, ValueType(std::forward<Args>(args)...));
				++m_Size;
			}

		}
		
		void erase(const KeyType& key)
		{
			size_t index = hash(key);

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
			size_t index = hash(key);

			if (!m_Table[index].empty())
			{
				for (auto it = m_Table[index].begin(); it != m_Table[index].end(); ++it)
				{
					if (key == it->first)
					{
						return it->second;
					}
				}
			}

			debug::Log("Inserting non-existed element");
			insert(key, ValueType());
			
			for (auto it = m_Table[index].begin(); it != m_Table[index].end(); ++it)
			{
				if (key == it->first)
				{
					return it->second;
				}
			}
			
			assert(false && "Error with accessing the value by key");
		}

		bool contains(const KeyType& key) const
		{
			size_t index = hash(key);

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

			return false;
		}

		bool contains_by_value(const ValueType& value)
		{
			//TODO
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
				}
				std::cout << std::endl;
			}
		}
	};
}