#include "RBTree.h"
#include <stdio.h>

struct RbNode *RbTreeFixUp_Add(struct RbNode *root, struct RbNode *node);
//struct RbNode *RbTreeFixUp_Delete(struct RbNode *root, struct RbNode *node);

struct RbNode *RbTreeRotateLeft(struct RbNode *root, struct RbNode *node);
struct RbNode *RbTreeRotateRight(struct RbNode *root, struct RbNode *node);

struct RbNode EmptyNode = { 0, 0, Black, NULL, NULL, NULL };
struct RbNode *EmptyNodePtr = &EmptyNode;

struct RbNode *RbTreeLookup(struct RbNode *root, int key)
{
	while (root != NULL)
	{
		if (key == root->key)
			return root;
		else if (key < root->key)
			root = root->left;
		else
			root = root->right;
	}

	return root;
}

struct RbNode *RbTreeMin(struct RbNode *root)
{
	while (root->left->left != NULL)
		root = root->left;

	return root;
}

struct RbNode *RbTreeMax(struct RbNode *root)
{
	while (root->right->right != NULL)
		root = root->right;

	return root;
}

void RbTreeFree(struct RbNode *root)
{
	if (root->key == 0)
		return;

	RbTreeFree(root->left);
	RbTreeFree(root->right);

	free(root);
}

void RbTreePrint(struct RbNode *root, int level)
{
	int i;
	if (root == NULL || root == EmptyNodePtr)
		return;

	for (i = 0; i < level; i++)
	{
		printf("\t");
	}

	printf("%d", root->key);

	if (root->color == Black)
		printf("%c\n", 'B');
	else
		printf("%c\n", 'R');

	RbTreePrint(root->right, level + 1);
	RbTreePrint(root->left, level + 1);
}

struct RbNode *RbTreeAdd(struct RbNode *root, int key, char *value)
{
	struct RbNode *node;
	struct RbNode *parent = EmptyNodePtr;

	for (node = root; node != EmptyNodePtr && node != NULL;)
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else if (key > node->key)
			node = node->right;
		else
			return root;
	}

	node = (struct RbNode*)malloc(sizeof(*node));
	if (node == NULL)
		return NULL;

	node->key = key;
	node->value = value;

	node->color = Red;
	node->parent = parent;
	node->left = EmptyNodePtr;
	node->right = EmptyNodePtr;

	if (parent != EmptyNodePtr)
	{
		if (key < parent->key)
			parent->left = node;
		else
			parent->right = node;
	}
	else
		root = node;

	return RbTreeFixUp_Add(root, node);
}

struct RbNode *RbTreeDelete(struct RbNode *root, int key)
{
	return NULL;
}

struct RbNode *RbTreeFixUp_Add(struct RbNode *root, struct RbNode *node)
{
	struct RbNode *uncle;

	// Текущий узел красный
	while ((node != root) && (node->parent->color == Red))
	{
		// Рассматриваем первые три случая, когда узел находится слева 
		// относительно родителя родителя узла
		if (node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;

			// 1 случай - uncle is Red
			if (uncle->color == Red)
			{
				uncle->color = Black;
				node->parent->color = Black;
				node->parent->parent->color = Red;

				node = node->parent->parent;
			}
			else
			{
				// Случай 2 и 3 - uncle is Black
				if (node == node->parent->right)
				{
					// Перевод случая 2 в 3
					node = node->parent;
					root = RbTreeRotateLeft(root, node);
				}

				// Случай 3
				node->parent->color = Black;
				node->parent->parent->color = Red;

				root = RbTreeRotateRight(root, node->parent->parent);
			}
		}
		else
		{
			// Случаи 4, 5 и 6 симметричны первым трём
			uncle = node->parent->parent->left;
			
			// 4 случай - uncle is Red
			if (uncle->color == Red)
			{
				uncle->color = Black;
				node->parent->color = Black;				
				node->parent->parent->color = Red;

				node = node->parent->parent;
			}
			else
			{
				// Случай 5 и 6
				if (node == node->parent->left)
				{
					// Перевеод в случай 6
					node = node->parent;
					root = RbTreeRotateRight(root, node);
				}

				// Случай 6
				node->parent->color = Black;
				node->parent->parent->color = Red;

				root = RbTreeRotateLeft(root, node->parent->parent);
			}
		}
	}

	root->color = Black;
	return root;
}

struct RbNode *RbTreeRotateLeft(struct RbNode *root, struct RbNode *node)
{
	struct RbNode *right = node->right;
	node->right = right->left;

	if (right->left != EmptyNodePtr)
		right->left->parent = node;

	if (right != EmptyNodePtr)
		right->parent = node->parent;

	if (node->parent != EmptyNodePtr)
	{
		if (node == node->parent->left)
			node->parent->left = right;
		else
			node->parent->right = right;
	}
	else
		root = right;

	right->left = node;
	if (node != EmptyNodePtr)
		node->parent = right;

	return root;
}

struct RbNode *RbTreeRotateRight(struct RbNode *root, struct RbNode *node)
{
	struct RbNode *left = node->left;
	node->left = left->right;

	if (left->right != EmptyNodePtr)
		left->right->parent = node;

	if (left != EmptyNodePtr)
		left->parent = node->parent;

	if (node->parent != EmptyNodePtr)
	{
		if (node == node->parent->right)
			node->parent->right = left;
		else
			node->parent->left = left;
	}
	else
		root = left;

	left->right = node;
	if (node != EmptyNodePtr)
		node->parent = left;

	return root;
}

void RbTreeTransplant(struct RbNode *root, struct RbNode *first, struct RbNode *second)
{
	struct RbNode *temp = EmptyNodePtr;

	if (first->parent == EmptyNodePtr)
		root = second;
	else if (first == first->parent->left)
		first->parent->left = second;
	else
		first->parent->right = second;

	if (second->parent == EmptyNodePtr)
		root = first;
	else if (second == second->parent->left)
		second->parent->left = first;
	else
		second->parent->right = first;

	temp->parent = first->parent;
	first->parent = second->parent;
	second->parent = temp->parent;

	first->left->parent = second->left->parent;
	first->right->parent = second->right->parent;
	second->left->parent = first->left->parent;
	second->right->parent = first->right->parent;

	temp->left = first->left;
	temp->right = first->right;
	first->left = second->left;
	first->right = second->right;
	second->left = temp->left;
	second->right = temp->right;
}
