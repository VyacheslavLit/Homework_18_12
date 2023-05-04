#pragma once
#include <vector>
#include <memory>
#include <set>
#include <exception>
#include <iostream>
#include "MessagePC.h"


//отработка исключений на повтор логина
struct ExpLogin :public exception
{
	const char* what() const noexcept override
	{
		return "К сожалению данный логин занят, измените логин.\n";
	}
};

//отработка исключений на повтор имени
struct ExpName :public exception
{
	const char* what() const noexcept override
	{
		return "К сожалению данное имя занято, измените имя.\n";
	}
};



/*
	Класс PerCor - основной класс обеспечивающий линую переписку.

	me_ - переменная определяющая пользователя              -- второстепенные методы - метода LoginMenu --
	party_ - переменная определяющая собеседника       getUsersFile - загрузка пользователей в контейнер из файла
	users_ - контейнер пользователей                   login - вход пользователя
	perCorParty_ - контейнер пользователей             registration - регистрация пользователя
			с которыми открыта переписка				  setUsersFile (дополнительный метод метода registration) -
	messagePC_ - контейнер с личной перепиской							внесение зарегистрированного пользователя в файл
	currentUser_ - указатель на пользователя (меня)			-- второстепенные методы - метода UserMenu --
			из общего контейнера рользователей         getMessagePC_File - загрузка личной переписки из файла
			--- ОСНОВНЫЕ МЕТОДЫ ---					   perCorParty - заполнение контейнера пользователей с которыми открыта личная переписка
	LoginMenu - вход и регистрацию пользователя	  	   setParty - выбор текущего собеседника
	UserMenu - выбор собеседника					   addParty - добавление и выбор нового собеседника
	showPC - переписка 								   expParty (дополнительный метод метода addParty) -
	loginAdminPC() - вход админа					   проверка выбранного пользователя на ошибки
															-- второстепенные методы - метода showPC --
	getUserByLogin - указатель проверяющий логин	   chat - вывод личной переписки с выбранным собеседником
		на предмеет повторов						   addMessage - добавление сообщения в чат и сохранения его в контейнер переписки
	getUserByName - указатель проверяющий имя				-- вспомогательный метод --
		на предмеет повторов						   expCin - обработка ошибок при использовании оператора cin
*/
class PerCor {
	string me_="";
	string party_="";
	map <const string, User> users_;

	set <string> perCorParty_;
	vector<MessagePC> messagePC_;

public:
	string getMe() const { return me_; }
	void loginMenuPC();
	void userMenuPC();
	void showPC();
	void loginAdminPC();
	auto getParty() { return party_; }

private:
	void getUsersFile();
	void login();
	void registration();
	void setUsersFile(const string, const string, const string);
	void getMessagePC_File();
	void perCorParty();
	void addParty();
	bool expParty(const string name);
	void chat();
	void addMessage(const string txt);
	void expCin();

	bool getUserByLogin(const string& login) const;
	bool getUserByName(const string& name)const;
	string getNameToLogin(string);

};
