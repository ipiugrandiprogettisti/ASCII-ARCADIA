main: main.o myString.o myWindow.o startmenu.o
	g++ -o main main.o myString.o myWindow.o startmenu.o -lncurses
main.o: main.cpp header/myWindow.hpp header/startmenu.hpp
	g++ -c main.cpp
myString.o: myString.cpp header/myString.hpp
	g++ -c myString.cpp
myWindow.o: myWindow.cpp
	g++ -c myWindow.cpp header/myWindow.hpp
startmenu.o: startmenu.cpp
	g++ -c startmenu.cpp header/startmenu.hpp
clean:
	rm *.o main
run: main
	./main