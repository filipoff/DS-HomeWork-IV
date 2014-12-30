#include <iostream>
#include "Tag.h"
#include "Tree.h"
#include "String.h"
#include "DynamicArray.h"
#include "List.h"
using namespace std;



int main()
{
	Tree test("newRoot");
	test.addTagWithElement("root/1/2/3","alphabet");
	test.addAttributeToTag("root/1", "version", "1");
	return 0;
}