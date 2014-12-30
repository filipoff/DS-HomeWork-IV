#pragma once
#include "Utils.h"

template <class T>

struct BaseNode
{
	T data;
	BaseNode <T> *next;

	BaseNode(const BaseNode <T> &other)
	{
		next = other.next ? new BaseNode(*other.next) : NULL;
		data = other.data;
	}

	BaseNode(const T &data)
	{
		this->next = NULL;
		this->data = data;
	}
	BaseNode(const T &data, BaseNode <T> *next)
	{
		this->next = next;
		this->data = data;
	}

	~BaseNode()
	{
		if (next)
		{
			delete next;
		}
	}
};

template <class T>

class List
{
private:


	BaseNode <T> *last, *first;
	size_t size;


private:

	BaseNode <T>* get_at(size_t index) const
	{
		if (index >= size)
		{
			throw "Invalid index";
		}

		BaseNode <T> *toGet = first;

		while (index > 0)
		{
			index--;
			toGet = toGet->next;
		}
		return toGet;
	}


	void clear()
	{
		delete first;
		first = last = NULL;
	}

	void copyFrom(const List<T>& other)
	{
		if (other.isEmpty())
		{
			first = last = NULL;
			size = 0;
		}
		else
		{
			clear();
			first = new BaseNode <T>(*other.first);
			size = other.size;
			for (last = first; last->next; last = last->next) {}
		}
	}

	T removeFirst()
	{
		if (isEmpty())
		{
			throw "Error, List is empty!";
		}
		T data = first->data;
		BaseNode <T> *oldNode = first;
		first = first->next;
		size--;
//		oldNode->next = NULL;
		delete oldNode;
		if (!size)
		{
			last = NULL;
		}
		return data;
	}

	T removeLast()
	{
		if (isEmpty())
		{
			throw "Error, List is empty!";
		}
		if (size == 1)
		{
			return removeFirst();
		}

		BaseNode <T> *beforeLast = get_at(size - 2);
		T data = beforeLast->next->data;
		size--;
		last = beforeLast;
		delete beforeLast->next;
		beforeLast->next = NULL;
		return data;
	}

public:
	bool isEmpty() const
	{
		return size == 0;
	}

	size_t getSize() const
	{
		return size;
	}

	List()
	{
		first = last = NULL;
		size = 0;
	}

	List(const T &node)
	{
		first = last = new BaseNode <T>(node);
		size = 1;
	}

	List(const List <T> &other)
	{
		copyFrom(other);
	}

	~List()
	{
		delete first;
	}

	List <T>& operator=(const List <T> &other)
	{
		if (this != &other)
		{
			copyFrom(other);
		}
		return *this;
	}

	void  pushFront(const T &elem)
	{
		first = new BaseNode <T>(elem, first);
		if (!size)
		{
			last = first;
		}
		size++;
	}

	void pushBack(const T &elem)
	{
		if (isEmpty())
		{
			first = last = new BaseNode <T>(elem);
		}
		else
		{
			last = last->next = new BaseNode <T>(elem);
		}
		size++;
	}

	T popFront()
	{
		if (isEmpty())
		{
			throw "Error, List is empty!";
		}
		T data = first->data;
		BaseNode <T> *oldNode = first;
		first = first->next;
		size--;
		oldNode->next = NULL;
		delete oldNode;
		if (!size)
		{
			last = NULL;
		}
		return data;
	}

	T popBack()
	{
		if (isEmpty())
		{
			throw "Error, List is empty!";
		}
		if (size == 1)
		{
			return removeFirst();
		}

		BaseNode <T> *beforeLast = get_at(size - 2);
		T data = beforeLast->next->data;
		size--;
		last = beforeLast;
		delete beforeLast->next;
		beforeLast->next = NULL;
		return data;
	}

	T removeAt(size_t index)
	{

		if (isEmpty())
		{
			throw "List is empty! Cannot remove at index";
		}

		if (index >= size)
		{
			throw "Invalid index!";
		}

		if (index == 0)
		{
			return removeFirst();
		}

		if (index == size - 1)
		{
			return removeLast();
		}

		BaseNode <T> *PreviousNode = getAt(index - 1);
		T data = PreviousNode->next->data;
		BaseNode <T> *toRemove = PreviousNode->next;
		PreviousNode->next = toRemove->next;
		toRemove->next = NULL;
		delete toRemove;
		toRemove = NULL;
		size--;
		return data;
	}

	void insertAt(size_t index, const T& elem)
	{
		if (isEmpty() && index != 0)
		{
			throw "List is empty! Cannot remove at index";
		}
		if (index >= size)
		{
			throw "invalid index!";
		}
		else if (index == 0)
		{
			pushFront(elem);
		}
		else if (index == size)
		{
			pushBack(elem);
		}
		else
		{
			BaseNode <T> *previousNode = getAt(index - 1);
			BaseNode <T> *toAdd = new BaseNode <T>(elem);
			toAdd->next = previousNode->next;
			previousNode->next = toAdd;
			size++;
		}
	}

	void setAt(size_t index, T elem)
	{
		if (isEmpty() && index != 0)
		{
			throw "List is empty! Cannot set at index";
		}
		if (index >= size)
		{
			throw "Invalid Index!";
		}
		get_at(index)->data = elem;
	}

	T getAt(size_t index) const
	{
		if (isEmpty())
		{
			throw "List is empty! Cannot get at index";
		}

		if (index >= size)
		{
			throw "Invalid Index!";
		}
		return get_at(index)->data;
	}
};