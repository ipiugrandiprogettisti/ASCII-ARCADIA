main: main.o game.o MyString.o myWindow.o startMenu.o
	g++ -o main main.o game.o MyString.o myWindow.o startMenu.o -lncurses
main.o: main.cpp header/game.hpp
	g++ -c main.cpp
game.o: game.cpp header/game.hpp
	g++ -c game.cpp
MyString.o: MyString.cpp header/MyString.hpp
	g++ -c MyString.cpp
myWindow.o: myWindow.cpp
	g++ -c myWindow.cpp header/myWindow.hpp
startMenu.o: startMenu.cpp
	g++ -c startMenu.cpp header/startMenu.hpp
clean:
	rm *.o ./header/*.gch main
run: main
	./main