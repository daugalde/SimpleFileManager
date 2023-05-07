#include <iostream>
#include <iomanip>
#include "AppManager.h"
#include "Menu.h"

using namespace std;

void AppManager::InitTreeLoad()
{
	FileLoader loader;

	this->setClientTotalRecords(loader.LoadFiles()->Length());
}

void AppManager::BuildBST() {
	FileLoader loader;

	this->setBst(loader.BuilBST());

	Menu::ClearMenu;
	cout << "\n Arbol En Preorden \n";

	this->getBst()->PreOrder();
	cout <<endl;

	if (this->getList()->IsEmpty())
	{
		cout << "\n Memoria Cache vacia\n ";
	}
}

void AppManager::SearchClient() {
	FileLoader loader;
	string clientId = "";

	cout << "Buscar Cliente \nDigite Primero un cliente Id \n";
	getline(cin, clientId);
	if (Menu::Is_number(clientId))
	{
		Menu::ClearMenu();
		Object* obj = this->getBst()->SearchById(stoi(clientId),this->getBst()->GetRoot());
		int index = 1;
		int range = 1;
		int idx = this->getList()->GetElementIndexById(stoi(clientId));
		if ((obj != NULL && !this->getList()->IsEmpty() && idx == -1))
		{
			this->setList(new CircularDoublyList());
		}
		if (obj != NULL && this->getList()->IsEmpty() )
		{
			Menu::ClearMenu();
			cout << "Buscar Cliente \n\nLa Cedula  " << clientId << "  Se esta Buscando en Disco \n \n";
			index = obj->getIndex();
			range = index + 19;
			FileLoader loader;
			do {
				while (index <= range ) {
					if (index <= this->getClientTotalRecords())
					{
						this->getBst()->SearchByIndex(index, this->getBst()->GetRoot(), *(this->getList()));
						
					}
					index++;
				}

				if (this->getList()->Length() != 20)
				{
					index = 1;

					range = 20 - this->getList()->Length();
				}
			
			} while (this->getList()->Length() != 20);
			
			//Find them in File
			loader.ReadClientsByRangeFile(*(this->getList()));

		}
		else 
		{
			Menu::ClearMenu();
			cout << "Buscar Cliente \n\nLa Cedula  " << clientId << "  esta Presente en la memoria cache por tanto se muestra a continuacion \n";
		}
		
		
		cout << "\n Memoria Cache \n";
		this->getList()->DisplayString();

		cout << "Pre Orden de Arbol\n \n";
		this->getBst()->PreOrder();
		cout << endl;
		
	}
	else {
		cout << "El Id proveido NO es valido o no Existe\n \n";
	}
	cout << "Presione Enter para Volver al Menu Anterior \n";
}

void AppManager::InsertClient() {
	string clientId = "";
	FileLoader loader;
	cout << "Insertar Cliente \nDigite Primero un cliente Id \n";
	getline(cin, clientId);
	if (Menu::Is_number(clientId))
	{
		Menu::ClearMenu();
		string name = "";
		cout << "Digite Nombre Nuevo cliente \n";
		getline(cin, name);
		FileLoader loader;
		loader.InsertNewClientInFile(stoi(clientId),name);
		this->setClientTotalRecords(loader.LoadFiles()->Length());
		this->setBst(loader.BuilBST());
		//Actualizar Cache

		int index = this->getClientTotalRecords() - 19;
		int range = this->getClientTotalRecords();
		
		do {
			while (index <= range) {
				if (index <= this->getClientTotalRecords())
				{
					this->getBst()->SearchByIndex(index, this->getBst()->GetRoot(), *(this->getList()));
				}

				index++;
			}

			if (this->getList()->Length() != 20)
			{
				index = 1;

				range = 20 - this->getList()->Length();
			}

		} while (this->getList()->Length() != 20);

		//Find them in File
		loader.ReadClientsByRangeFile(*(this->getList()));
		//cout << "Cliente Insertado Correctamente en Disco\n \n";
		cout << "Pre Orden de Arbol\n \n";
		this->getBst()->PreOrder();
		
		cout <<endl;
		cout << "\n Memoria Cache \n";
		this->getList()->DisplayString();
		
	}else {
		cout << "El Id proveido NO es valido o no Existe\n \n";
	}
	cout << "Presione Enter para Volver al Menu Anterior \n";
}

void AppManager::DeleteClient() {
	string clientId = "";

	cout << "Eliminar Cliente \nDigite Primero un cliente Id \n";
	getline(cin, clientId);
	if (Menu::Is_number(clientId))
	{
		Menu::ClearMenu();
		
		cout << "Removiendo de Arbol\n \n";
		this->getBst()->Delete(stoi(clientId));
		cout << "Pre Orden de Arbol\n \n";
		this->getBst()->PreOrder();

		cout << "Removiendo de CACHE SI Existe\n \n";
		int idx = this->getList()->GetElementIndexById(stoi(clientId));
		this->getList()->RemoveElementAtIndex(idx);
		this->getList()->DisplayString();

		FileLoader loader;
		loader.SoftDeleteInClientsFile(stoi(clientId));
	}
	else {
		cout << "El Id proveido NO es valido o no Existe\n \n";
	}
	cout << "Presione Enter para Volver al Menu Anterior \n";
}


void AppManager::PurgeClient() {
	Menu::ClearMenu();
	cout << "Purgar Cliente \n";

	FileLoader loader;
	loader.PurgeClientsFile();
	cout << "Desea sobreescribir Cliente ? Escriba si para proceder \n";
	string answer = "";
	getline(cin, answer);
	if (answer == "si")
	{
		loader.OverrideClientFile();
		cout << "Archivo actualizado correctamente \n";
	}
	cout << "Pre Orden de Arbol\n \n";
	this->getBst()->PreOrder();

	cout << endl;
	cout << "\n Memoria Cache \n";
	this->getList()->DisplayString();
	cout << "Presione Enter para Volver al Menu Anterior \n";
}

void AppManager::ReIndex() {
	string clientId = "";

	cout << "ReIndexar\n";
	FileLoader loader;
	this->setClientTotalRecords(loader.LoadFiles()->Length());
	this->setBst(loader.BuilBST());
	cout << "Pre Orden de Arbol\n \n";
	this->getBst()->PreOrder();

	cout << endl;
	cout << "\n Memoria Cache \n";
	this->getList()->DisplayString();
	cout << "Archivos ReIndexados \n";
	cout << "Presione Enter para Volver al Menu Anterior \n";
}
