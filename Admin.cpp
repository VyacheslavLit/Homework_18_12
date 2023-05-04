#include "Admin.h"

/*
	  --- ОСНОВНОЙ МЕТОД класса администротора Admin ---
		LoginMenu - вход администратора.
		В   данном   методе   предоставлется  входа   под   своим  паролем,
	возможность его изменить и выход в предыдущее меню.
*/
void Admin::loginMenu()
{
	string tmp;
	while (true)
	{
		system("clear");
		cout << "1. Ввод пароля.\n2. Смена пароля.\n0. Выход в предыдущее меню.\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "1")
		{
			inPassword();
			break;
		}
		if (tmp == "2")
		{
			passChange();
			continue;
		}
		if (tmp == "0")
		{
			break;
		}
		cout << "Выбор не пределен. Повторите попытку.\n";
		cin.get();
		continue;
	}
}

/*
	  --- ОСНОВНОЙ МЕТОД класса администротора Admin ---
		adminMenu - меню администратора.
		В   данном   методе   администратор выбирает  в  каком  направлении
	работать на данный момент.
		1. Наложение (снятие) бана с пользователя
		2. Администрирование общего чата (возможность удалять сообщения  не
	проходящие цензуру)
		3. Личная  переписка  с  пользователями  (переход на класс PerCor -
	персональная переписка)
*/
void Admin::adminMenu()
{
	string tmp;
	while (true)
	{
		system("clear");
		cout << "----- Доступные разделы администриррования -----\n";
		cout << "1. Наложение (снятие) бана с пользователя.\n";
		cout << "2. Администрирование общего чата.\n";
		cout << "3. Личная переписка с пользователями\n";
		cout << "------------------------------------------------\n";
		cout << "Выберите необходимый раздел, 0 - выход из администрирования.\n";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "0") break;
		if (tmp == "1")
		{
			ban();
			continue;
		}
		if (tmp == "2")
		{
			showChat();
			continue;
		}
		if (tmp == "3")
		{
			PerCor perCor;
			perCor.loginAdminPC();
			perCor.userMenuPC();
			if (!perCor.getParty().empty()) perCor.showPC();
			continue;
		}
		cout << "\nВыбор не определен.\nПовторите попытку\n";
		cin.get();
	}
}




/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenu ---
		loginMenu - ввод пароля.
*/
void Admin::inPassword()
{
	string tmp;
	getUsersFile();
	while (!login_)
	{
		system("clear");
		cout << "Введите пароль, 0 - выход без ввода пароля: ";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == "0") break;
		currentAdmin_ = getAdminByLogin("admin");
		if (tmp != currentAdmin_->getPassword())
		{
			cout << "Пароль введен не верно\nПовторите ввод.\n";
			cin.get();
			continue;
		}
		login_ = (true);
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenu ---
		passChange - смена пароля.
*/
void Admin::passChange()
{
	string tmpPass;
	string tmpPassNew1;
	string tmpPassNew2;
	string tmp;
	getUsersFile();
	while (true)
	{
		system("clear");
		cout << "Введите действующий пароль, 0 - для выхода: ";
		cin >> tmpPass;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpPass == "0")break;
		cout << "Введите новый пароль: ";
		cin >> tmpPassNew1;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		cout << "Повторите новый пароль: ";
		cin >> tmpPassNew2;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		currentAdmin_ = getAdminByLogin("admin");
		if (tmpPass != currentAdmin_->getPassword())
		{
			cout << "Пароль введен не верно\nПовторите ввод.\n";
			cin.get();
			continue;
		}
		if (tmpPassNew1 != tmpPassNew2)
		{
			cout << "\nНовые пароли не совпадают\nПовторите попытку.\n";
			cin.get();
			continue;
		}
		tmp = currentAdmin_->getPassword();
		users_[Admin::numAdmin_].setPassword(tmpPassNew1);
		if (setUsersFile())
		{
			cout << "\nСохранение пароля неудалось.\nПовторите попытку.\n";
			users_[Admin::numAdmin_].setPassword(tmp);
			cin.get();
		}
		break;
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода loginMenu ---
		setUsersFile - сохранение пользователей в файл User.txt.
		В даном методе мы переносим данные из вектора User, в файл User.txt.
	При этом  происходит  проверка на доступ к файлу в случае если он открыт
	другим пользователем.
*/
bool Admin::setUsersFile()
{
	char tmp;
	while (true)
	{
		system("clear");
		ofstream outf("./Users.txt", ios::out);
		if (!outf)
		{
			while (true)
			{
				system("clear");
				cout << "Неудачная попытка сохранить данные, наберите любой символ для повтора или \n0 - для продолжения без сохранений\n";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					outf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') return true;
			continue;
		}
		for (auto& user : users_)
		{
			outf << user.getBan() << endl << user.getLogin() << endl << user.getPassword() << endl << user.getName() << endl;
		}
		outf.close();
		return (false);
	}
}

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД метода adminMenu ---
		ban - в данном методе прописана возможность наложить  и снять бан на
	пользователя.

*/
void Admin::ban()
{
	int numTMP;
	string tmpBan;
	unsigned tmpUser;
	while (true)
	{
		system("clear");
		cout << "----- Перечень пользователей -----\n";
		numTMP = 0;
		for (auto& user : users_)
		{
			if (numTMP <= 0)
			{
				numTMP++;
				continue;
			}
			cout << numTMP << ".\t" << user.getLogin() << "\t" << user.getName();
			if (users_[numTMP].getBan() == "true") cout << "\t(забанен).";
			cout << endl;
			numTMP++;
		}
		cout << "----------------------------------\n";
		cout << "1. Наложить бан.\n2. Снять бан.\n-------------\nВыберите необходимый раздел, 0 - выход в предыдущее меню.\n";
		cin >> tmpBan;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpBan == "0")
		{
			setUsersFile();
			break;
		}
		cout << "Выберите пользователя от 1 до " << users_.size() - 1 << ", 0 - выход в предыдущее меню: ";
		cin >> tmpUser;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmpUser == 0)
		{
			setUsersFile();
			break;
		}
		if (tmpUser > users_.size() - 1)
		{
			cout << "Выбор за пределами списка. Повторите ввод.\n";
			cin.get();
			continue;
		}
		if (tmpBan == "1")
		{
			if (users_[tmpUser].getBan() == "false")
			{
				users_[tmpUser].setBan(0);
			}
			else
			{
				cout << "На пользователя уже наложен бан.\nПовторите попытку.\n";
				cin.get();

			}
			continue;
		}
		if (tmpBan == "2")
		{
			if (users_[tmpUser].getBan() == "true")
			{
				users_[tmpUser].setBan(1);
			}
			else
			{
				cout << "На пользователя нет бана.\nПовторите попытку.\n";
				cin.get();

			}
			continue;
		}
		cout << "\nВыбор не определен.\nПовторите попытку\n";
		cin.get();
	}
}

/*
	  --- ДОПОЛНИТЕЛЬНЫЙ МЕТОД метода adminMenu ---
		showChat  -  вывод  на  экран  переписки с возможностью продолжения
	переписки и удаления сообщений пользователей.
		В  данном  методе  предоставлен  бесконечный цикл, который  выводит
	переписку   и  дает  возможность  написать  новое  сообщение,  обновить
	переписку, чтобы проверить новые сообщения, а также  удалить  сообщение
	не отвечающее правилам форума.
*/
void Admin::showChat()//const
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
		cout << "Введите сообщение или: 1 - обновить переписку, 2 - удалить сообщение,\n\t\t\t 3 снять удаление с сообщения, 0 выйти из переписки.\n";
		getline(cin, txt);
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (txt == "0")break;
		if (txt == "1")continue;
		if (txt == "2")
		{
			delMess();
			continue;
		}
		if (txt == "3")
		{
			upDelMess();
			continue;
		}
		if (!txt.empty()) addMessage(txt);
	}
}

/*
	  --- ДОПОЛНИТЕЛЬНЫЙ МЕТОД метода showChat ---
		chat  -  вывод  на экран переписки в виде таблицы изходя из вектора
	message_ с его обновлением.
*/
void Admin::chat()
{
	system("clear");
//	string from;
	int tmp = 1;
	getMessage_File();
	cout << "Общий чат: " << "\n-----------------------------------------------------------------------\n";
	for (auto& mess : message_)
	{
		if (mess.getDelete().empty())continue;
		cout << tmp << "\t";
		if (mess.getDelete() == "true") cout << "(удалено)\t";
		cout << mess.getTime() << "\t" << mess.getFrom() << "\t" << mess.getText() << endl;
		tmp++;
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

/*
	  --- ДОПОЛНИТЕЛЬНЫЙ МЕТОД метода showChat ---
		getMessagePC_File  -  считывание  сообщений из файла messages.txt и
	внесение   их   в  вектор  message_,  при  этом  обрабатывается  ошибка
	открытия файла.
*/
void Admin::getMessage_File()
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
		if (!inf.is_open())
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
		while (inf.is_open())
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
	  --- ДОПОЛНИТЕЛЬНЫЙ МЕТОД метода showChat ---
		delMess  - возможность  пометить  удаленным  сообщение пользователя
	неотвечающее правилам чата.
*/
void Admin::delMess()
{
	string tmpTrue{ "true" };
	string tmpFalse{ "false" };
	int tmp;
	while (true)
	{
		cout << "\n№ сообщения для удаления, от 1 до " << message_.size() - 1 << ", 0 - выход из коррекировки: ";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == 0) break;
		if (tmp<1 || tmp>message_.size() - 1)
		{
			cout << "\nВведеный номер вне диапазона.\nПовторите ввод.\n";
			cin.get();
			continue;
		}
		if (message_[tmp].getDelete() == "true")
		{
			cout << "\nСообщение уже удалено.\n";
			cin.get();
			break;
		}
		getMessage_File();
		message_[tmp].setDelete(tmpTrue);
		if (setMessage_File()) message_[tmp].setDelete(tmpFalse);
		break;
	}
}

/*
	  --- ДОПОЛНИТЕЛЬНЫЙ МЕТОД метода showChat ---
		upDelMess  - снятие пометки удалено с сообщения пользователя.
*/
void Admin::upDelMess()
{
	string tmpTrue{ "true" };
	string tmpFalse{ "false" };
	int tmp;
	while (true)
	{
		cout << "\n№ сообщения для восстановления, от 1 до " << message_.size() - 1 << ", 0 - выход из коррекировки: ";
		cin >> tmp;
		if (cin.fail())
		{
			expCin();
			continue;
		}
		if (tmp == 0) break;
		if (tmp<1 || tmp>message_.size() - 1)
		{
			cout << "\nВведеный номер вне диапазона.\nПовторите ввод.\n";
			cin.get();
			continue;
		}
		if (message_[tmp].getDelete() == "false")
		{
			cout << "\nСообщение не удалено.\n";
			cin.get();
			break;
		}
		getMessage_File();
		message_[tmp].setDelete(tmpFalse);
		if (setMessage_File()) message_[tmp].setDelete(tmpTrue);
		break;
	}
}

/*
	  --- ДОПОЛНИТЕЛЬНЫЙ МЕТОД метода showChat ---
		setMessage_File  -  запись  сообщений в файл messages.txt из вектора
	message_,  при  этом   обрабатывается   ошибка   открытия   файла,   при
	не возможности сохранить возврашается значение false,  для корректировки
	последних изменений.
*/
bool Admin::setMessage_File()
{
	char tmp;
	while (true)
	{
		system("clear");
		ofstream outf("./Messages.txt", ios::out);
		if (!outf)
		{
			while (true)
			{
				system("clear");
				cout << "Неудачная попытка сохранить данные, наберите любой символ для повтора или \n0 - для продолжения без сохранений\n";
				cin >> tmp;
				if (cin.fail())
				{
					expCin();
					outf.close();
					continue;
				}
				break;
			}
			if (tmp == '0') return true;
			continue;
		}
		for (auto& mess : message_)
		{
			if (mess.getDelete().empty())continue;
			outf << mess.getDelete() << "\n" << mess.getTime() << "\n" << mess.getFrom() << "\n" << mess.getText() << "\n";
		}
		outf.close();
		return (false);
	}

}

/*
	  --- ДОПОЛНИТЕЛЬНЫЙ МЕТОД метода showChat ---
		addMessage - добавление нового сообщения в переписку, с добавлением
	данного сообщения в файл messages.txt и в контейнер message_.
*/
void Admin::addMessage(const string txt)
{
	char tmp;
	while (true)
	{
		system("clear");
		ofstream outf("./Messages.txt", ios::app);
		if (!outf)
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
		outf << "false\n" << time() << "\n" << "admin" << "\n" << txt << "\n";
		outf.close();
		Message message = Message("false", time(), "admin", txt);
		message_.push_back(message);
		break;
	}
}

/*
	  --- вспомогательный метод класса администротора Admin ---
		expCin - обработка лшибок ввода с клавиатуры.
*/
void Admin::expCin()
{
	cin.clear();
	cin.ignore(32767, '\n');
	cout << "Ошибка ввода, повторите попытку.\n";
	cin.get();
};

/*
	  --- ВСПОМОГАТЕЛЬНЫЙ МЕТОД ---
		getUsersFile - загрузка пользователей из файла User.txt.
		В  даном  методе  мы  заполняем  вектор  User,  данными  считанными
	из  файла  User.txt.  При  этом  происходит  проверка на доступ к файлу
	в случае если он открыт другим пользователем.
*/
void Admin::getUsersFile()
{
	char tmp;
	string banTMP;
	string loginTMP;
	string passwordTMP;
	string nameTMP;
	while (true)
	{
		system("clear");
		int tmp_=users_.size();
		for(int i=0;i<tmp_;i++)users_.pop_back();
		ifstream inf("./Users.txt");
		if (!inf.is_open())
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
		while(inf)
		{
			getline(inf, banTMP);
			if (!inf) break;
			getline(inf, loginTMP);
			if (!inf) break;
			getline(inf, passwordTMP);
			if (!inf) break;
			getline(inf, nameTMP);
                        User user = User(banTMP, loginTMP, passwordTMP, nameTMP);
                        users_.push_back(user);

		}
		inf.close();
		break;
	}
}




//проверка логина на повторы
shared_ptr<User> Admin::getAdminByLogin(const string& login)//const
{
	int num = 0;
	for (auto& user : users_)
	{
		if (login == user.getLogin())
		{
			setNumAdmin(num);
			return make_shared<User>(user);
		}
		num++;
	}
	return nullptr;
}

//проверка имени на повторы.
shared_ptr<User> Admin::getAdminByName(const string& name)const
{
	for (auto& user : users_)
	{
		if (name == user.getName()) return make_shared<User>(user);
	}
	return nullptr;
}
