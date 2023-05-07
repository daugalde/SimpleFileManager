#pragma once
#include <iostream>
#include <regex>

using namespace std;

class Menu {

public:

	Menu() {}

	static void Displaymenu()
	{
		ClearMenu();
		cout << " ===================================================== \n";
		cout << " \t\tMENU \n ";
		cout << "===================================================== \n";
		cout << " 1.Construir Arbol\n";
		cout << " 2.Insertar Clientes \n";
		cout << " 3.Busqueda Clientes (Cache) \n";
		cout << " 4.Eliminar Clientes \n";
		cout << " 5.Purgar \n";
		cout << " 6.Reindexar \n";
		cout << " 7.Salir \n";
	}

	static void ClearMenu() {
		cout << flush;
		system("CLS");
	}

	bool static Is_number(const std::string& s)
	{
		return !s.empty() && std::find_if(s.begin(),
			s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}

	bool static Is_NOT_EmptyOrWhiteSpace(const std::string& s)
	{
		return !s.empty() && !(s.find_first_not_of(' ') == s.npos);
	}

	std::string ltrim(const std::string& s) {
		return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
	}

	std::string rtrim(const std::string& s) {
		return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
	}

	std::string trim(const std::string& s) {
		return ltrim(rtrim(s));
	}

};