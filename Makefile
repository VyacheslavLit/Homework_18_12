main: main.cpp Menu.cpp Menu.h DictMenu.cpp DictMenu.h Admin Chat Dict PerCor Times
	g++ -o main -std=c++17 main.cpp Menu.cpp DictMenu.cpp -L. -lAdmin -lChat -lDict -lPerCor -lTimes

Admin: Admin.cpp Admin.h
	g++ -o Admin.o Admin.cpp -c
	ar rc libAdmin.a Admin.o

Chat: Chat.cpp Chat.h User.h
	g++ -o Chat.o Chat.cpp -c
	ar rc libChat.a Chat.o

Dict: Dict.cpp Dict.h
	g++ -o Dict.o Dict.cpp -c
	ar rc libDict.a Dict.o

PerCor: PerCor.cpp PerCor.h User.h
	g++ -o PerCor.o PerCor.cpp -c
	ar rc libPerCor.a PerCor.o      

Times: Times.cpp Times.h
	g++ -o Times.o Times.cpp -c
	ar rc libTimes.a Times.o

cl:
	rm *.a *.o

in:
	install ./main ~/bin

ui:
	rm -rf ~/bin/main


