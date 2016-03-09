#pragma once

#include <vector>

namespace Hive
{

	template <class T>
	class ObjectPool
	{
	private:
		int in_use;
		std::vector<T> pool;
		std::vector<bool> used;
	public:
		ObjectPool();
		ObjectPool(int size);

		class op_iterator
		{
		private:
			typename std::vector<T>::iterator t_iter;
			std::vector<bool>::iterator b_iter;
			std::vector<bool>::iterator b_iter_end;
		public:
			op_iterator() {}
			op_iterator(const op_iterator& o) :
				t_iter(o.t_iter), b_iter(o.b_iter), b_iter_end(o.b_iter_end) {};
			op_iterator(
				typename std::vector<T>::iterator t_iter, std::vector<bool>::iterator b_iter, std::vector<bool>::iterator b_iter_end) :
				t_iter(t_iter), b_iter(b_iter), b_iter_end(b_iter_end) {}
			op_iterator& operator++();
			op_iterator operator++(int);
			inline bool operator==(const op_iterator& o);
			inline bool operator!=(const op_iterator& o);
			inline T& operator*();
		};
		typedef op_iterator iterator;

		class cop_iterator
		{
		private:
			typename std::vector<T>::iterator t_iter;
			std::vector<bool>::iterator b_iter;
			std::vector<bool>::iterator b_iter_end;
		public:
			cop_iterator() {}
			cop_iterator(const cop_iterator& o) :
				t_iter(o.t_iter), b_iter(o.b_iter), b_iter_end(o.b_iter_end) {};
			cop_iterator(
				typename std::vector<T>::iterator t_iter, std::vector<bool>::iterator b_iter, std::vector<bool>::iterator b_iter_end) :
				t_iter(t_iter), b_iter(b_iter), b_iter_end(b_iter_end) {}
			cop_iterator& operator++();
			cop_iterator operator++(int);
			inline bool operator==(const cop_iterator& o);
			inline bool operator!=(const cop_iterator& o);
			inline const T& operator*();
		};
		typedef cop_iterator const_iterator;

		iterator begin();
		const_iterator cbegin();

		iterator end();
		const_iterator cend();

		T* get(int index);
		int get_num_in_use();
		bool is_used(int index);
		void remove(int index);
		int create();
		int count();
		int capacity();

		~ObjectPool();

	};

	template <class T>
	ObjectPool<T>::ObjectPool()
	{
		in_use = 0;
	}

	template <class T>
	ObjectPool<T>::ObjectPool(int size)
	{
		in_use = 0;
		used = std::vector<bool>(size);
		pool = std::vector<T>(size);
	}

	template <class T>
	typename ObjectPool<T>::iterator ObjectPool<T>::begin()
	{
		return op_iterator(pool.begin(), used.begin(), used.end());
	}
	template <class T>
	typename ObjectPool<T>::const_iterator ObjectPool<T>::cbegin()
	{
		return cop_iterator(pool.cbegin(), used.cbegin(), used.cbegin());
	}

	template <class T>
	typename ObjectPool<T>::iterator ObjectPool<T>::end()
	{
		return op_iterator(pool.end(), used.end(), used.end());
	}
	template <class T>
	typename ObjectPool<T>::const_iterator ObjectPool<T>::cend()
	{
		return cop_iterator(pool.cend(), used.cend(), used.cend());
	}

	template <class T>
	T* ObjectPool<T>::get(int index)
	{
		return &pool.at(index);
	}

	template <class T>
	int ObjectPool<T>::get_num_in_use()
	{
		return in_use;
	}

	template <class T>
	bool ObjectPool<T>::is_used(int index)
	{
		return used[index];
	}

	template <class T>
	int ObjectPool<T>::create()
	{
		for (int i = 0; i < used.size(); i++)
		{
			if (!used[i])
			{
				used[i] = true;
				++in_use;
				return i;
			}
		}
		return -1;
	}

	template <class T>
	void ObjectPool<T>::remove(int index)
	{
		if (index < 0 || index >= pool.size()) throw std::out_of_range("Objectpool remove index out of range.");
		used[index] = false;
		--in_use;
	}

	template <class T>
	int ObjectPool<T>::capacity()
	{
		return pool.capacity();
	}

	template <class T>
	int ObjectPool<T>::count()
	{
		return in_use;
	}

	template <class T>
	ObjectPool<T>::~ObjectPool() {}

	template <class T>
	typename ObjectPool<T>::op_iterator& ObjectPool<T>::op_iterator::operator++()
	{
		do
		{
			++b_iter; ++t_iter;
		} while (b_iter != b_iter_end && !(*b_iter));
		return *this;
	}

	template <class T>
	typename ObjectPool<T>::op_iterator ObjectPool<T>::op_iterator::operator++(int)
	{
		typename ObjectPool<T>::op_iterator tmp(*this);
		operator++();
		return tmp;
	}

	template <class T>
	bool ObjectPool<T>::op_iterator::operator==(const typename ObjectPool<T>::op_iterator& o)
	{
		return (t_iter == o.t_iter) && (b_iter == o.b_iter) && (b_iter_end == o.b_iter_end);
	}

	template <class T>
	bool ObjectPool<T>::op_iterator::operator!=(const typename ObjectPool<T>::op_iterator& o)
	{
		return !(*this == o);
	}

	template <class T>
	T& ObjectPool<T>::op_iterator::operator*()
	{
		return *t_iter;
	}

	template <class T>
	typename ObjectPool<T>::cop_iterator& ObjectPool<T>::cop_iterator::operator++()
	{
		do
		{
			++b_iter; ++t_iter;
		} while (b_iter != b_iter_end && !(*b_iter));
		return *this;
	}

	template <class T>
	typename ObjectPool<T>::cop_iterator ObjectPool<T>::cop_iterator::operator++(int)
	{
		typename ObjectPool<T>::cop_iterator tmp(*this);
		operator++();
		return tmp;
	}

	template <class T>
	bool ObjectPool<T>::cop_iterator::operator==(const typename ObjectPool<T>::cop_iterator& o)
	{
		return (t_iter == o.t_iter) && (b_iter == o.b_iter) && (b_iter_end == o.b_iter_end)
	}

	template <class T>
	bool ObjectPool<T>::cop_iterator::operator!=(const typename ObjectPool<T>::cop_iterator& o)
	{
		return !(*this == o);
	}

	template <class T>
	const T& ObjectPool<T>::cop_iterator::operator*()
	{
		return *t_iter;
	}
}