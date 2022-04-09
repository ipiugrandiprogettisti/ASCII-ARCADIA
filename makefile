main: main.o game.o MyString.o myWindow.o utils.o map.o
	g++ -o main main.o game.o MyString.o myWindow.o utils.o map.o -lncurses
main.o: main.cpp header/game.hpp
	g++ -c main.cpp
game.o: game.cpp header/game.hpp
	g++ -c game.cpp
MyString.o: MyString.cpp header/MyString.hpp
	g++ -c MyString.cpp
myWindow.o: myWindow.cpp
	g++ -c myWindow.cpp header/myWindow.hpp
utils.o: utils.cpp
	g++ -c utils.cpp header/utils.hpp
map.o: map.cpp
	g++ -c map.cpp header/map.hpp
clean:
	rm *.o ./header/*.gch main
run: main
	./main