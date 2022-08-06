main: main.o game.o MyString.o myWindow.o utils.o Map.o Room.o Entity.o Artifact.o Character.o Protagonist.o Power.o 
	g++ -o main main.o game.o MyString.o myWindow.o utils.o Map.o Room.o Entity.o Character.o Protagonist.o Artifact.o Power.o -lncurses
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
Character.o: Character.cpp
	g++ -c Character.cpp header/Character.hpp
Protagonist.o: Protagonist.cpp
	g++ -c Protagonist.cpp header/Protagonist.hpp
Artifact.o: Artifact.cpp
	g++ -c Artifact.cpp header/Artifact.hpp
Power.o: Power.cpp
	g++ -c Power.cpp header/Power.hpp
clean:
	rm *.o ./header/*.gch main
run: main
	./main