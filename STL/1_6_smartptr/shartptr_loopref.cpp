
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

struct Node_weak
{
	Node_weak(int value)
	:_value(value)
	{
		cout<<"Node_weak()"<<endl;
	}
    ~Node_weak()
    {
        cout<<"~Node_weak()"<<endl;
    }
    weak_ptr<Node_weak> _prev;
    weak_ptr<Node_weak> _next;
    int _value;
};


struct Node
{
	Node(int value)
	:_value(value)
	{
		cout<<"Node()"<<endl;
	}
    ~Node()
    {
        cout<<"~Node()"<<endl;
    }
    shared_ptr<Node> _prev;
    shared_ptr<Node> _next;
    int _value;
};

void Test2()
{
    shared_ptr<Node> sp1(new Node(1));
    shared_ptr<Node> sp2(new Node(2));
    cout << sp1.use_count() << endl;
    cout << sp2.use_count() << endl;
    sp1->_next = sp2;
    sp2->_prev = sp1;
    cout << sp1.use_count() << endl;
    cout << sp2.use_count() << endl;
}

void Test3()
{
    shared_ptr<Node_weak> sp1(new Node_weak(1));
    shared_ptr<Node_weak> sp2(new Node_weak(2));
    cout << sp1.use_count() << endl;
    cout << sp2.use_count() << endl;
    sp1->_next = sp2;
    sp2->_prev = sp1;
    cout << sp1.use_count() << endl;
    cout << sp2.use_count() << endl;
}


int main()
{
	//Test2();
    Test3();
	return 0;
}







