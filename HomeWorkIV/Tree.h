#pragma once
#include "Utils.h"
#include "Tag.h"


class Tree
{
private:
	Tag* root;

private:
	DynamicArray<String> getTagNamesFromPath(String path);
public:
	Tree();
	Tree(String rootName);
	~Tree() { delete root; } //?
	void print(ostream out) const;
	void addTagByElement(String path, String element);
	void addTagByAttribute(String path, String attributeName, String atributeValue);
};
