
test:main.o person.o personimpl.o
	g++ main.o person.o personimpl.o -o test

main.o:main.cpp Person.h
	g++ -c main.cpp -o main.o

person.o:Person.cpp Person.h PersonImpl.h
	g++ -c Person.cpp -o person.o

personimpl.o:PersonImpl.cpp PersonImpl.h
	g++ -c PersonImpl.cpp -o personimpl.o

clean:
	rm test main.o person.o personimpl.o

