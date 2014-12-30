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

	if (size == 1)
	{
		throw "Error, cannot add another root!";
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

	if (size == 1)
	{
		throw "Error, cannot add another root!";
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

	if (size == 1)
	{
		throw "Error, cannot set element of root, it has no element!";
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

	if (size == 1)
	{
		if (!isRootName(path))
		{
			cerr << "Error" << path <<"is not root" << endl;
			return;
		}
		Attribute* temp = root->findAtrributeByName(oldName);
		if (temp)
		{
			temp->data.first = newName;
			temp->data.second = newValue;
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
			Attribute* temp = current->findAtrributeByName(oldName);
			if (temp)
			{
				temp->data.first = newName;
				temp->data.second = newValue;
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

	if (size == 1)
	{
		if (!isRootName(path))
		{
			cerr << "Error" << path << "is not root" << endl;
			return;
		}

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

	if (size == 1)
	{
		if (!isRootName(path))
		{
			cerr << "Error" << path << "is not root" << endl;
		}
		throw "Error, cannot get element of root, it has no element!";
	}

	Tag* current = root;

	for (size_t i = 1; i < size; i++)
	{
		if (!current->searchChildByName(tagNamesFromPath.getAt(i)))
		{
			throw "Error, wrong path, tag element not found!";
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

	if (size == 1)
	{
		if (!isRootName(path))
		{
			cerr << "Error" << path << "is not root" << endl;
			throw;
		}
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
			throw "Error, wrong path, tag not found! Cannot get attributes";
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