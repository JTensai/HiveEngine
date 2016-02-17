#pragma once

#include <unordered_map>
#include <vector>

namespace Hive
{

	template <class T>
	class DataCollection
	{
	private:
		std::unordered_map<std::string, std::size_t> _indexMap;
		std::vector<T> _data;
		std::size_t _head;

	public:
		DataCollection();
		DataCollection(std::size_t size);

		bool hasKey(std::string key);
		std::size_t getIndex(std::string key);
		std::size_t operator[](std::string key);
		T* getItem(std::size_t index);
		T* operator[](std::size_t index);

		//Copies from data, keeping data afterwards is unnecessary.
		void addItem(std::string key, const T* data);

		~DataCollection();
	};

	template <class T>
	DataCollection<T>::DataCollection() {
		_head = 0;
	}

	template <class T>
	DataCollection<T>::DataCollection(std::size_t size) {
		_indexMap = std::unordered_map(size);
		_head = 0;
		_data(size);
	}

	template <class T>
	bool DataCollection<T>::hasKey(std::string key)
	{
		return _indexMap.count(key);
	}

	template <class T>
	std::size_t DataCollection<T>::getIndex(std::string key) {
		return _indexMap[key];
	}
	template <class T>
	std::size_t DataCollection<T>::operator[](std::string key) {
		return _indexMap[key];
	}

	template <class T>
	T* DataCollection<T>::getItem(std::size_t index) {
		return &_data[index];
	}

	template <class T>
	T* DataCollection<T>::operator[](std::size_t index) {
		return &_data[index];
	}

	template <class T>
	void DataCollection<T>::addItem(std::string key, const T* data) {
		_data.push_back(*data);
		_indexMap.emplace(key, _head++);
	}

	template <class T>
	DataCollection<T>::~DataCollection() {}

}