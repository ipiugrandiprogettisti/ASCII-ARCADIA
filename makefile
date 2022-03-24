main: main.o myLib.o myString.o
	g++ -o main main.o myLib.o myString.o -lncurses
main.o: main.cpp header/myLib.hpp header/myString.hpp
	g++ -c main.cpp
myString.o: myString.cpp header/myString.hpp
	g++ -c myString.cpp
myLib.o: myLib.cpp
	g++ -c myLib.cpp
clean:
	rm *.o main
run: main
	./main