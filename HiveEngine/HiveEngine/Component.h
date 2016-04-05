#pragma once

#include <algorithm>
#include <vector>

#include <glm\glm.hpp>

#include "Data.h"
#include "ObjectPool.h"

namespace Hive
{

	template <class T>
	class Component
	{
	protected:
		static const int DEFAULT_POOL_SIZE = 10;
		static std::vector<Handle> id_to_index;
		static ObjectPool<T> pool;

	public:
		static void initialize();
		static Handle create_component();
		static T* get_component(Handle id);
		static void destroy_component(Handle id);
		static bool is_active(Handle id);

		static void preupdate() {}
		static void update_all(float delta);
		virtual void update_component(float delta) = 0;
		static void postupdate() {}

		static const ObjectPool<T>& view_pool() { return pool; }
	};

	template <class T>
	ObjectPool<T> Component<T>::pool = ObjectPool<T>(DEFAULT_POOL_SIZE);

	template <class T>
	std::vector<Handle> Component<T>::id_to_index = std::vector<Handle>(DEFAULT_POOL_SIZE);

	template <class T>
	void Component<T>::initialize()
	{
		std::fill(id_to_index.begin(), id_to_index.end(), -1);
	}

	template <class T>
	Handle Component<T>::create_component()
	{
		Handle index = pool.create();
		std::vector<Handle>::iterator iter, begin, end;
		begin = id_to_index.begin();
		end = id_to_index.end();
		iter = std::find(begin, end, -1);
		if (iter == end)
		{
			int id = id_to_index.capacity();
			id_to_index.push_back(index);
			return (Handle) id;
		}
		*iter = index;
		return iter - begin;
	}

	template <class T>
	T* Component<T>::get_component(Handle id)
	{
		if (id < 0 || id >= id_to_index.capacity())
			throw std::out_of_range("get_component id out of bounds");
		int index = id_to_index[id];
		if (index < 0 || index >= pool.capacity())
			throw std::out_of_range("get_component index out of bounds");
		return pool.get(index);
	}

	template <class T>
	void Component<T>::destroy_component(Handle id)
	{
		if (id < 0 || id >= id_to_index.capacity()) throw std::out_of_range("destroy_component id out of bounds");
		
		int index = id_to_index[id];
		if (index < 0 || index >= pool.capacity()) throw std::out_of_range("destroy_component index out of bounds");
		pool.remove(index);
		id_to_index[id] = -1;
	}

	template <class T>
	void Component<T>::update_all(float delta)
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
				t.update_component(delta);
			}
		}
		// TODO: if i/cap is significantly larger than num_used/cap, the objectpool should be sorted.
		T::postupdate();
	}

	template <class T>
	bool Component<T>::is_active(Handle id)
	{
		if (id < 0 || id >= id_to_index.capacity()) throw std::out_of_range("is_active id out of bounds");
		int index = id_to_index[id];

		if (index == -1)
			return false;

		if (index < 0 || index >= pool.capacity()) throw std::out_of_range("is_active index out of bounds");
		return pool.is_used(index);
	}


	template <class T>
	class DrawableComponent : public Component<T>
	{
	public:
		static void predraw() {}
		static void draw_all(const glm::mat4& VP);
		virtual void draw_component(const glm::mat4& VP) = 0;
		static void postdraw() {}
	};

	template <class T>
	void DrawableComponent<T>::draw_all(const glm::mat4& VP)
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
