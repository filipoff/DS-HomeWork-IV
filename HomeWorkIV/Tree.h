#pragma once
#include "Utils.h"
#include "Tag.h"


class Tree
{
private:
	Tag* root;
public:
	Tree();
	Tree(String element);
	~Tree() { delete root; }
	void addTag(String path, String element);
};
