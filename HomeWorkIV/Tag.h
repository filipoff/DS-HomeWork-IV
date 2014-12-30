#pragma once
#include "Utils.h"
#include "List.h"
#include "String.h"
#include "DynamicArray.h"
#include "Attribute.h"

class Tag
{
private:

	String name;
	String element;
	DynamicArray<Attribute> attributes;
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

	Tag(const Tag& other)
	{
		copyFrom(other);
	}

	Tag(String name) : name(name), nextSibling(NULL), element(), attributes(), children() {}

	Tag(String name, String element) : name(name), nextSibling(NULL), element(element),
		attributes(), children() {}

	Tag(String name, String attributeName, String attributeValue) : name(name),
		nextSibling(NULL), element(), children()
	{
		Attribute temp(attributeName, attributeValue);
		attributes.push(temp);
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

	Attribute& findAtrributeByName(String name)
	{
		Attribute temp;
		size_t size = attributes.getSize();
		for (size_t i = 0; i < size; i++)
		{
			if (attributes.getAt(i).data.first == name)
			{
				return attributes.getAt(i);
			}
		}
	}

	DynamicArray<Attribute> getAttributes() const
	{
		return attributes;
	}

	String getElement() const
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

	void setName(String newName)
	{
		name = newName;
	}

	void setElement(String newElement)
	{
		element = newElement;
	}

	void setAttribute(Attribute attribute, String newName, String newValue)
	{
		attribute.data.first = newName;
		attribute.data.second = newValue;
	}

	void addAttribute(String name, String value)
	{
		Attribute temp(name, value);
		attributes.push(temp);
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
		if (!hasChildren())
			return NULL;
		return children.getAt(children.getSize() - 1);
	}

	bool searchChildByName(String childName)
	{
		for (size_t i = 0; i < children.getSize(); i++)
		{
			if (children.getAt(i)->getName() == childName)
				return true;
		}
		return false;
	}

	bool hasAttributes() const
	{
		return  !attributes.isEmpty();
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
