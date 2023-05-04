#include <iostream>
#include <ctime>
#include <fstream>
#include <iterator>
#include "Chat.h"
#include "PerCor.h"

/*
	  --- ОСНОВНОЙ МЕТОД класса переписки Chat ---
		LoginMenu - вход и регистрацию пользователя.
		В данном методе предоставлется выбор и реализация Входа в переписку
	под  своим  логином  и  паролем, регистрация нвого пользователя и выход
	в предыдущее меню.
		Определяется    значение    указателя    currentUser_   (корректный
	пользователь)   текущий   пользователь,  от  лица  которого  происходит
	общение.
		База   пользователей   загружается   из   файла   User.txt,   новые
	пользователи добавляются в данный файл.
*/
void Chat::loginMenu()
{
	string operation;
	system("clear");
	getUsersFile();
	while (true)
	{
		cout << "1. Вход.\n2. Регистрация.\n0. Выход в предыдущее меню.\n";
		cin >> operation;
		cin.clear();
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (operation == "1")
		{
			login();
			break;
		}
		//При регистрации отрабатываются исключения на повтор имён и логинов.
		if (operation == "2")
		{
			try
			{
				registration();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				cin.get();;
			}
			continue;
		}
		if (operation == "0")
		{
			break;
		}
		cout << "Выбор не пределен. Повторите попытку.\n";
		cin.get();
		continue;
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса переписки Chat ---
		showChat  -  вывод  на  экран  переписки с возможностью продолжения
	переписки.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку   и  дает  возможность  написать  новое  сообщение,  обновить
	переписку, чтобы проверить новые сообщения.
*/
void Chat::showChat()
{
	string txt;
	system("clear");
	getMessage_File();
	/*
	Применение бесконечного цикла обеспечивает непрерывнсть работы
	и возможность обновлять переписку.
	*/
	while (true)
	{
		chat();
		cout << "Введите сообщение или: 1 обновить переписку, 0 выйти из переписки.\n";
		getline(cin, txt);
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (txt == "1")continue;
		if (txt == "0")break;
		if (!txt.empty()) addMessage(txt);
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса переписки Chat ---
		showChatDict  -  вывод  на  экран  переписки с возможностью продолжения
	переписки с использованием словаря.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку   и  дает  возможность  написать  новое  сообщение (возможно с
	использованием словаря),  обновить 	переписку, чтобы проверить новые сообщения.
*/

void Chat::showChatDict(Dict dict)//const
{
	string mes;
	char tmp;
	system("clear");
	getMessage_File();
	/*
	Применение бесконечного цикла обеспечивает непрерывнсть работы
	и возможность обновлять переписку.
	*/
	while (true)
	{
		system("clear");
		chat();
		mes = dict.messeng();
		if (mes != "") addMessage(mes);
		cout << "Продолжить переписку любая буква, 0 выйти из переписки.\n";
		cin >> tmp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}
		if (tmp == '0')break;
	}
}




/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода LoginMenu ---
		getUsersFile - загрузка пользователей из файла User.txt.
		В  даном  методе  мы  заполняем  вектор  User,  данными  считанными
	из  файла  User.txt.  При  этом  происходит  проверка на доступ к файлу
	в случае если он открыт другим пользователем.
*/
void Chat::getUsersFile()
{
	char tmp;
	string banTMP;
	string loginTMP;
	string passwordTMP;
	string nameTMP;
	while (true)
	{
		system("clear");
		ifstream inf("./Users.txt");
		/*
		повторить операцию, чтобы обеспечить обязательность загрузки базы пользователей.
		*/

		if (! inf.is_open())
		{
			while (true)
			{
				cout << "Неудачная загрузка базы пользователей, наберите любой символ для повтора или \n0 - для продолжения без загрузки базы пользователей.: ";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					inf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') break;
			continue;
		}

		while (inf)
		{
			getline(inf, banTMP);
			if (!inf) break;
			getline(inf, loginTMP);
			if (!inf) break;
			getline (inf, passwordTMP);
			if (!inf) break;
			getline (inf, nameTMP);
			User user = User(banTMP, loginTMP, passwordTMP, nameTMP);
			users_.insert(make_pair(loginTMP, user));
		}
		inf.close();
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода LoginMenu ---
		login - вход в прорамму по логину и паролю.
		В  даном  методе  пользователю дается возможность ввести свой логин
	и пароль. Производится их проверка, при наличии такой комбинации в базе
	пользователей     выбирается    текущий    пользователь    currentUser_
	и  присваивается  переменной  me_  имя текущео пользователя. если такой
	логин   отсутсвует   или  пароль  не  соответствует  введеному  логину,
	выводится ошибка, и предложение повториь ввод.
*/
void Chat::login() {
	string login, password;
	system("clear");
	do
	{
		cout << "Для входя введите логин и пароль, или 0 для выхода:\n";
		cout << "Логин: ";
		cin >> login;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "Пароль: ";
		cin >> password;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (login == "0" || password == "0") break;
		map <const string, User> :: iterator it = users_.find(login);
		me_ = it->second.getName();
		if (password != users_.find(login)->second.getPassword())
		{
			me_ = "";
			cout << "Логин или пароль введены не верно\nПовторите ввод.\n";
			continue;
		}
		if (users_.find(login)->second.getBan() == "true")
		{
			me_ = "";
			cout << "Данный пользователь забанен\nПопробуйте другова пользователя.\n";
			continue;
		}
	} while (me_ == "");
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода LoginMenu ---
		registration - добавление новогопользователя в базу пользователей.
		В  даном  методе  пользователю  дается  возможность  добавить новую
	учетную запись, путем введения своих логина, пароля и имени.
		Производится  проверка  логина и имени на уникальность, при наличии
	повторов  в  базе  пользователей,  дается  возможность  повторить  ввод
	скорректировав повтор.
		По  результатам ввода вызывается дополнительный метод setUsersFile,
	для   добавления  нового  пользователя  в  базу  и  происходит  возврат
	в предыдущее меню.
*/
void Chat::registration()
{
	string login, password, name;
	while (true)
	{
		system("clear");
		cout << "Для регистрации нового пользователя введите логин, пароль и имя пользователя.\n";
		cout << "Логин: ";
		cin >> login;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (getUserByLogin(login) || login == "Admin" || login == "0")throw ExpLogin();
		cout << "\nПароль: ";
		cin >> password;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "\nИмя: ";
		cin >> name;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (getUserByName(name) || name == "0") throw ExpName();
		cout << endl;
		break;
	}
	setUsersFile(login, password, name);
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода registration ---
		setUsersFile  - добавление новогопользователя в базу пользователей.
		В  даном методе данные пользователя введенные в методе registration
	вносятся в файл Users.txt и добавляется новая запись в вектор User. При
	этом  проверяется,  что  файл  открыт  без  ошибок.  При наличии ошибки
	открытия  файла,  пользователю  дается  возможность  повторить  попытку
	сохранения свои данных..
*/
void Chat::setUsersFile(string login, string password, string name)
{
	char tmp;
	while (true)
	{
		system("clear");
		ofstream outf("Users.txt", ios::app);
		if (!outf)
		{
			while (true)
			{
				system("cls");
				cout << "Неудачная попытка сохранить данные, наберите любой символ для повтора или \n0 - для продолжения без загрузки базы пользователей.: ";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					outf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') break;
			continue;
		}
		outf << "false/n" << login << "/n" << password << "/n" << name << "/n";
		outf.close();
		User user = User("false", password, name);
		users_.insert({ login, user });
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showChat ---
		getMessagePC_File  -  считывание  сообщений из файла messages.txt и
	внесение   их   в  вектор  message_,  при  этом  обрабатывается  ошибка
	открытия файла.
*/
void Chat::getMessage_File()
{
	char tmp;
	message_.resize(1);
	string delTMP;
	string timeTMP;
	string fromTMP;
	string txtTMP;
	while (true)
	{
		system("clear");
		ifstream inf("./Messages.txt");
		if (!inf)
		{
			while (true)
			{
				cout << "Неудачная загрузка базы личных сообщений, наберите любой символ для повтора";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					inf.close();
					continue;
				}
				break;
			}
			continue;
		}
		while (inf)
		{
			getline(inf, delTMP);
			if (!inf) break;
			getline(inf, timeTMP);
			if (!inf) break;
			getline(inf, fromTMP);
			if (!inf) break;
			getline(inf, txtTMP);
			Message message = Message(delTMP, timeTMP, fromTMP, txtTMP);
			message_.push_back(message);
		}
		inf.close();
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showChat ---
		chat  -  вывод  на экран переписки в виде таблицы изходя из вектора
	message_ с его обновлением.
*/
void Chat::chat()
{
	getUsersFile();
	string from;
	getMessage_File();
	cout << "Общий чат: " << "\n-----------------------------------------------------------------------\n";
	for (auto& mess : message_)
	{
		me_ == mess.getFrom() ? from = "(Я)" : from = mess.getFrom();
		if (me_ != "") if (users_.find(getNameToLogin(me_))->second.getBan() == "true")from += " (Забанен)";
		if (!mess.getTime().empty()) mess.getDelete() == "false" ? cout << mess.getTime() << "\t" << from << "\t" << mess.getText() << endl :
			cout << mess.getTime() << "\t" << from << "\t" << "Сообщение удалено модератором" << endl;
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода showChat ---
		addMessage - добавление нового сообщения в переписку, с добавлением
	данного сообщения в файл messages.txt и в контейнер message_.
*/
void Chat::addMessage(const string txt)
{
	char tmp;
	while (true)
	{
		system("clear");
		ofstream outf("./Messages.txt", ios::app);
		if (!outf.is_open())
		{
			while (true)
			{
				system("clear");
				cout << "Неудачная попытка сохранить сообщение, наберите любой символ для повтора или \n0 - для продолжения без отправки сообщения.: ";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					outf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') break;
			continue;
		}
		outf << "false\n" << time() << "\n" << me_ << "\n" << txt << "\n";
		outf.close();
		Message message = Message("false", time(), me_, txt);
		message_.push_back(message);
		break;
	}
}



/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД ---
		expCin - метод отработки ошибки при испльзовании оператора cin.
		В  даном  методе  производится  очистка буфера ввода, игнорирование
	ошибок и выводится сообщение пользователю сообщения об ошибке.
*/
void Chat::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	cin.get();
};

//проверка логина на повторы
bool Chat::getUserByLogin(const string& login)const
{
	for (int i = 0; i < users_.size(); ++i);

	for (auto it = users_.begin(); it != users_.end(); ++it)
	{
		if (it->first == login)return true;
	}
	return false;
}

//проверка имени на повторы.
bool Chat::getUserByName(const string& name)const
{
	for (auto it = users_.begin(); it != users_.end(); ++it)
	{
		if (it->second.getName() == name)return true;
	}
	return false;
}

string Chat::getNameToLogin(string name)
{
	for (auto it = users_.begin(); it != users_.end(); ++it)
	{
		if (it->second.getName() == name)return it->first;
	}
	return "";

}
