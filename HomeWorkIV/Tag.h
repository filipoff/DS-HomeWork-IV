#pragma once
#include "Utils.h"
#include "List.h"
#include "String.h"
#include "DynamicArray.h"
#include "Pair.h"

class Tag
{
private:

	String name;
	String element;
	DynamicArray<Pair<String, String>> attributes;
	Tag* nextSibling;
	List<Tag*> children;

private:


	void copyFrom(const Tag& other)
	{
		delete nextSibling;
		this->nextSibling = other.nextSibling ? new Tag(*other.nextSibling) : NULL;
		this->name = other.name;
		this->element = other.element;
		this->attributes = other.attributes;
		this->children = other.children;
	}

public:

	Tag() : name(), element(), attributes(), nextSibling(NULL), children() {}

	Tag(const Tag &other)
	{
		copyFrom(other);
	}

	Tag(String name)
	{
		this->nextSibling = NULL;
		this->name = name;

	}

	Tag(String name, String element)
	{
		this->nextSibling = NULL;
		this->name = name;
		this->element = element;
	}

	Tag& operator=(const Tag& other)
	{
		if (this != &other)
		{
			copyFrom(other);
		}
		return *this;
	}
	~Tag()
	{
		if (nextSibling)
			delete nextSibling;
	}

	bool hasChildren() const
	{
		return !children.isEmpty();
	}

	String getName() const
	{
		return name;
	}

	String getValue() const
	{
		return element;
	}

	Tag* getNextSibling() const
	{
		return nextSibling;
	}

	void  setNextSibling(Tag* nextSibling)
	{
		this->nextSibling = nextSibling;
	}

	void addChild(Tag* child, Tag* nextSibling)
	{
		if (nextSibling)
		{
			child->setNextSibling(nextSibling);
		}
		children.pushBack(child);
	}

	Tag* getLastChild() const
	{
		if (children.isEmpty())
			return NULL;
		return children.getAt(children.getSize() - 1);
	}

	bool isChildFound(String childName)
	{
		for (size_t i = 0; i < children.getSize(); i++)
		{
			if (children.getAt(i)->getName() == childName)
				return true;
		}
		return false;
	}

	Tag* getChildByName(String childName)
	{

		for (size_t i = 0; i < children.getSize(); i++)
		{
			if (children.getAt(i)->getName() == childName)
				return  children.getAt(i);
		}
			return NULL;
	}
};
