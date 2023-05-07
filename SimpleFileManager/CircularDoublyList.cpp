#include <iostream>
#include <fstream>
#include "CircularDoublyList.h"

int CircularDoublyList::Length()
{
    int cont = 0;

    
    if (IsEmpty())
    {
        return cont;
    }
    else
    {
        DoublyPointerNode aux = head->NextNode;
        cont = cont + 1;
        while (aux != head)
        {
            aux = aux->NextNode;
            cont++;
        }
        return cont;
    }
};

void CircularDoublyList::Add(Object* obj)
{
    if (IsEmpty()) {
        head = new DoublyNode(obj);
        head->PrevNode = head;
        head->NextNode = head;
    }
    else
    {
        DoublyPointerNode newNode = new DoublyNode(obj);
        newNode->NextNode = head;
        newNode->PrevNode = head->PrevNode;//3
        head->PrevNode->NextNode = newNode;//4
        newNode->NextNode->PrevNode = newNode;
        head = newNode;
    }

};

void CircularDoublyList::DisplayString()
{

    if (IsEmpty()) {
        cout << "Cache vacia\n";
    }
    else
    {
        DoublyPointerNode aux = head;
        cout << "Index" << " " << "Id" << " " << "Nombre Cliente" << "\n" << endl;

        do {
            cout << aux->PrevNode->value->getIndex() << " " << aux->PrevNode->value->getId() << "  " << aux->PrevNode->value->getName() << "\n" << endl;
            aux = aux->PrevNode;
        } while (aux != head);
    }
};

void CircularDoublyList::GenerateIndexFile()
{

    if (IsEmpty()) {
        cout << "Lista esta vacia\n";
    }
    else
    {
        DoublyPointerNode aux = head;
        ofstream outfile("indices.txt");

        do {
            outfile << aux->PrevNode->value->getIndex() << ";" << aux->PrevNode->value->getId() << "\n";
            aux = aux->PrevNode;
        } while (aux != head);
        outfile.close();
    }
};

void CircularDoublyList::GenerateTemp(){
	
    if (!IsEmpty()) {
        DoublyPointerNode aux = head;
        ofstream outfile("ClientesTemp.txt");

        do {
            outfile << aux->PrevNode->value->getId() << ";" << aux->PrevNode->value->getName() << "\n";
            aux = aux->PrevNode;
        } while (aux != head);
        outfile.close();
    }
};

void CircularDoublyList::OverwriteClientsFile()
{
    if (!IsEmpty()) {
        DoublyPointerNode aux = head;
        ofstream outfile("Clientes.txt");

        do {
            outfile << aux->PrevNode->value->getId() << ";" << aux->PrevNode->value->getName() << "\n";
            aux = aux->PrevNode;
        } while (aux != head);
        outfile.close();
    }
};

void CircularDoublyList::DisplayElementById(int id)
{

    if (IsEmpty()) {
        cout << "Lista esta vacia\n";
    }
    else
    {
        DoublyPointerNode aux = head;

        do {
            if (aux->value->getId() == id) {

                cout << "El record buscado es -> " << aux->value->getId() << " " << aux->value->getName() << "\n" << endl;
                return;
            }
            aux = aux->NextNode;
        } while (aux != head);

        cout << "El record no se encontro con el id proveeido" << endl;
    }
};

bool CircularDoublyList::ExistsElementId(int id)
{

    if (IsEmpty()) {
        return false;
    }
    else
    {
        DoublyPointerNode aux = head;

        do {
            if (aux->value->getId() == id) {

                return true;
            }
            aux = aux->NextNode;
        } while (aux != head);

        return false;
    }
};

bool CircularDoublyList::ExistsElementIdAndSetName(int id, string name)
{

    if (IsEmpty()) {
        return false;
    }
    else
    {
        DoublyPointerNode aux = head;

        do {
            if (aux->value->getId() == id) {

                aux->value->setName(name);
                return true;
            }
            aux = aux->NextNode;
        } while (aux != head);

        return false;
    }
};

int CircularDoublyList::GetElementIndexById(int id) 
{

    int index = -1;
    if (IsEmpty()) {
        return index;
    }
    else
    {
        DoublyPointerNode aux = head;
        index = 0;
        do
        {
            if (aux->value->getId() == id) {
                return index;
            }
            else {
                index++;
            }
            aux = aux->NextNode;
        } while (aux != head);

        return -1;
    }
};

Object* CircularDoublyList::GetElementByKeyId(int id) {

    Object* element = NULL;
    if (!IsEmpty()) {
        DoublyPointerNode aux = head;

        do {
            if (aux->value->getId() == id) {

                return aux->value;
            }
            aux = aux->NextNode;
        } while (aux != head);
    }
    return element;
}

Object* CircularDoublyList::GetElementByKeyIndex(int i) {

    Object* element = NULL;
    if (!IsEmpty()) {
        DoublyPointerNode aux = head;

        do {
            if (aux->value->getIndex() == i) {

                return aux->value;
            }
            aux = aux->NextNode;
        } while (aux != head);
    }
    return element;
}

void CircularDoublyList::SetElementValueById(int id, string name) {

    if (!IsEmpty()) {
        DoublyPointerNode aux = head;

        do {

            if (aux->value->getId() == id) {
                aux->value->setName(name);
            }

            aux = aux->NextNode;
        } while (aux != head);
    }
}

void CircularDoublyList::RemoveElement()
{
    if (IsEmpty())
        cout << "No hay elementos en la lista:" << endl;
    else
    {
        if (head->NextNode == head)
        {
            DoublyPointerNode temp = head;
            head = NULL;
            delete temp;
        }
        else
        {
            DoublyPointerNode aux = head->PrevNode;//1
            DoublyPointerNode temp = head;//2
            aux->NextNode = head->NextNode;//3
            head = head->NextNode; //4
            head->PrevNode = aux;//5
            delete temp;//6
        }
    }
}

void CircularDoublyList::RemoveElementAtIndex(int index)
{
    if (IsEmpty()) {
        cout << "Lista vacia" << endl;
    }
    else
    {
        if ((index == 0))

        {
            RemoveElement();

        }

        else
        {
            if (index > Length() || (index <= 0))
            {
                cout << "Error en posicion" << endl;
            }

            else
            {
                int cont = 1;
                DoublyPointerNode aux = head;
                while (cont < index)
                {
                    aux = aux->NextNode;
                    cont++;
                }
                DoublyPointerNode temp = aux->NextNode;
                aux->NextNode = aux->NextNode->NextNode;
                aux->NextNode->PrevNode = aux;
                delete temp;
            }
        }
    }
}

bool CircularDoublyList::RemoveFront() {

    if (head != NULL) {
        DoublyPointerNode aux = head;
        if (Length() == 1)
        {
            head = NULL;
        }
        else
        {
            DoublyPointerNode back = head->PrevNode;
            back->NextNode = head->NextNode;
            head->NextNode->PrevNode = back;
            head = head->NextNode;
        }
        delete aux;
        return true;
    }
    else
    {
        return false;
    }
}

bool CircularDoublyList::RemoveRear() {

    if (head != NULL) {
        if (Length() == 1)
        {
            delete head;
            head = NULL;
        }
        else
        {
            DoublyPointerNode temp = GetPosition(Length() - 1);
            DoublyPointerNode ultimo = this->head->PrevNode;
            temp->NextNode = head;
            head->PrevNode = temp;
            delete ultimo;
        }
        return true;
    }
    else
        return false;
}

bool CircularDoublyList::RemoveAtIndex(int pos)
{
    if (head == NULL)
        return false;
    else
        if ((pos >= 1) && (pos <= Length()))
            if (pos == 1)
                return RemoveFront();
            else
                if (pos == Length())
                    return RemoveRear();
                else
                {
                    DoublyPointerNode back = GetPosition(pos - 1);
                    DoublyPointerNode found = GetPosition(pos);
                    back->NextNode = found->NextNode;
                    found->NextNode->PrevNode = back;
                    delete found;
                    return true;
                }
        else
            return false;
}

DoublyPointerNode CircularDoublyList::GetPosition(int index)
{
    if (index <= Length())
    {
        if (index == 1)
            return head;
        else
            if (index == Length())
                return head->PrevNode;
            else
            {
                int cont = 1;
                DoublyPointerNode aux = head;
                while (cont != index)
                {
                    aux = aux->NextNode;
                    cont++;
                }
                return aux;
            }
    }
    return NULL;
}


