#include <string>
#include "Menu.h"
#include "AppManager.h"

using namespace std;

int main() {

	AppManager manager;

	manager.InitTreeLoad();

	int yourchoice = 0;

	string confirm = "";

	Menu::Displaymenu();

	do
	{
		getline(cin, confirm);

		if (confirm.length() == 0) {

			Menu::Displaymenu();
			confirm = " ";
			continue;
		}

		switch (confirm[0])
		{
		case '1':
			Menu::ClearMenu();
			manager.BuildBST();
			yourchoice = 6;
			break;
		case '2':
			Menu::ClearMenu();
			manager.InsertClient();
			yourchoice = 6;
			break;
		case '3':
			Menu::ClearMenu();
			manager.SearchClient();
			yourchoice = 6;
			break;
		case '4':
			Menu::ClearMenu();
			manager.DeleteClient();
			yourchoice = 6;
			break;
		case '5':
			Menu::ClearMenu();
			manager.PurgeClient();
			yourchoice = 6;
			break;
		case '6':
			Menu::ClearMenu();
			manager.ReIndex();
			yourchoice = 6;
			break;
		case '7':
			cout << "Desea Salir ? Presione Y\n";
			getline(cin, confirm);
			if (confirm == "Y" || confirm == "y")
			{
				confirm = "";
			}
			else {
				confirm = " ";
			}
		default:
			Menu::Displaymenu();
			break;
		}

	} while (confirm.length() != 0);

	return 0;
}