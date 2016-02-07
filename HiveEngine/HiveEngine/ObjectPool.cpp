#include "ObjectPool.h"


template <class T>
ObjectPool::ObjectPool(int size)
{
	_size = size;
	_pool = new T[size];
	_used = new bool[size];
}

template <class T>
T* ObjectPool::get(int index)
{
	if (index < 0 || index >= _size || !_used[index]) return 0;
	return &_pool[index];
}

template <class T>
T* ObjectPool::create()
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

template <class T>
void ObjectPool::remove(int index) {
	if (index < 0 || index >= size) return;
	_used[index] = false;
}

template <class T>
ObjectPool::~ObjectPool()
{
	if (_pool)
	{
		delete[] _pool;
	}
	if (_used)
	{
		delete[] _used;
	}
}
