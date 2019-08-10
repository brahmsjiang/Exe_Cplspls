
test:34.o BinaryTree.o
	g++ 34.o BinaryTree.o -o test

BinaryTree.o:Utilities/BinaryTree.h Utilities/BinaryTree.cpp
	g++ -std=c++11 -c Utilities/BinaryTree.cpp -o BinaryTree.o

34.o:34.cpp Utilities/BinaryTree.h
	g++ -std=c++11 -c 34.cpp -o 34.o


clean:
	rm test *.o *.out

