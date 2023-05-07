#include "TreeNode.h"
#include "BinaryTree.h"
#include <iomanip>
#include <iostream>
#include <fstream> 

using namespace std;

void BinaryTree::InOrderRoot(TreeNode* node) {
	if (node == NULL) {
		return;
	}
	else {
		InOrderRoot(node->GetLeft());
		cout << "\"" << node->GetElement()->getIndex() << "  " << node->GetElement()->getId() << "  " << "\"" << "\n";
		InOrderRoot(node->GetRight());
	}
}

void BinaryTree::PreOrderRoot(TreeNode* node) {
	if (node == NULL) {
		return;
	}
	else {
		cout << "\"" << node->GetElement()->getIndex() << "  " << node->GetElement()->getId() << "  " << "\"" << "\n";
		PreOrderRoot(node->GetLeft());
		PreOrderRoot(node->GetRight());
	}
}

void BinaryTree::PostOrderRoot(TreeNode* node) {
	if (node == NULL) {
		return;
	}
	else {
		PostOrderRoot(node->GetLeft());
		PostOrderRoot(node->GetRight());
		cout << "\"" << node->GetElement()->getIndex() << "  " << node->GetElement()->getId() << "  " << "\"" << "\n";
	}
}

void BinaryTree::InOrder() {
	this->InOrderRoot(this->GetRoot());
}

void BinaryTree::PreOrder() {
	this->PreOrderRoot(this->GetRoot());
}

void BinaryTree::PostOrder() {
	this->PostOrderRoot(this->GetRoot());
}

bool BinaryTree::InsertNode(Object* obj, TreePointerNode node) {
	bool result = false;

	if (obj->getId() < node->GetElement()->getId()) {
		if (node->GetLeft() == NULL) {
			node->SetLeft(new TreeNode(obj));
			result = true;
		}
		else {
			result = InsertNode(obj, node->GetLeft());
		}
	}
	else if (obj->getId() > node->GetElement()->getId()) {
		if (node->GetRight() == NULL) {
			node->SetRight(new TreeNode(obj));
			result = true;
		}
		else {
			result = InsertNode(obj, node->GetRight());
		}
	}
	return result;
}

bool BinaryTree::Insert(Object* obj) {
	if (IsEmpty()) {
		SetRoot(new TreeNode(obj));
		return true;
	}
	else {
		return this->InsertNode(obj, this->root);
	}
}

Object* BinaryTree::SearchById(int id, TreeNode* node) {
	Object* result = NULL;
	if (node != NULL) {
		if (id == node->GetElement()->getId()) {
			result = node->GetElement();
		}
		else {
			if (id < node->GetElement()->getId()) {
				result = SearchById(id, node->GetLeft());
			}
			else if (id > node->GetElement()->getId()) {
				result = SearchById(id, node->GetRight());
			}
		}
	}
	return result;
}

void BinaryTree::SearchByIndex(int index, TreeNode* node, CircularDoublyList& list) {

	if (node == NULL) {
		return;
	}
	else {
		SearchByIndex(index,node->GetLeft(), list);
		if (node->GetElement() != NULL && index == node->GetElement()->getIndex()) {
			list.Add(node->GetElement());
		}
		SearchByIndex(index,node->GetRight(),list);
	}
}

int BinaryTree::SmallestNode(TreeNode* node) {
	int result = -1;
	if (node != NULL)
	{
		result = node->GetElement()->getId();
		if (node->GetLeft() != NULL) {
			result = SmallestNode(node->GetLeft());
		}
	}
	return result;
}


int BinaryTree::SmallestNode() {
	return SmallestNode(this->GetRoot());
}

bool BinaryTree::DeleteSmallestNode(int id, TreeNode* node, TreeNode* ancestor, int side) {
	bool result = false;
	if (node != NULL)
	{
		if (node->GetLeft() != NULL) {
			result = DeleteSmallestNode(id, node->GetLeft(), node, 1);
		}
		else {
			result = DeleteSmallestNode(id, node, ancestor, side);
		}
	}
	return result;
}


bool BinaryTree::DeleteNodeRecursive(TreeNode* node, TreeNode* ancestor, int side) {
	bool result = false;
	if (node->GetLeft() == NULL) {
		if (side == 1) {
			ancestor->SetLeft(node->GetRight());
		}
		if (side == 2) {
			ancestor->SetRight(node->GetRight());
		}
		delete (node);
		node = NULL;
		result = true;
	}
	else {
		if (node->GetRight() == NULL) {
			if (side == 1) {
				ancestor->SetLeft(node->GetLeft());
			}
			if (side == 2) {
				ancestor->SetRight(node->GetLeft());
			}
			delete (node);
			node = NULL;
			result = true;
		}
		else {
			int val = SmallestNode(node->GetRight());
			node->GetElement()->setId(val);
			result = DeleteSmallestNode(val, node->GetRight(), node, 2);
		}
	}
	return result;
}

bool BinaryTree::DeleteNode(int id, TreeNode* node, TreeNode* ancestor, int side) {
	bool result = false;
	if (node != NULL) {


		if (node->GetElement()->getId() == id) {
			result = DeleteNodeRecursive(node, ancestor, side);
		}
		else {
			if (id < node->GetElement()->getId()) {
				result = DeleteNode(id, node->GetLeft(), node, 1);
			}
			else {
				result = DeleteNode(id, node->GetRight(), node, 2);
			}
		}
	}
	return result;
}

bool BinaryTree::Delete(int id) {
	return this->DeleteNode(id, this->GetRoot(), NULL, 0);
}