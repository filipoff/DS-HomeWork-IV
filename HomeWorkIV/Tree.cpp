#include "Tree.h"



Tree::Tree()
{
	root = new Tag("root");
}


Tree::Tree(String rootName)
{
	root = new Tag(rootName);
}

DynamicArray<String> Tree::getTagNamesFromPath(String path)
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
	tagNamesFromPath.removeAt(0);
	return tagNamesFromPath;
}

void Tree::addTagByElement(String path, String element)
{

	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));

	Tag* current = root;

	size_t size = tagNamesFromPath.getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (current->isChildFound(tagNamesFromPath.getAt(i)))
		{
			current = current->getChildByName(tagNamesFromPath.getAt(i));
		}
		else
		{
			Tag* newChild = NULL;
			if (i == size - 1)
			{
				newChild = new Tag(tagNamesFromPath.getAt(i), element);
			}
			else
				newChild = new Tag(tagNamesFromPath.getAt(i));

			if (current->hasChildren())
			{
				current->getLastChild()->setNextSibling(newChild);
			}
			current->addChild(newChild, NULL);
			current = newChild;
		}

	}
}



void Tree::addTagByAttribute(String path, String attributeName, String attributeValue)
{

	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));

	Tag* current = root;

	size_t size = tagNamesFromPath.getSize();

	for (size_t i = 0; i < size; i++)
	{
		if (current->isChildFound(tagNamesFromPath.getAt(i)))
		{
			current = current->getChildByName(tagNamesFromPath.getAt(i));
		}
		else
		{
			Tag* newChild = NULL;
			if (i == size - 1)
			{
				newChild = new Tag(tagNamesFromPath.getAt(i), attributeName, attributeValue);
			}
			else
				newChild = new Tag(tagNamesFromPath.getAt(i));

			if (current->hasChildren())
			{
				current->getLastChild()->setNextSibling(newChild);
			}
			current->addChild(newChild, NULL);
			current = newChild;
		}

	}

}

void Tree::print(ostream out) const
{
	Tag* current = root;
}