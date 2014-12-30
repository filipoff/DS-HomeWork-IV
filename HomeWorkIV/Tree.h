#pragma once
#include "Utils.h"
#include "Tag.h"


class Tree
{
private:
	Tag* root;

private:
	DynamicArray<String> getTagNamesFromPath(String path) const;
	bool isRootName(String nodeName) const;
public:
	Tree();
	Tree(String rootName);
	~Tree() { delete root; } //?
	void print(ostream out) const;
	void addTagWithElement(String path, String element);
	void addTagWithAttribute(String path, String attributeName, String atributeValue);
	void addAttributeToTag(String path, String attributeName, String attributeValue);
	String getTagElement(String path) const;
	DynamicArray<Attribute> getTagAttributes(String path) const;
	void setTagElement(String path, String element);
	void setTagAttribute(String path, String oldName, String newName, String newValue);
};
