
test:main.o widget.o
	g++ main.o widget.o -o test

main.o:main.cpp widget.h
	g++ -c main.cpp -o main.o

widget.o:widget.cpp widget.h timer.h
	g++ -c widget.cpp -o widget.o

clean:
	rm test *.o *.gch
