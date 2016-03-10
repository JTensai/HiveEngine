#pragma once

#include <unordered_map>
#include <vector>

namespace Hive
{

	template <class T>
	class DataCollection
	{
	protected:
		static const int DEFAULT_COLLECTION_SIZE = 10;
		static std::unordered_map<std::string, int> index_map;
		static std::vector<T> data;
		static int head;

	public:
		static void reserve(int size);
		static bool hasKey(std::string key);
		static int getIndex(std::string key);
		static T* getItem(int index);
		
		//Copies from data, keeping data afterwards is unnecessary.
		static void addItem(std::string key, const T& new_data);
	};

	template <class T>
	int DataCollection<T>::head = 0;

	template <class T>
	std::unordered_map<std::string, int> DataCollection<T>::index_map = std::unordered_map<std::string, int>(DEFAULT_COLLECTION_SIZE);

	template <class T>
	std::vector<T> DataCollection<T>::data = std::vector<T>(DEFAULT_COLLECTION_SIZE);

	template <class T>
	void DataCollection<T>::reserve(int size)
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
	int DataCollection<T>::getIndex(std::string key) {
		return index_map[key];
	}

	template <class T>
	T* DataCollection<T>::getItem(int index) {
		if (index < 0 || index >= data.size()) throw std::out_of_range("Data collection getItem index out of range.");
		return &data[index];
	}

	template <class T>
	void DataCollection<T>::addItem(std::string key, const T& new_data) {
		data.push_back(new_data);
		index_map.emplace(key, head++);
	}
}