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
		std::vector<std::list<std::pair<const KeyType&, const ValueType&>>> m_Table;
		
		/* Number of elemebts contained */
		size_t m_Size;

		std::function<size_t(const KeyType&)> m_CustomHashFunction; //I believe that the argument is wrong here
	public: 
		TreasureMap(size_t BucketsNumber = 8) : m_Table(BucketsNumber), m_BucketsNumber(BucketsNumber) {}

		TreasureMap(std::initializer_list<std::pair<const KeyType&, const ValueType&>>) : TreasureMap(initList.size()) 
		{
			for (const auto& pair : initList) 
			{
				insert(pair.first, pair.second);
			}
		}
		
		size_t bucket_cont() { return m_Table.size(); }

		const size_t& size() const { return m_Size; } //TODO check what is right to return in this case

		/*
		Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key.
		
		*/
		void insert(const KeyType& key, const ValueType& value)
		{
			//TODO compare size and the buckets number, reallocate if more

			size_t index;

			//TODO move this to constructor
			if (m_CustomHashFunction)
			{
				index = m_CustomHashFunction(key) % m_Table.size();
			}
			else
			{
				debug::Log("No CustomHashFunction, using  std::hash");

				index = std::hash<KeyType>{} (key) % m_Table.size();
			}

			//TODO replace with iterators
			if (m_Table[index].empty())
			{
				m_Table[index].emplace_back(key, value);
				++m_Size;
			}
			else
			{
				bool contains{ false };

				for (const auto& [k, v] : m_Table[index])
				{
					if (key == k) contains = true;
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

		void insert(std::pair<const KeyType&, const ValueType&>> pair)
		{
			insert(pair.first, par.second);
		}
		
		void erase(const KeyType& key)
		{
			size_t index;

			if (m_CustomHashFunction)
			{
				index = m_CustomHashFunction(key) % m_Table.size();
			}
			else
			{
				debug::Log("No CustomHashFunction, using  std::hash");

				index = std::hash<KeyType>{} (key) % m_Table.size();
			}

			if (!m_Table[index].empty())
			{

				for (auto it = m_Table[index].begin(); it != m_Table[index].end(); ++it)
				{
					if (key == it->first)
					{
						m_Table[index].erase(it);
						--m_Size;

						break;
					}
				}
			}
		}

		ValueType& operator[](const KeyType& key)
		{

		}

		bool contains(const KeyType& key)
		{

		}

		bool contains_by_value(const ValueType& value)
	};

}