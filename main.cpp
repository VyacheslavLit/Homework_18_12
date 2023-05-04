#include "Menu.h"
#include <filesystem>
#include <iostream>
using namespace std;


/*Баззовая функция.
  В ней пользовательвыбирает между тремя возможными вариантами работы:

  1. Администрироваие  функции администратора и модератора.
  2. общий чат, в котором все пользователи могут общаться одновременно.
  3. личная переписка, в данном варианте предусмтрено общение тет&тет, другие пользователи не могут просмотреть переписку 2 пользователей.
  4. просмотр правил пользоваия чатом.
  И конечно предусмотрен выход из прграммы.
*/
int main()
{
	char tmp;
        auto permissions=std::filesystem::perms::group_all | std::filesystem::perms::others_all;
	std::filesystem::permissions("./Messages.txt", permissions, std::filesystem::perm_options::remove);
        std::filesystem::permissions("./Users.txt", permissions, std::filesystem::perm_options::remove);
	std::filesystem::permissions("./MessagesPC.txt", permissions, std::filesystem::perm_options::remove);
	//бесконечный цикл для обеспечения непрерывной работы программы.
	while (true)
	{
		system("clear");
		cout << "Выбирите раздел:\n1. Администрирование.\n2. Чат.\n3. Личная переписка.\n4. Правила пользования чатом.\n5. Работа с автозаполнением.\n0. Выход.\n";
		cin >> tmp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}
		if (tmp == '1')
		{
			administration();
			continue;
		}
		if (tmp == '2')
		{
			chat();
			continue;
		}
		if (tmp == '3')
		{
			perCor();
			continue;
		}
		if (tmp == '4')
		{
			regulation();
			continue;
		}
		if (tmp == '5')
		{
			dictMenu();
			continue;
		}
		if (tmp == '0')
		{
			cout << "Нам жаль, что вы уже уходите. Приходите еще.\n";
			cin.get();
			break;
		}
		cout << "Выбор не определен. Повторите попытку.\n";
		cin.get();
		continue;
	}
	return 0;
}
