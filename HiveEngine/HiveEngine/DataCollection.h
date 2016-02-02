#pragma once

#include <unordered_map>

template <class T>
class DataCollection
{
private:
	std::unordered_map<std::string, std::size_t> _indexMap;
	T* _data;
	std::size_t _size;
	std::size_t _head;

public:
	DataCollection();
	DataCollection(std::size_t size);

	std::size_t getSize();

	std::size_t getIndex(std::string key);
	std::size_t operator[](std::string key);
	const T* getItem(std::size_t index);
	const T* operator[](std::size_t index);

	//Copies from data, keeping data afterwards is unnecessary.
	void addItem(std::string key, const T* data);

	void expandSize(std::size_t delta);

	~DataCollection();
};

