main: main.o
	gcc -o main main.o -lncurses
main.o: main.cpp
	gcc -c main.cpp 
clean:
	rm *.o main