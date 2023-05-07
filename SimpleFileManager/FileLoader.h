#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "CircularDoublyList.h"
#include "BinaryTree.h"

using namespace std;

class FileLoader {

private:


public:
	FileLoader() { }

	~FileLoader();

	CircularDoublyList* LoadFiles();

	CircularDoublyList* ReadClientsFile();

	void ReadClientsByRangeFile(CircularDoublyList& newList);

	BinaryTree* BuilBST();

	void InsertNewClientInFile(int id, string name);

	void SoftDeleteInClientsFile(int id);

	void PurgeClientsFile();

	void OverrideClientFile();
};