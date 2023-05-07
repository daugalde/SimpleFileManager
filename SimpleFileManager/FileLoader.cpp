#include <fstream>
#include <iostream>
#include <string>
#include "FileLoader.h"
#include "DoublyNode.h"
#include "CircularDoublyList.h"
#include "BinaryTree.h"

using namespace std;

FileLoader::~FileLoader()
{
	
}

CircularDoublyList* FileLoader::LoadFiles() {
	return ReadClientsFile();
}

CircularDoublyList* FileLoader::ReadClientsFile() {
    string str;
    ifstream file("Clientes.txt");
    CircularDoublyList* list = new CircularDoublyList();
    int index = 0;

    while (getline(file, str)) {
        if (str != "") {
            Object* client = new Object();
            string delim = ";";
            size_t pos = 0;
            string token;
            int count = 0;
            int idToken = -1;

            while ((pos = str.find(delim)) != string::npos || count <= 1) {
                token = str.substr(0, pos);

                if (count == 0) {
                    client->setId(stoi(token));
                    idToken = stoi(token);
                }
                else if (count == 1) {
                    client->setName(token);
                }

                str.erase(0, pos + delim.length());
                count++;
            }

            if (!list->ExistsElementId(idToken)) {
                index++;
                client->setIndex(index);
                list->Add(client);
            }
        }
    }
    list->GenerateIndexFile();
    
    ofstream output("Clientes.txt", ios::out | ios::trunc);
	    for (int i = 1; i <= list->Length(); i++) {
	        Object* client = list->GetElementByKeyIndex(i);
	        output << client->getId() << ";" << client->getName() << endl;
	    }
    output.close();

    return list;
}

BinaryTree* FileLoader::BuilBST() {

	string str;

	ifstream file("indices.txt");

	BinaryTree* bst = new BinaryTree();

	while (!file.eof()) {

		getline(file, str);

		if (str != "") {
			Object* client = new Object();

			string delim = ";";

			size_t pos = 0;

			string token;

			int count = 0;

			while (((pos = str.find(delim)) != string::npos) || count <= 1)
			{
				token = str.substr(0, pos);

				if (count == 0)
				{
					client->setIndex(stoi(token));
				}
				else if (count == 1)
				{
					  client->setId(stoi(token));
				}

				str.erase(0, pos + delim.length());

				count++;
			}

			bst->Insert(client);
		}
	}
	return bst;
}

void FileLoader::ReadClientsByRangeFile(CircularDoublyList& newList) {
	string str;

	ifstream file("Clientes.txt");

	while (!file.eof()) {

		getline(file, str);

		if (str != "") {

			string delim = ";";

			size_t pos = 0;

			string token;

			int count = 0;
			bool found = false;

			int idToken = -1;
			while (((pos = str.find(delim)) != string::npos) || count <= 1)
			{
				token = str.substr(0, pos);

				if (count == 0 && (newList.ExistsElementId(stoi(token))))
				{
					idToken = stoi(token);
					if (newList.ExistsElementId(stoi(token)))
					{
						found = true;
					}
				}
				else if (count == 1 && found)
				{
					newList.ExistsElementIdAndSetName(idToken, token);
				}

				str.erase(0, pos + delim.length());

				count++;
			}

		}
	}
	
}

void FileLoader::InsertNewClientInFile(int id, string name) {

	string str;

	ifstream file("Clientes.txt");

	CircularDoublyList* list = new CircularDoublyList();

	while (!file.eof()) {

		getline(file, str);

		if (str != "") {

			Object* obj = new Object();

			string delim = ";";

			size_t pos = 0;

			string token;

			int count = 0;
			while (((pos = str.find(delim)) != string::npos) || count <= 1)
			{
				token = str.substr(0, pos);

				if (count == 0)
				{
					obj->setId(stoi(token));
				}
				else if (count == 1) {
					obj->setName(token);
				}
				str.erase(0, pos + delim.length());

				count++;
			}

			if (obj->getId() == id)
			{
				obj->setName(obj->getId() + ";" + obj->getName() + ";1");
			}

			list->Add(obj);
		}
	}
	Object* objLatest = new Object();
	objLatest->setId(id);
	objLatest->setName(name);
	objLatest->setIndex(list->Length() + 1);
	list->Add(objLatest);
	list->OverwriteClientsFile();
	cout << "Archivo de Clientes Generado Correctamente" << "\n" << endl;
}

void FileLoader::SoftDeleteInClientsFile(int id) {
	string str;

	ifstream file("Clientes.txt");

	CircularDoublyList* list = new CircularDoublyList();

	while (!file.eof()) {

		getline(file, str);

		if (str != "") {

			Object* obj = new Object();

			string delim = ";";

			size_t pos = 0;

			string token;

			int count = 0;
			while (((pos = str.find(delim)) != string::npos) || count <= 1)
			{
				token = str.substr(0, pos);

				if (count == 0 )
				{
					obj->setId(stoi(token));
				}
				else if (count == 1) {
					obj->setName(token);
				}
				str.erase(0, pos + delim.length());

				count++;
			}

			if (obj->getId() == id)
			{
				obj->setName(obj->getName()+ ";1");
			}

			list->Add(obj);
		}
	}

	list->OverwriteClientsFile();
}

void FileLoader::PurgeClientsFile() {
	string str;

	ifstream file("Clientes.txt");

	CircularDoublyList* list = new CircularDoublyList();
	bool isDelete = false;
	while (!file.eof()) {

		getline(file, str);

		if (str != "") {

			Object* obj = new Object();

			string delim = ";";

			size_t pos = 0;

			string token;

			int count = 0;
			isDelete = false;
			while (((pos = str.find(delim)) != string::npos) || count <= 2)
			{
				token = str.substr(0, pos);

				if (count == 0)
				{
					obj->setId(stoi(token));
				}
				else if (count == 1) {
					obj->setName(token);
				}
				else if (count == 2 && token == "1") {
					isDelete = true;
				}

				str.erase(0, pos + delim.length());

				count++;
			}

			if (!isDelete)
			{
				list->Add(obj);
				isDelete = false;
			}

		}
	}

	list->GenerateTemp();
}

void FileLoader::OverrideClientFile() {
	string str;

	ifstream file("ClientesTemp.txt");

	CircularDoublyList* list = new CircularDoublyList();
	while (!file.eof()) {

		getline(file, str);

		if (str != "") {

			Object* obj = new Object();

			string delim = ";";

			size_t pos = 0;

			string token;

			int count = 0;
			while (((pos = str.find(delim)) != string::npos) || count <= 1)
			{
				token = str.substr(0, pos);

				if (count == 0)
				{
					obj->setId(stoi(token));
				}
				else if (count == 1) {
					obj->setName(token);
				}

				str.erase(0, pos + delim.length());

				count++;
			}

			list->Add(obj);
		}
	}

	list->OverwriteClientsFile();
}
