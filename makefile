main: main.o myLib.o
	g++ -o main main.o myLib.o -lncurses
main.o: main.cpp
	g++ -c main.cpp myLib.hpp
myLib.o: myLib.cpp
	g++ -c myLib.cpp
clean:
	rm *.o main