#include <stdlib.h>


class Node
{
public: 
	int data;
	Node* parent;
	Node* left;
	Node* right;

public:
	Node():data(-1),parent(NULL),left(NULL),right(NULL){};
	Node(int num):data(num),parent(NULL),left(NULL),right(NULL){};
};

class Tree
{
public:
	Tree():root(NULL){}	
	Tree(int num[], int len);
	void insertNode(int data);
	Node* searchNode(int data);
	void deleteNode(int data);
	void InOrderTree();
private:
	void insertNode(Node* current, int data);
	Node* searchNode(Node* current, int data);
	void deleteNode(Node* current);
	void InOrderTree(Node* current);

private:
	Node* root;
};
