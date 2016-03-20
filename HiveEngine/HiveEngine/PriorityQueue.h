/*
* PriorityQueue.h
*
*  Created on: Dec 2, 2015
*      Author: ericseaman
*/

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <stdexcept>
#include <iostream>



template <class T>
class PriorityQueue {
private:
	T* pq;
	int pq_size;//current size of queue
	int mode;

	void balance(int index)
	{
		if (mode == ASCENDING)
		{
			ascending_balance(index);
		}
		else
		{
			descending_balance(index);
		}
	}

	void ascending_balance(int index)
	{
		int i = index + 1;
		int left_index = i * 2 - 1;
		int right_index = i * 2;
		int smallest = index;
		if (left_index <= pq_size - 1 && pq[left_index] < pq[index])
		{
			smallest = left_index;
		}
		if (right_index <= pq_size - 1 && pq[right_index] < pq[smallest])
		{
			smallest = right_index;
		}
		if (smallest != index)
		{
			T c = pq[index];
			pq[index] = pq[smallest];
			pq[smallest] = c;
			balance(smallest);
		}
	}

	void descending_balance(int index)
	{
		int i = index + 1;
		int left_index = i * 2 - 1;
		int right_index = i * 2;
		int largest = index;
		if (left_index <= pq_size - 1 && pq[left_index] > pq[index])
		{
			largest = left_index;
		}
		if (right_index <= pq_size - 1 && pq[right_index] > pq[largest])
		{
			largest = right_index;
		}
		if (largest != index)
		{
			T c = pq[index];
			pq[index] = pq[largest];
			pq[largest] = c;
			balance(largest);
		}
	}

	void decrease_key(T &c, int index)
	{
		if (mode == ASCENDING)
		{
			ascending_decrease_key(c, index);
		}
		else
		{
			descending_decrease_key(c, index);
		}
	}

	void ascending_decrease_key(T &c, int index)
	{
		int i = index + 1;
		int parent_index = (i / 2) - 1;
		while (i - 1 > 0 && pq[parent_index] > pq[i - 1])
		{
			pq[i - 1] = pq[parent_index];
			pq[parent_index] = c;
			i = parent_index + 1;
			parent_index = (i / 2) - 1;
		}
	}

	void descending_decrease_key(T &c, int index)
	{
		int i = index + 1;
		int parent_index = (i / 2) - 1;
		while (i - 1 > 0 && pq[parent_index] < pq[i - 1])
		{
			pq[i - 1] = pq[parent_index];
			pq[parent_index] = c;
			i = parent_index + 1;
			parent_index = (i / 2) - 1;
		}
	}

public:
	//smaller values are at head of queue
	static const int ASCENDING = 0;
	//larger values are at head of queue
	static const int DESCENDING = 1;

	PriorityQueue() {
		pq = nullptr;
		pq_size = 0;
		mode = ASCENDING;
	}

	PriorityQueue(int size) {
		pq = new T[size];
		pq_size = 0;
		mode = ASCENDING;
	}

	~PriorityQueue() {
	}

	void insert(T& c)
	{
		++pq_size;
		pq[pq_size - 1] = c;
		decrease_key(c, pq_size - 1);
	}

	T deleteMin()
	{
		T min = pq[0];
		pq[0] = pq[pq_size - 1];
		--pq_size;
		balance(0);
		return min;
	}

	int size()
	{
		return pq_size;
	}

	T get_index(int index)
	{
		try
		{
			/*if (index >= pqSize)
			{
				T empty;
				return empty;
			}*/
			return pq[index];
		}
		catch (const std::out_of_range& oor) {
			std::cerr << "Out of Range error: " << oor.what() << '\n';
		}

		throw std::out_of_range("");
	}

	void delete_object(T c)
	{
		T to_delete = pq[0];
		int i = 0;
		while (to_delete != c)
		{
			++i;
			if (i >= pq_size)
			{
				return;
			}
			to_delete = pq[i];
		}

		pq[i] = pq[pq_size - 1];
		--pq_size;
		balance(i);
	}

	void set_mode(int new_mode)
	{
		mode = new_mode;
	}

	bool contains(T obj)
	{
		for (int i = 0; i < pq_size; ++i)
		{
			if (pq[pq_size] == obj)
			{
				return true;
			}
		}
		return false;
	}
};

#endif /* PRIORITYQUEUE_H_ */