#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;

class BST;
class BalancedBST;

class BST
{
public:
    BST():bst1(-1),bst2(-2){}
    virtual ~BST(){cout << "BST::~BST" << endl;}
    virtual ostream& operator<<(ostream& os) const
    {
        os << "BST::operator<<:" << bst1 << "," << bst2 << endl;
        return os;
    }
private:
    int bst1;
    int bst2;
};

class BalancedBST: public BST
{
public:
    BalancedBST():bbst1(1), bbst2(2){}
    virtual ~BalancedBST(){cout << "BalancedBST::~BalancedBST" << endl;}
    virtual ostream& operator<<(ostream& os) const
    {
        os << "BalancedBST::operator<<:" << bbst1 << "," << bbst2 << endl;
        return os;
    }
private:
    int bbst1;
    int bbst2;
};


void printBSTArray1(ostream& s, const BST array[], int numEles)
{
    cout << "printBSTArray1:" << endl;
    for (int i = 0; i < numEles; ++i) {
        array[i]<<s;
    }
}

ostream& operator<<(ostream& os, const BST& bst)
{
    bst << os;
    return os;
}

void printBSTArray2(ostream& s, const BalancedBST array[], int numEles)
{
    cout << "printBSTArray2:" << endl;
    for (int i = 0; i < numEles; ++i) {
        cout<<array[i];
    }
}

void deleteArray(ostream& logstream, BST array[])
{
    logstream << "deleting array at address " << static_cast<void*>(array) << endl;
    delete [] array;
}


int main(int argc, char* argv[])
{
    BST BSTArray[10];
    BalancedBST BalancedBSTArray[10];
    
    //printBSTArray1(cout, BSTArray, 10);           //ok
    //printBSTArray1(cout, BalancedBSTArray, 10);   //crash
    
    //printBSTArray2(cout, BSTArray, 10);           //complie failed
    //printBSTArray2(cout, BalancedBSTArray, 10);   //ok
    
    
    BST* balTree = new BalancedBST;
    delete balTree;
    cout << "===============" << endl;
    
    BalancedBST* balTreeArray = new BalancedBST[4];
    deleteArray(cout, balTreeArray);
    cout << "===============" << endl;
    
    BST* treeArray = new BalancedBST[4];
    deleteArray(cout, treeArray);
    cout << "===============" << endl;
    
    return 0;
}
