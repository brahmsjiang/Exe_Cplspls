
test:32.o BinaryTree.o
	g++ 32.o BinaryTree.o -o test

BinaryTree.o:Utilities/BinaryTree.h Utilities/BinaryTree.cpp
	g++ -std=c++11 -c Utilities/BinaryTree.cpp -o BinaryTree.o

32.o:32.cpp Utilities/BinaryTree.h
	g++ -std=c++11 -c 32.cpp -o 32.o


clean:
	rm test *.o *.out

