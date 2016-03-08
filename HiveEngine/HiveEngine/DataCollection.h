#pragma once

#include <unordered_map>
#include <vector>

namespace Hive
{

	template <class T>
	class DataCollection
	{
	protected:
		static const int DEFAULT_COLLECTION_SIZE = 20;
		static std::unordered_map<std::string, std::size_t> index_map;
		static std::vector<T> data;
		static std::size_t head;

	public:
		static void reserve(std::size_t size);
		static bool hasKey(std::string key);
		static std::size_t getIndex(std::string key);
		static T* getItem(std::size_t index);
		
		//Copies from data, keeping data afterwards is unnecessary.
		static void addItem(std::string key, const T& new_data);
	};

	template <class T>
	std::size_t DataCollection<T>::head = 0;

	template <class T>
	std::unordered_map<std::string, std::size_t> DataCollection<T>::index_map = std::unordered_map<std::string, std::size_t>(DEFAULT_COLLECTION_SIZE);

	template <class T>
	std::vector<T> DataCollection<T>::data = std::vector<T>(DEFAULT_COLLECTION_SIZE);

	template <class T>
	void DataCollection<T>::reserve(std::size_t size)
	{
		index_map.reserve(size);
		data.reserve(size);
	}

	template <class T>
	bool DataCollection<T>::hasKey(std::string key)
	{
		return index_map.count(key) > 0;
	}

	template <class T>
	std::size_t DataCollection<T>::getIndex(std::string key) {
		return index_map[key];
	}

	template <class T>
	T* DataCollection<T>::getItem(std::size_t index) {
		return &data[index];
	}

	template <class T>
	void DataCollection<T>::addItem(std::string key, const T& new_data) {
		data.push_back(new_data);
		index_map.emplace(key, head++);
	}
}