#pragma once
#include "User.h"
#include "Times.h"

/*
	Класс class MessagePC, создает тип данных - сообщение в личной переписке.
	time_, from_, from_, to_, text_ данные сообщения.
	del_ - индикатор, сообщение удалено или нет.
*/
class MessagePC
{
	string del_;
	const string time_;
	const string from_;
	const string to_;
	const string text_;

public:
	MessagePC() {}
	MessagePC(string del, const string& times, const string &from, const string &to, const string &text) : del_(del), time_(times), from_(from), to_(to), text_(text) {}
	string& getDelete() { return del_; }
	const string& getTime() const { return time_; }
	const string& getFrom() const { return from_; }
	const string& getTo() const { return to_; }
	const string& getText()const { return text_; }
	void setDelete(string& deletes) { del_ = deletes; }
};