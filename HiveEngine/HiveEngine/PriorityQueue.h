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
#define NULL 0



template <class T>
class PriorityQueue {
private:
	T* pq;
	int pqSize;
	int mode;

	void balance(int index)
	{
		if (mode == ASCENDING)
		{
			ascendingBalance(index);
		}
		else
		{
			descendingBalance(index);
		}
	}

	void ascendingBalance(int index)
	{
		int i = index + 1;
		int leftIndex = i * 2 - 1;
		int rightIndex = i * 2;
		int smallest = index;
		if (leftIndex <= pqSize - 1 && pq[leftIndex] < pq[index])
		{
			smallest = leftIndex;
		}
		if (rightIndex <= pqSize - 1 && pq[rightIndex] < pq[smallest])
		{
			smallest = rightIndex;
		}
		if (smallest != index)
		{
			T c = pq[index];
			pq[index] = pq[smallest];
			pq[smallest] = c;
			balance(smallest);
		}
	}

	void descendingBalance(int index)
	{
		int i = index + 1;
		int leftIndex = i * 2 - 1;
		int rightIndex = i * 2;
		int largest = index;
		if (leftIndex <= pqSize - 1 && pq[leftIndex] > pq[index])
		{
			largest = leftIndex;
		}
		if (rightIndex <= pqSize - 1 && pq[rightIndex] > pq[largest])
		{
			largest = rightIndex;
		}
		if (largest != index)
		{
			T c = pq[index];
			pq[index] = pq[largest];
			pq[largest] = c;
			balance(largest);
		}
	}

	void decreaseKey(T &c, int index)
	{
		if (mode == ASCENDING)
		{
			ascendingDecreaseKey(c, index);
		}
		else
		{
			descendingDecreaseKey(c, index);
		}
	}

	void ascendingDecreaseKey(T &c, int index)
	{
		int i = index + 1;
		int parentIndex = (i / 2) - 1;
		while (i - 1 > 0 && pq[parentIndex] > pq[i - 1])
		{
			pq[i - 1] = pq[parentIndex];
			pq[parentIndex] = c;
			i = parentIndex + 1;
			parentIndex = (i / 2) - 1;
		}
	}

	void descendingDecreaseKey(T &c, int index)
	{
		int i = index + 1;
		int parentIndex = (i / 2) - 1;
		while (i - 1 > 0 && pq[parentIndex] < pq[i - 1])
		{
			pq[i - 1] = pq[parentIndex];
			pq[parentIndex] = c;
			i = parentIndex + 1;
			parentIndex = (i / 2) - 1;
		}
	}

public:
	//smaller values are at head of queue
	static const int ASCENDING = 0;
	//larger values are at head of queue
	static const int DESCENDING = 1;

	PriorityQueue() {
		pq = nullptr;
		pqSize = 0;
		mode = ASCENDING;
	}

	PriorityQueue(int size) {
		pq = new T[size];
		pqSize = 0;
		mode = ASCENDING;
	}

	~PriorityQueue() {
	}

	void insert(T& c)
	{
		++pqSize;
		pq[pqSize - 1] = c;
		decreaseKey(c, pqSize - 1);
	}

	T deleteMin()
	{
		T min = pq[0];
		pq[0] = pq[pqSize - 1];
		--pqSize;
		balance(0);
		return min;
	}

	int size()
	{
		return pqSize;
	}

	T getIndex(int index)
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

	void deleteObject(T c)
	{
		T toDelete = pq[0];
		int i = 0;
		while (toDelete != c)
		{
			++i;
			if (i >= pqSize)
			{
				return;
			}
			toDelete = pq[i];
		}

		pq[i] = pq[pqSize - 1];
		--pqSize;
		balance(i);
	}

	void setMode(int newMode)
	{
		mode = newMode;
	}

	bool contains(T obj)
	{
		for (int i = 0; i < pqSize; ++i)
		{
			if (pq[pqSize] == obj)
			{
				return true;
			}
		}
		return false;
	}
};

#endif /* PRIORITYQUEUE_H_ */