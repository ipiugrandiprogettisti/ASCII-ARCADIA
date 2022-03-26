main: main.o game.o myString.o myWindow.o startmenu.o
	g++ -o main main.o game.o myString.o myWindow.o startmenu.o -lncurses
main.o: main.cpp header/game.hpp
	g++ -c main.cpp
game.o: game.cpp header/game.hpp
	g++ -c game.cpp
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