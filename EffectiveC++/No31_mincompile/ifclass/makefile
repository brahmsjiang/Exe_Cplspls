test:main.o person.o realperson.o
	g++ -Wall main.o person.o realperson.o -o test
	
main.o:main.cpp Person.h
	g++ -c -Wall main.cpp -o main.o

person.o:Person.cpp Person.h RealPerson.h 
	g++ -c -Wall Person.cpp -o person.o

realperson.o:RealPerson.cpp RealPerson.h
	g++ -c -Wall RealPerson.cpp -o realperson.o

clean:
	rm -rf *.o test
