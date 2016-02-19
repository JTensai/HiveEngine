#pragma once

#include <unordered_map>
#include <vector>

namespace Hive
{

	template <class T>
	class DataCollection
	{
	private:
		std::unordered_map<std::string, std::size_t> index_map;
		std::vector<T> data;
		std::size_t head;

	public:
		DataCollection();
		DataCollection(std::size_t size);

		bool hasKey(std::string key);
		std::size_t getIndex(std::string key);
		std::size_t operator[](std::string key);
		T* getItem(std::size_t index);
		T* operator[](std::size_t index);

		//Copies from data, keeping data afterwards is unnecessary.
		void addItem(std::string key, const T& new_data);

		~DataCollection();
	};

	template <class T>
	DataCollection<T>::DataCollection() {
		head = 0;
	}

	template <class T>
	DataCollection<T>::DataCollection(std::size_t size) {
		index_map = std::unordered_map(size);
		head = 0;
		data(size);
	}

	template <class T>
	bool DataCollection<T>::hasKey(std::string key)
	{
		return index_map.count(key);
	}

	template <class T>
	std::size_t DataCollection<T>::getIndex(std::string key) {
		return index_map[key];
	}
	template <class T>
	std::size_t DataCollection<T>::operator[](std::string key) {
		return index_map[key];
	}

	template <class T>
	T* DataCollection<T>::getItem(std::size_t index) {
		return &data[index];
	}

	template <class T>
	T* DataCollection<T>::operator[](std::size_t index) {
		return &data[index];
	}

	template <class T>
	void DataCollection<T>::addItem(std::string key, const T& new_data) {
		data.push_back(new_data);
		index_map.emplace(key, head++);
	}

	template <class T>
	DataCollection<T>::~DataCollection() {}

}