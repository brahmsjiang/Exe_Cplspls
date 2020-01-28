#include <iostream>
#include <stack>
#include <queue>
#include <assert.h>

using namespace std;

template<typename T>
class CQueue
{
public:
    CQueue(void)
    {}
    ~CQueue(void)
    {}

    void appendTail(const T& node);
    T deleteHead();

private:
    stack<T> stack1;//push
    stack<T> stack2;//pop
};


template<typename T>
void CQueue<T>::appendTail(const T& node)
{
    stack1.push(node);
}

template<typename T>
T CQueue<T>::deleteHead()
{
    if (stack2.empty()) //when copy stack1's elems to stack2, stack2 must be empty because pop stack2s' elems first
    {
        while (!stack1.empty())
        {
            T& topEle1 = stack1.top();
            stack2.push(topEle1);
            stack1.pop();
        }
    }

    if (stack2.size() == 0) //just throw a exception, no judgment
        throw exception("queue is empty");

    T head = stack2.top();
    stack2.pop();
    return head;
}

void test_queue()
{
    CQueue<char> cQue;
    cQue.appendTail('a');
    cQue.appendTail('b');
    cQue.appendTail('c');
    cout << cQue.deleteHead() << endl;
    cout << cQue.deleteHead() << endl;
    cQue.appendTail('d');
    cout << cQue.deleteHead() << endl;
    cout << cQue.deleteHead() << endl;
}


template<typename T>
class CStack
{
public:
    CStack(void)
    {}
    ~CStack(void)
    {}

    void appendHead(const T& node);
    T deleteHead();

private:
    queue<T> queue1;
    queue<T> queue2;
};

template<typename T>
void CStack<T>::appendHead(const T& node)
{
    if (queue1.empty() && queue2.empty()) {
        queue1.push(node);
    }
    else if (!queue1.empty() && queue2.empty()) {
        queue1.push(node);
    }
    else if (!queue2.empty() && queue1.empty()) {
        queue2.push(node);
    }
}

template<typename T>
T CStack<T>::deleteHead()
{
    T data{};
    queue<T> *oriQ, *moveTarQ;
    if (!queue1.empty() && queue2.empty()) {
        oriQ = &queue1;
        moveTarQ = &queue2;
    }
    else if (!queue2.empty() && queue1.empty()) {
        oriQ = &queue2;
        moveTarQ = &queue1;
    }
    else {
        return data;
    }

    while (1 < oriQ->size()) {
        moveTarQ->push(oriQ->front());
        oriQ->pop();
    }
    data = oriQ->front();
    oriQ->pop();

    assert(oriQ->empty());
    return data;
   
}

void test_stack()
{
    CStack<char> stk;
    stk.appendHead('a');
    stk.appendHead('b');
    stk.appendHead('c');
    cout << stk.deleteHead() << endl;
    cout << stk.deleteHead() << endl;
    stk.appendHead('d');
    cout << stk.deleteHead() << endl;
    cout << stk.deleteHead() << endl;
}

int main(int argc, char* argv[])
{
    //test_queue();
    test_stack();
    return 0;
}