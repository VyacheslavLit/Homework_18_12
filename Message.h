#pragma once
#include "User.h"
#include "Times.h"


/*
	Класс Message, создает тип данных - сообщение.
	time_, from_, text_ данные сообщения.
	del_ - индикатор, сообщение удалено или нет.
*/
class Message
{
	string del_;
	const string time_;
	const string from_;
	const string text_;

public:
	Message() {	}
	Message(string del, const string& times, const string& from, const string& text) :del_(del), time_(times), from_(from), text_(text) {}
	string& getDelete() { return del_; }
	const string& getTime() const { return time_; }
	const string& getFrom() const { return from_; }
	const string& getText()const { return text_; }
	void setDelete(string& del) { del_ = del; }
};