#pragma once
#include <stdlib.h>

typedef enum  
{
	Black,
	Red
} RbNodeColor;

struct RbNode
{
	int key;
	char *value;
	RbNodeColor color;

	struct RbNode *parent;
	struct RbNode *left;
	struct RbNode *right;
};

struct RbNode *RbTreeAdd(struct RbNode *root, int key, char *value);
struct RbNode *RbTreeDelete(struct RbNode *root, int key);
struct RbNode *RbTreeLookup(struct RbNode *root, int key);
struct RbNode *RbTreeMin(struct RbNode *root);
struct RbNode *RbTreeMax(struct RbNode *root);

void RbTreeTransplant(struct RbNode *root, struct RbNode *first, struct RbNode *second);

void RbTreeFree(struct RbNode *root);
void RbTreePrint(struct RbNode *root, int level);