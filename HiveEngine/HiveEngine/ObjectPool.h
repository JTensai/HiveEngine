#pragma once

template <class T>
class ObjectPool
{
private:
	int _size;
	T* _pool;
	bool* _used;
public:
	ObjectPool(int size);
	T* get(int index);
	void remove(int index);
	T* create();
	~ObjectPool();
};

