
test:3.o List.o
	g++ 3.o List.o -o test

BinaryTree.o:Utilities/BinaryTree.h Utilities/BinaryTree.cpp
	g++ -std=c++11 -c Utilities/BinaryTree.cpp -o BinaryTree.o

List.o:Utilities/List.h Utilities/List.cpp
	g++ -std=c++11 -c Utilities/List.cpp -o List.o

3.o:3.cpp Utilities/List.h
	g++ -std=c++11 -c 3.cpp -o 3.o


clean:
	rm test *.o *.out

