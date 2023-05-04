#include "DictMenu.h"


void dictMenu()
{
	Dict dict;
	bool dictOn{ false };
	int tmp;
	while (true)
	{
		system("clear");
		cout << "       --------- МЕНЮ РАБОТЫ СО СЛОВАРЕМ ---------\n";
		cout << "1. Пополнение словаря из файла Dict.txt;\n";
		cout << "2. Пополнение словаря из файла общей переписки Messages.txt;\n";
		cout << "3. Пополнение словаря из файла указанного пользователем;\n";
		cout << "4. Показать словарь;\n";
		cout << "5. Общий чат.\n";
		cout << "0. Возврат в предыдущее меню.\n\n";
		cout << "Выберите нужный раздел: ";
		cin >> tmp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nОшибка ввода, повторите попытку.\n";
			cout<<cin.get();
			cin.clear();
			cin.ignore(32767, '\n');
			continue;
		}
		if (tmp < 0 || tmp>5)
		{
			cout << "\nРаздел выбран не корректно, повторите попытку.\n";
			cin.clear();
			cin.ignore(32767, 'n');
			cout << cin.get();
			continue;
		}
		if (tmp == 0) break;
		if (tmp == 1) dictOn = dict.addDictToDict(dictOn);
		if (tmp == 2) dict.addDictToMessages();
		if (tmp == 3) dict.addDictToTxt();
		if (tmp == 4) dict.show();
		if (tmp == 5)
		{
			Chat Chat;
			User user;
			Chat.loginMenu();
			if (Chat.getMe() != "" && dictOn)
			{
				Chat.showChatDict(dict);
				break;
			}
			else if (!dictOn)
			{
				cout << "\nСловарь еще не загружен.\n";
				cin.clear();
				cin.ignore(32767, '\n');
				cout << cin.get();
			}
			else
			{
				cout << "\nПользователь еще не выбран.\n";
				cin.clear();
				cin.ignore(32767, '\n');
				cout << cin.get();
			}
		}

	}
}


void expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	cout << cin.get();
	cin.clear();
	cin.ignore(32767, '\n');
};
