#include "smart_ptr.h"
#include "stdlib.h"

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
    T* ptr = dynamic_cast<T*>(other->get());
    return smart_ptr<T>(other, ptr);
}

class A
{
public:
    void printA() {
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


int main(int argc, char* argv[])
{
    smart_ptr<A> ptr_AA(new AA);
    smart_ptr<A> ptr_A{ ptr_AA };

    ptr_AA->printA();
    (*ptr_AA).printA();
    if (ptr_AA) {
        cout << "ptr_AA not null" << endl;
    }


    system("pause");
    return 0;
}











