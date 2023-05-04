#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>
#include "User.h"
using namespace std;

/*
	Функция присвоения системного времени и даты контейнеру S, с возвратом по запросу.
*/
string time()
{
	char s[20];
	struct tm* u;
	const time_t timer = time(NULL);
	u = localtime(&timer);
	for (int i = 0; i < 20; i++) s[i] = 0;
	int length = strftime(s, 20, "%d.%m.%Y %H:%M:%S", u);
	return (string)s;
}