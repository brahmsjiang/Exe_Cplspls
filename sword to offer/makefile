
test:29.o BinaryTree.o
	g++ 29.o BinaryTree.o -o test

BinaryTree.o:Utilities/BinaryTree.h Utilities/BinaryTree.cpp
	g++ -std=c++11 -c Utilities/BinaryTree.cpp -o BinaryTree.o

29.o:29.cpp Utilities/BinaryTree.h
	g++ -std=c++11 -c 29.cpp -o 29.o


clean:
	rm test *.o *.out

