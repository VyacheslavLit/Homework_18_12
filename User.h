#pragma once
#include <string>
#include <map>
#include <set>
using namespace std;


/*
	Объявление класса User - пользователь.
	login_, password_, name_ - данные пользователя.
	ban_ - индикатор наличия бана на пользователе
*/
class User
{
	string ban_;
	const string login_;
	string password_;
	const string name_;

public:
	User() {}
	User(string ban, const string login, string password, const string name) :ban_(ban), login_(login), password_(password), name_(name) {}
	User(string ban, const string password, const string name) :ban_(ban),  password_(password), name_(name) {}
	const string getBan() const { return ban_; }
	const string& getLogin() const { return login_; }
	const string& getPassword() const { return password_; }
	const string& getName() const { return name_; }
	void setPassword(string& password) { password_ = password; }
	void setBan(int ban) { ban ? ban_ = "false" : ban_ = "true"; }
};

