#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>
#include <tuple>

using namespace std;

struct A: public enable_shared_from_this<A>
{
	shared_ptr<A> GetSelf() {
		return shared_from_this();
		//shared_from_this use inner weak_ptr's lock() to ret shared_ptr
		//based on its inner shared_ptr<A> construct called.
	}
	/*
	shared_ptr<A> GetSelfErrVer() {
		return shared_ptr<A>(this);
	}
	*/
	~A() {
		cout << "A is deleted" << endl;
	}
};

struct AA;
struct BB;

struct AA {
	shared_ptr<BB> bptr;
	~AA() {cout << "AA deleted!" << endl;}
};

struct BB {
	weak_ptr<AA> aptr;
	~BB() {cout << "BB deleted!" << endl;}
};

void TestCycleRef() {
	{
		shared_ptr<AA> ap(new AA);
		shared_ptr<BB> bp(new BB);
		ap->bptr = bp;
		bp->aptr = ap;
		cout << "ap.use_count: " << ap.use_count() << endl;
		cout << "bp.use_count: " << bp.use_count() << endl;
	}
}

weak_ptr<int> wp;
void f() {
	if (wp.expired()) {
		cout << "weak_ptr expired\n";
	} else {
		cout << "weak_ptr valid\n";
		shared_ptr<int> spt = wp.lock();
		cout << *spt << endl;
	}
}

shared_ptr<void> Guard(void* p)
{
	//shared_ptr<void> sp(p, [](void* p){delete p;});
	//return sp;
	return shared_ptr<void>(p, [](void* p){delete p;});
}

shared_ptr<int> Guard(int* p)
{
	//shared_ptr<void> sp(p, [](void* p){delete p;});
	//return sp;
	return shared_ptr<int>(p);
}

int f_int() {
	return int(1);
}

#define GUARD(p) shared_ptr<void> p##p(p, [](void* p){delete p;cout<<"delete p"<<endl;});


int main(int argc, const char * argv[]) {
	void* who = new int(1);
	GUARD(who);
	whowho = nullptr;

	{
		shared_ptr<int> sp = make_shared<int>(42);
		wp = sp;
		f();
	}
	f();

	shared_ptr<A> spy(new A);
	//shared_ptr<A> pp = spy; //same effect as below line
	shared_ptr<A> pp = spy->GetSelf();//wont double free
	{
		A* ptrA = new A;
		shared_ptr<A> p0(ptrA);
		//shared_ptr<A> p1 = ptrA->GetSelf();//err, have to use after shared_ptr construct called 
		shared_ptr<A> p1 = p0->GetSelf();
	}
	//shared_ptr<A> pe = spy->GetSelfErrVer();//err, double free. for ref_count not ref same obj

	cout << "spy.use_count: " << spy.use_count() << endl;
	cout << "pp.use_count: " << pp.use_count() << endl;
	//cout << "pe.use_count: " << pe.use_count() << endl;

	TestCycleRef();


	return 0;
}
