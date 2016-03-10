#pragma once

#include <algorithm>
#include <vector>

#include <glm\glm.hpp>

#include "ObjectPool.h"

namespace Hive
{

	template <class T>
	class Component
	{
	protected:
		static const int DEFAULT_POOL_SIZE = 10;
		static std::vector<int> id_to_index;
		static ObjectPool<T> pool;

	public:
		static void initialize();
		static int create_component();
		static T* get_component(int id);
		static void destroy_component(int id);

		static void preupdate() {}
		static void update(float delta, bool is_a);
		virtual void update_component(float delta, bool is_a) = 0;
		static void postupdate() {}
	};

	template <class T>
	ObjectPool<T> Component<T>::pool = ObjectPool<T>(DEFAULT_POOL_SIZE);

	template <class T>
	std::vector<int> Component<T>::id_to_index = std::vector<int>(DEFAULT_POOL_SIZE);

	template <class T>
	void Component<T>::initialize()
	{
		std::fill(id_to_index.begin(), id_to_index.end(), -1);
	}

	template <class T>
	int Component<T>::create_component()
	{
		int index = pool.create();
		std::vector<int>::iterator iter, begin, end;
		begin = id_to_index.begin();
		end = id_to_index.end();
		iter = std::find(begin, end, -1);
		if (iter == end)
		{
			int id = id_to_index.capacity();
			id_to_index.push_back(index);
			return id;
		}
		*iter = index;
		return iter - begin;
	}

	template <class T>
	T* Component<T>::get_component(int id)
	{
		if (id < 0 || id >= id_to_index.capacity()) throw std::out_of_range("get_component id out of bounds");
		int index = id_to_index[id];
		if (index < 0 || index >= pool.capacity()) throw std::out_of_range("get_component index out of bounds");
		return pool.get(index);
	}

	template <class T>
	void Component<T>::destroy_component(int id)
	{
		if (id < 0 || id >= id_to_index.capacity()) throw std::out_of_range("destroy_component id out of bounds");
		int index = id_to_index[id];
		if (index < 0 || index >= pool.capacity()) throw std::out_of_range("destroy_component index out of bounds");
		pool.remove(index);
		id_to_index[id] = -1;
	}

	template <class T>
	void Component<T>::update(float delta, bool is_a)
	{
		T::preupdate();
		int i = 0;
		int num = 0;
		int cap = pool.capacity();
		int num_used = pool.get_num_in_use();
		for (; i < cap && num < num_used; ++i)
		{
			if (pool.is_used(i))
			{
				++num;
				T& t = *pool.get(i);
				t.update_component(delta, is_a);
			}
		}
		// TODO: if i/cap is significantly larger than num_used/cap, the objectpool should be sorted.
		T::postupdate();
	}


	template <class T>
	class DrawableComponent : public Component<T>
	{
	public:
		static void predraw() {}
		static void draw(const glm::mat4& VP);
		virtual void draw_component(const glm::mat4& VP) = 0;
		static void postdraw() {}
	};

	template <class T>
	void DrawableComponent<T>::draw(const glm::mat4& VP)
	{
		T::predraw();
		int i = 0;
		int num = 0;
		int cap = pool.capacity();
		int num_used = pool.get_num_in_use();
		for (; i < cap && num < num_used; ++i)
		{
			if (pool.is_used(i))
			{
				++num;
				T& t = *pool.get(i);
				t.draw_component(VP);
			}
		}
		T::postdraw();
	}
}
