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
	test.addTagByElement("root/abc","alphabet");
	test.addTagByElement("root/ocb", "haha");
	test.addTagByAttribute("root/abc/asd", "lang", "en");
	return 0;
}