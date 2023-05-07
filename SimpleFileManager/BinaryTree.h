#pragma once
#include <iostream>
#include <string>
#include "TreeNode.h"
#include <fstream> 
#include "CircularDoublyList.h"
#include "Object.h"

using namespace std;

class BinaryTree {

private:
	TreePointerNode root;
	bool InsertNode(Object* obj, TreePointerNode node);

	void InOrderRoot(TreeNode*);

	void PreOrderRoot(TreeNode*);

	void PostOrderRoot(TreeNode*);

	int SmallestNode(TreeNode* node);

	bool DeleteSmallestNode(int id, TreeNode* node, TreeNode* ancestor, int side);

	bool DeleteNodeRecursive(TreeNode* node, TreeNode* ancestor, int side);

	bool DeleteNode(int id, TreeNode* node, TreeNode* ancestor, int side);
public:

	BinaryTree() {
		this->root = NULL;
	}

	BinaryTree(Object* obj) {
		this->root = new TreeNode(obj);
	}

	void SetRoot(TreeNode* element) {
		this->root = element;
	}

	TreeNode* GetRoot() {
		return this->root;
	}

	bool IsEmpty() { return root == NULL; }

	bool Insert(Object*);

	Object* SearchById(int id, TreeNode* node);

	void SearchByIndex(int index, TreeNode* node, CircularDoublyList& list);

	void InOrder();

	void PreOrder();

	void PostOrder();

	int SmallestNode();

	bool Delete(int id);

	friend class CircularDoublyList;
};