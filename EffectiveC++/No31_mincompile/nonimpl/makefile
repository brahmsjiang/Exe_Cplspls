
test:main.o person.o 
	g++ main.o person.o  -o test

main.o:main.cpp Person.h
	g++ -c main.cpp -o main.o

person.o:Person.cpp Person.h
	g++ -c Person.cpp -o person.o

clean:
	rm test main.o person.o

