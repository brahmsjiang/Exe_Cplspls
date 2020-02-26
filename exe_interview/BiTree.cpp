
#include <iostream>

#include "BiTree.h"

using namespace std;

Tree::Tree(int num[], int len)
{
	if(num == NULL || len == 0)
		return;
	root = new Node(num[0]);
	for(int i=1;i < len;i++)
	{
		insertNode(num[i]);
	}
}

void Tree::insertNode(int data)
{
	if(root != NULL)
	{
		insertNode(root, data);
	}
	else
	{
		root = new Node(data);
	}
}

void Tree::insertNode(Node* current, int data)
{
	if(current->data > data)
	{
		if(current->left == NULL)
		{
			current->left = new Node(data);
			current->left->parent = current;
		}
		else {
			insertNode(current->left, data);
		}
	}
	else if(current->data < data)
	{
		if(current->right == NULL)
		{
			current->right = new Node(data);
			current->right->parent = current;
		}
		else {
			insertNode(current->right, data);
		}
	}
	return;

}


Node* Tree::searchNode(int data)
{
	if(root != NULL)
	{
		return searchNode(root, data);
	}
	return NULL;
}

Node* Tree::searchNode(Node* current, int data)
{
	if(current->data > data)
	{
		if(current->left == NULL)
			return NULL;
		return searchNode(current->left, data);
	}
	else if(current->data < data)
	{
		if(current->right == NULL)
			return NULL;
		return searchNode(current->right, data);
	}
	return current;
}

void Tree::deleteNode(int data)
{
	Node* current = NULL;
	current = searchNode(data);
	if(current != NULL)
	{
		deleteNode(current);
	}
}

void Tree::deleteNode(Node* current)
{
	if(current->left != NULL)
	{
		deleteNode(current->left);
	}
	if(current->right != NULL)
	{
		deleteNode(current->right);
	}
	if(current->parent == NULL)
	{
		delete current;
		root = NULL;
		return;
	}
	if(current->parent->right == current)
	{
		current->parent->right = NULL;
	}
	else {
		current->parent->left = NULL;
	}
	delete current;

}	

void Tree::InOrderTree()
{
	if(root == NULL)
		return;
	InOrderTree(root);	
}

void Tree::InOrderTree(Node* current)
{
	if(current->left != NULL)
		InOrderTree(current->left);
	cout << current->data << " ";
	if(current->right != NULL)
		InOrderTree(current->right);
}


int main(int argc, char* argv[])
{
	int data[] = {2,6,7,1,4,8,3,10,5,11};
	unsigned int len = (unsigned int)sizeof(data)/sizeof(int);
	Tree newtree;
	for(int i=0;i<len;i++)
		newtree.insertNode(data[i]);
	newtree.InOrderTree();
	return 0;
}




