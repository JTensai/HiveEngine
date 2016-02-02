#include "DataCollection.h"


template <class T>
DataCollection::DataCollection() {
	_size = 0;
	_head = 0;
}

template <class T>
DataCollection::DataCollection(std::size_t size) {
	_indexMap = std::unordered_map(size);
	_size = size;
	_head = 0;
	_data = new T [size];
}

template <class T>
std::size_t DataCollection::getSize() {
	return _size;
}

template <class T>
std::size_t DataCollection::getIndex(std::string key) {
	return _indexMap[key];
}
template <class T>
std::size_t DataCollection::operator[](std::string key) {
	return _indexMap[key];
}

template <class T>
const T* DataCollection::getItem(std::size_t index) {
	return &_data[index];
}
template <class T>
const T* DataCollection::operator[](std::size_t index) {
	return &_data[index];
}

template <class T>
void DataCollection::addItem(std::string key, const T* data) {
	_data[_head] = *data;
	_indexMap.emplace(key, _head++);
}

template <class T>
void DataCollection::expandSize(std::size_t delta) {
	_indexMap.rehash(_size + delta);
	T* newData = new T[_size + delta];
	for (int i = 0; i <= _head; i++) {
		newData[i] = _data[i];
	}
	delete[] _data;
	_data = newData;
}

template <class T>
DataCollection::~DataCollection() {
	if (_data)
		delete[] _data;
}
