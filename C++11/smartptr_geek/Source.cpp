#include "smart_ptr.h"
#include <stdlib.h>
#include <assert.h>

template <typename T>
void swap(smart_ptr<T>& lhs, smart_ptr<T>& rhs) noexcept
{
    lhs.swap(rhs);
}

template <typename T, typename U>
smart_ptr<T> static_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = static_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = dynamic_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr); //return by val would use copy ctor
}

class A
{
public:
    virtual void printA() { //virtual func is needed to make dynamic_cast work, because compiler found no need to create a vtable
        cout << "printA" << endl;
    }
};

class AA : public A
{
public:
    void printAA() {
        cout << "printAA" << endl;
    }
};

class AB : public A
{
public:
    void printAB() {
        cout << "printAB" << endl;
    }
};


int main(int argc, char* argv[])
{
    {
        smart_ptr<A> ptr1(new AA);
        smart_ptr<A> ptr2{ ptr1 }; //call copy ctor
        //smart_ptr<A> ptr21 = ptr1; //call copy ctor
        smart_ptr<A> ptr22; 
        cout << "===============" << endl; 
        ptr22 = ptr1; //call operator=
        cout << "===============" << endl;

        ptr2->printA();
        (*ptr2).printA();
        if (ptr2) {
            cout << "ptr2 not null" << endl;
        }
    }
    cout << "---------------" << endl;
    {
        smart_ptr<AA> ptr3(new AA);
        smart_ptr<A> ptr4{ ptr3 };
        smart_ptr<A> ptr5{ move(ptr3) };
        ptr4->printA();
        //ptr4->printAA(); //compile err
        
    }
    cout << "---------------" << endl;
    {
        smart_ptr<A> ptr6{ new AA };
        smart_ptr<AA> ptr7 = dynamic_pointer_cast<AA>(ptr6); //dynamic_(pointer_)cast, convert base_ptr to child_ptr
        assert(ptr7);
        ptr7->printA();
        ptr7->printAA();
    }
    cout << "`````````````" << endl;
    {
        smart_ptr<A> ptr6{ new AA };
        smart_ptr<AA> ptr7 = static_pointer_cast<AA>(ptr6); //dynamic_(pointer_)cast, convert base_ptr to child_ptr
        assert(ptr7);
        ptr7->printA();
        ptr7->printAA();
    }
    cout << "---------------" << endl;
    {
        smart_ptr<A> ptr6{ new A };
        smart_ptr<AA> ptr7 = dynamic_pointer_cast<AA>(ptr6); //dynamic_(pointer_)cast, convert base_ptr to child_ptr
        if (!ptr7)
            cout << "nullptr !" << endl;
    }
    cout << "~~~~~~~~~~~~~~~" << endl;
    {
        smart_ptr<A> ptr8{ new A };
        smart_ptr<AA> ptr9 = static_pointer_cast<AA>(ptr8);
        assert(ptr9);
        ptr9->printA();
        ptr9->printAA();
    }
    cout << "---------------" << endl;
    {
        smart_ptr<AA> ptr10{ new AA };
        smart_ptr<A> ptr11 = static_pointer_cast<A>(ptr10);
        assert(ptr11);
        ptr11->printA();
    }
    cout << "---------------" << endl;
    {
        smart_ptr<A> ptr8{ new A };
        smart_ptr<AA> ptr9 = static_pointer_cast<AA>(ptr8);
        assert(ptr9);
        ptr9->printA();
        ptr9->printAA();
    }
    cout << "---------------" << endl;
    system("pause");
    return 0;
}











