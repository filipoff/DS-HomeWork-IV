#include "Tree.h"



Tree::Tree()
{
	root = new Tag("root");
}


Tree::Tree(String rootName)
{
	root = new Tag(rootName);
}

DynamicArray<String> Tree::getTagNamesFromPath(String path) const
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
	return tagNamesFromPath;
}

bool Tree::isRootName(String nodeName) const
{
	if (root->getName() == nodeName)
		return true;
	return false;
}

void Tree::addTagWithElement(String path, String element)
{

	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));
	size_t size = tagNamesFromPath.getSize();

	if (!isRootName(tagNamesFromPath.getAt(0)))
	{
		cerr << "Error \"" << tagNamesFromPath.getAt(0) << "\" is not root" << endl;
		return;
	}

	if (size == 1)
	{
		cerr << "Error, cannot add another root!" << endl;
	}
	Tag* current = root;

	for (size_t i = 1; i < size; i++)
	{
		if (current->searchChildByName(tagNamesFromPath.getAt(i)))
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



void Tree::addTagWithAttribute(String path, String attributeName, String attributeValue)
{

	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));
	size_t size = tagNamesFromPath.getSize();

	if (!isRootName(tagNamesFromPath.getAt(0)))
	{
		cerr << "Error \"" << tagNamesFromPath.getAt(0) << "\" is not root" << endl;
		return;
	}

	if (size == 1)
	{
		cerr << "Error, cannot add another root!" << endl;
	}

	Tag* current = root;

	for (size_t i = 1; i < size; i++)
	{
		if (current->searchChildByName(tagNamesFromPath.getAt(i)))
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

void Tree::setTagElement(String path, String element)
{
	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));
	size_t size = tagNamesFromPath.getSize();

	if (!isRootName(tagNamesFromPath.getAt(0)))
	{
		cerr << "Error \"" << tagNamesFromPath.getAt(0) << "\" is not root" << endl;
		return;
	}

	if (size == 1)
	{
		cerr << "Error, cannot set element of root, it has no element!" << endl;
		return;
	}

	Tag* current = root;
	for (size_t i = 1; i < size; i++)
	{
		if (!current->searchChildByName(tagNamesFromPath.getAt(i)))
		{
			cerr << "Error, wrong path, tag to edit not found!" << endl;
			return;
		}

		current = current->getChildByName(tagNamesFromPath.getAt(i));

		if (i == size - 1)
		{
			current->setElement(element);
			return;
		}
	}
}

void Tree::setTagAttribute(String path,
	String oldName, String newName, String newValue)
{
	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));
	size_t size = tagNamesFromPath.getSize();

	if (!isRootName(tagNamesFromPath.getAt(0)))
	{
		cerr << "Error \"" << tagNamesFromPath.getAt(0) << "\" is not root" << endl;
		return;
	}

	if (size == 1)
	{
		Attribute& temp = root->findAtrributeByName(oldName);

		if (true)
		{
			temp.data.first = newName;
			temp.data.second = newValue;
			return;
		}
		else
		{
			cerr << "Error, root tag attribute to set not found!" << endl;
			return;
		}
	}

	Tag* current = root;
	for (size_t i = 1; i < size; i++)
	{
		if (!current->searchChildByName(tagNamesFromPath.getAt(i)))
		{
			cerr << "Error, wrong path, tag attribute to edit not found!" << endl;
			return;
		}

		current = current->getChildByName(tagNamesFromPath.getAt(i));

		if (i == size - 1)
		{
			Attribute& ptr = current->findAtrributeByName(oldName);
			if (true)
			{
				ptr.data.first = newName;
				ptr.data.second = newValue;
				return;
			}
			else
			{
				cerr << "Error, root tag attribute to edit not found!" << endl;
				return;
			}
		}
	}
}

void Tree::addAttributeToTag(String path, String attributeName, String attributeValue)
{
	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));
	size_t size = tagNamesFromPath.getSize();


	if (!isRootName(tagNamesFromPath.getAt(0)))
	{
		cerr << "Error \"" << tagNamesFromPath.getAt(0) << "\" is not root" << endl;
		return;
	}


	if (size == 1)
	{
		root->addAttribute(attributeName, attributeValue);
		return;
	}

	Tag* current = root;
	for (size_t i = 1; i < size; i++)
	{
		if (!current->searchChildByName(tagNamesFromPath.getAt(i)))
		{
			cerr << "Error, wrong path, tag not found!" << endl;
			return;
		}

		current = current->getChildByName(tagNamesFromPath.getAt(i));

		if (i == size - 1)
		{
			current->addAttribute(attributeName, attributeValue);
			return;
		}
	}
}

String Tree::getTagElement(String path) const
{
	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));
	size_t size = tagNamesFromPath.getSize();

	if (!isRootName(tagNamesFromPath.getAt(0)))
	{
		cerr << "Error \"" << tagNamesFromPath.getAt(0) << "\" is not root" << endl;
		throw "invalid root from getTagElement()";
	}

	if (size == 1)
	{
		cerr << "Error, cannot get element of root, it has no element!" << endl;
		throw "root has no elements from getTagElement()";
	}

	Tag* current = root;

	for (size_t i = 1; i < size; i++)
	{
		if (!current->searchChildByName(tagNamesFromPath.getAt(i)))
		{
			cerr << "Error, wrong path, tag element not found!" << endl;
			throw "tag element not found from getTagElement()";
		}

		current = current->getChildByName(tagNamesFromPath.getAt(i));

		if (i == size - 1)
		{
			return current->getElement();
		}
	}
	return current->getElement();
}

DynamicArray<Attribute> Tree::getTagAttributes(String path) const
{
	DynamicArray<String> tagNamesFromPath(getTagNamesFromPath(path));
	size_t size = tagNamesFromPath.getSize();

	if (!isRootName(tagNamesFromPath.getAt(0)))
	{
		cerr << "Error \"" << tagNamesFromPath.getAt(0) << "\" is not root" << endl;
		throw "invalid root from getTagAttributes()";
	}

	if (size == 1)
	{
		if (!root->getAttributes().getSize())
		{
			cerr << "There are no attributes for this tag!" << endl;
		}
		return root->getAttributes();
	}

	Tag* current = root;

	for (size_t i = 1; i < size; i++)
	{
		if (!current->searchChildByName(tagNamesFromPath.getAt(i)))
		{
			cerr << "Error, wrong path, tag not found! Cannot get attributes" << endl;
			throw "invalid path from getTagAttributes()";
		}

		current = current->getChildByName(tagNamesFromPath.getAt(i));

		if (i == size - 1)
		{
			if (!current->getAttributes().getSize())
			{
				cerr << "There are no attributes for this tag!" << endl;
			}
			return current->getAttributes();
		}
	}
	return current->getAttributes();
}

void Tree::print(ostream out) const
{
	Tag* current = root;
}