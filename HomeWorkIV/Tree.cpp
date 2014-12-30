#include "Tree.h"



Tree::Tree()
{
	root = new Tag("root");
}


Tree::Tree(String rootName)
{
	root = new Tag(rootName);
}



void Tree::addTag(String path, String element)
{

	DynamicArray<String> tagNamesFromPath;
	String next;
	size_t len = path.getLength();
	for (size_t i = 0; i <= len; i++)
	{
		if (path[i] == '/' || path[i] == '\0')
		{
			tagNamesFromPath.push(next);
			next.clear();
		}
		else next += path[i];
	}

	Tag* current = root;

	for (size_t i = 1; i < tagNamesFromPath.getSize(); i++)
	{
		if (current->isChildFound(tagNamesFromPath.getAt(i)))
		{
			current = current->getChildByName(tagNamesFromPath.getAt(i));
		}
		else
		{
			Tag* newChild = new Tag(current->getName(), current->getValue());
			if (current->hasChildren())
			{
				current->getLastChild()->setNextSibling(newChild);
			}
			current->addChild(newChild, NULL);
		}

	}
}
