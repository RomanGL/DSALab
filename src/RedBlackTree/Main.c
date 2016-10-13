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

	rootNode = RbTreeDelete(rootNode, 8);
	RbTreePrint(rootNode, 1);
	printf("\n\n\n");

	struct RbNode *min = RbTreeMin(rootNode);
	printf("Min: %d\n", min->key);

	struct RbNode *max = RbTreeMax(rootNode);
	printf("Max: %d\n\n", max->key);

	struct RbNode *finded = RbTreeLookup(rootNode, 11);
	printf("Finded 11: %d\n", finded->key);

	finded = RbTreeLookup(rootNode, 25);
	printf("Finded 25: %d\n", finded == NULL ? -1 : finded->key);

	_getch();
	return 0;
}