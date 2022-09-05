main: main.o game.o utils.o Map.o Room.o Entity.o Enemy.o Artifact.o Character.o Protagonist.o Power.o 
	g++ -o main main.o game.o utils.o Map.o Room.o Entity.o Enemy.o Artifact.o Character.o Protagonist.o Power.o -lncurses
main.o: main.cpp header/game.hpp
	g++ -c main.cpp
game.o: game.cpp header/game.hpp
	g++ -c game.cpp
utils.o: utils.cpp
	g++ -c utils.cpp header/utils.hpp
Map.o: Map.cpp
	g++ -c Map.cpp header/Map.hpp
Room.o: Room.cpp
	g++ -c Room.cpp header/Room.hpp
Entity.o: Entity.cpp
	g++ -c Entity.cpp header/Entity.hpp
Enemy.o: Enemy.cpp
	g++ -c Enemy.cpp header/Enemy.hpp
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