#include <conio.h>
#include <stdio.h>
#include "RBTree.h"

int main()
{
	struct RbNode *rootNode = NULL;
	rootNode = RbTreeAdd(rootNode, 10, "10");
	rootNode = RbTreeAdd(rootNode, 5, "5");
	rootNode = RbTreeAdd(rootNode, 3, "3");
	rootNode = RbTreeAdd(rootNode, 11, "11");
	rootNode = RbTreeAdd(rootNode, 12, "12");
	rootNode = RbTreeAdd(rootNode, 6, "6");
	rootNode = RbTreeAdd(rootNode, 8, "8");
	rootNode = RbTreeAdd(rootNode, 9, "9");

	RbTreePrint(rootNode, 1);
	printf("\n\n");

	struct RbNode *x = RbTreeLookup(rootNode, 5);
	struct RbNode *y = RbTreeLookup(rootNode, 12);
	RbTreeTransplant(rootNode, x, y);

	RbTreePrint(rootNode, 1);
	RbTreeFree(rootNode);

	_getch();
	return 0;
}