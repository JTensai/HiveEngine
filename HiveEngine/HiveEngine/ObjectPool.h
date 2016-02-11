#pragma once

#include <vector>

template <class T> class ObjectPool
{
private:
	std::vector<T> _pool;
	std::vector<bool> _used;
public:
	ObjectPool();
	ObjectPool(int size);

	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;

	iterator begin();
	const_iterator cbegin();

	iterator end();
	const_iterator cend();

	T* get(int index);
	void remove(int index);
	T* create();

	~ObjectPool();
};

template <class T> ObjectPool<T>::ObjectPool() {}

template <class T> ObjectPool<T>::ObjectPool(int size)
{
	_used = std::vector<bool>(size);
	_pool = std::vector<T>(size);
}

template <class T> typename ObjectPool<T>::iterator ObjectPool<T>::begin()
{
	return _pool.begin();
}
template <class T> typename ObjectPool<T>::const_iterator ObjectPool<T>::cbegin()
{
	return _pool.cbegin();
}

template <class T> typename ObjectPool<T>::iterator ObjectPool<T>::end()
{
	return _pool.end();
}
template <class T> typename ObjectPool<T>::const_iterator ObjectPool<T>::cend()
{
	return _pool.cend();
}

template <class T> T* ObjectPool<T>::get(int index)
{
	return &_pool.at(index);
}

template <class T> T* ObjectPool<T>::create()
{
	for (int i = 0; i < _size; i++)
	{
		if (!_used[i])
		{
			_used[i] = true;
			return &_pool[index];
		}
	}
	return 0;
}

template <class T> void ObjectPool<T>::remove(int index) {
	if (index < 0 || index >= size) throw std::out_of_range;
	_used[index] = false;
}

template <class T> ObjectPool<T>::~ObjectPool()
{
	if (_used)
	{
		delete[] _used;
	}
}

