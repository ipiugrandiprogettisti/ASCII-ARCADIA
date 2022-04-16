main: main.o game.o MyString.o myWindow.o utils.o Map.o Room.o Entity.o
	g++ -o main main.o game.o MyString.o myWindow.o utils.o Map.o Room.o Entity.o -lncurses
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
Map.o: Map.cpp
	g++ -c Map.cpp header/Map.hpp
Room.o: Room.cpp
	g++ -c Room.cpp header/Room.hpp
Entity.o: Entity.cpp
	g++ -c Entity.cpp header/Entity.hpp
clean:
	rm *.o ./header/*.gch main
run: main
	./main