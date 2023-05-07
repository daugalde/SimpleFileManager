#pragma once
#include <iostream>
#include <string>
#include "Object.h"

using namespace std;

class DoublyNode {

private:
	Object* value;
	DoublyNode* NextNode;
	DoublyNode* PrevNode;


public:  // Constructors

	DoublyNode() {
		value = NULL;
		NextNode = NULL;
		PrevNode = NULL;
	}

	DoublyNode(Object* v)
	{
		value = v;
		NextNode = NULL;
		PrevNode = NULL;
	}

	DoublyNode(Object* v, DoublyNode* newNextNode)
	{
		value = v;
		NextNode = newNextNode;
	}

	friend class CircularDoublyList;
	friend class AppManager;
	friend class Object;
};

typedef DoublyNode* DoublyPointerNode; //Alias
