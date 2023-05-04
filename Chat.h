#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "Message.h"
#include "Dict.h"



class Dict;

/*
	Класс Chat - основной класс обеспечивающий общую переписку.

	me_ - переменная определяющая пользователя              -- второстепенные методы - метода LoginMenu --
	users_ - контейнер пользователей					getUsersFile  -  загрузка  пользователей в контейнер из файла
	message_ - контейнер с перепиской					login - вход пользователя
	currentUser_ - указатель на пользователя (меня)		registration - регистрация пользователя
			из общего контейнера пользователей				setUsersFile (дополнительный метод метода registration) -
																		внесение   зарегистрированного  пользователя
		--- ОСНОВНЫЕ МЕТОДЫ ---											в файл
	LoginMenu - вход и регистрацию пользователя				-- второстепенные методы - метода showChat --
	showChat - переписка								getMessage_File - загрузка переписки из файла
														chat - вывод переписки
	getUserByLogin - указатель проверяющий логин		addMessage - добавление  сообщения  в  чат  и  сохранения его
		на предмет повторов										в контейнер переписки
	getUserByName - указатель проверяющий имя				-- вспомогательный метод --
		на предмет повторов								expCin - обработка ошибок при использовании оператора cin
*/
class Chat {
	string me_ = "";
	map <const string, User> users_;
	vector<Message> message_;

public:
	string getMe() const { return me_; }
	void loginMenu();
	void showChat();
	void showChatDict(Dict dict);

private:
	void getUsersFile();
	void login();
	void registration();
	void setUsersFile(string, string, string);
	void getMessage_File();
	void chat();
	void addMessage(const string txt);
	void expCin();

	bool getUserByLogin(const string& login) const;
	bool getUserByName(const string& name)const;
	string getNameToLogin(string);
};

