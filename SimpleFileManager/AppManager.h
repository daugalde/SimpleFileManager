#pragma once
#include <iostream>
#include <string>
#include "FileLoader.h"
#include "CircularDoublyList.h"
#include "BinaryTree.h"
using namespace std;

class AppManager {

private:
	BinaryTree* bst;
	CircularDoublyList* list;
	int clientTotalRecord = 0;

public:  // Constructors

	AppManager() {
		bst = new BinaryTree();
		list = new CircularDoublyList();
	}

	BinaryTree* getBst() {
		return bst;
	}

	void setBst(BinaryTree* bst) {
		this->bst = bst;
	}

	CircularDoublyList* getList() {
		return list;
	}

	void setList(CircularDoublyList* list) {
		this->list = list;
	}

	int getClientTotalRecords() {
		return clientTotalRecord;
	}

	void setClientTotalRecords(int totalRecords) {
		this->clientTotalRecord = totalRecords;
	}

	void InitTreeLoad();

	void BuildBST();

	void SearchClient();

	void InsertClient();

	void DeleteClient();

	void PurgeClient();

	void ReIndex();
};