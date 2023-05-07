#pragma once
#include <iostream>
#include <fstream>
#include "DoublyNode.h"

using namespace std;

class CircularDoublyList {

private:
	DoublyPointerNode head;

public:
	CircularDoublyList() {
		this->head = NULL;
	}

	~CircularDoublyList() {
		this->head = NULL;
	};
	bool IsEmpty() { return head == NULL; }
	void Add(Object* obj); // Insert at End
	int GetElementIndexById(int id);
	Object* GetElementByKeyId(int id);
	Object* GetElementByKeyIndex(int i);
	void SetElementValueById(int id, string name);
	void RemoveElement();
	void RemoveElementAtIndex(int index);
	void DisplayString();
	void DisplayElementById(int id);
	int Length();
	bool ExistsElementId(int id);
	void GenerateIndexFile();
	bool ExistsElementIdAndSetName(int id, string name);
	bool RemoveAtIndex(int pos);
	bool RemoveRear();
	bool RemoveFront();
	DoublyPointerNode GetPosition(int index);
	void GenerateTemp();
	void OverwriteClientsFile();

	friend class AppManager;
};
