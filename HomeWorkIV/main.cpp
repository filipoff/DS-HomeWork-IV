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
	test.addTagWithElement("newRoot/1/2/3","alphabet");
	test.addAttributeToTag("newRoot", "version", "1");
	test.setTagAttribute("newRoot", "version", "version", "2");
	return 0;
}