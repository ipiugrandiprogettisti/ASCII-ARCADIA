main: main.o myLib.o
	gcc -o main main.o myLib.o -lncurses
main.o: main.cpp
	gcc -c main.cpp myLib.hpp
myLib.o: myLib.cpp
	gcc -c myLib.cpp
clean:
	rm *.o main