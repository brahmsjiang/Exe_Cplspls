#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>

using namespace std;

template<typename T>
class Optional
{
    using data_t = typename aligned_storage<sizeof(T), alignment_of<T>::value>::type;
public:
    Optional() {}
    Optional(const T& v) {
        Create(v);
    }
    Optional(const Optional& other) {
        if(other.IsInit())
            Assign(other);
    }
    ~Optional() {
        Destory();
    }
    template<class...Args>
    void Emplace(Args&&... args) {
        Destory();
        Create(forward<Args>(args)...);
    }
    bool IsInit() const { return m_hasInit; }
    explicit operator bool() const {
        return IsInit();
    }
    const T& operator*() const {
        if (IsInit())
            return *((T*)(&m_data));
        throw logic_error("is not init");
    }

private:
    template<class... Args>
    void Create(Args&&... args) {
        new (&m_data) T(forward<Args>(args)...);
        m_hasInit = true;
    }
    void Destory() {
        if (m_hasInit) {
            m_hasInit = false;
            ((T*)(&m_data))->~T();
        }
    }
    void Assign(const Optional& other) {
        if (other.IsInit()) {
            Copy(other.m_data);
            m_hasInit = true;
        } else {
            Destory();
        }
    }
    void Copy(const data_t& val) {
        Destory();
        new (&m_data) T(*((T*)(&val)));
    }
private:
    bool m_hasInit = false;
    data_t m_data;
};

struct MyStruct
{
    MyStruct() {}
    MyStruct(int a, int b): m_a(a), m_b(b) {}
    int m_a;
    int m_b;
};

void TestOptional() {
    Optional<string> a("ok");
    Optional<string> b("ok");
    Optional<string> c("aa");
    c = a;

    Optional<MyStruct> op;
    op.Emplace(1, 2);
    MyStruct t;
    if (op)
        t = *op;
    
    op.Emplace(3, 4);
    t = *op;
}

template<typename T>
struct Lazy
{
    Lazy() {}
    template <typename Func, typename... Args>
    Lazy(Func& f, Args&&... args)
    {
        m_func = [&f, &args...]{ return f(args...); };
    }
    const T& Value()
    {
        if (!m_value.IsInit())
        {
            m_value = m_func();
        }
        return *m_value;
    }
    bool IsValueCreated() const
    {
        return m_value.IsInit();
    }
private:
    function<T()> m_func;
    Optional<T> m_value;
};

template<class Func, typename... Args>
Lazy<typename std::result_of<Func(Args...)>::type> lazy(Func&& func, Args&&... args)
{
    return Lazy<typename std::result_of<Func(Args...)>::type>(forward<Func>(func), forward<Args>(args)...);
}

struct BigObject
{	
	BigObject() {
		cout << "lazy load big object" << endl;
	}
};

struct MyStruct2
{
	MyStruct2() {
		m_obj = lazy([] {return make_shared<BigObject>();  });
	}
	void Load() {
		m_obj.Value();
	}
	Lazy<shared_ptr<BigObject>> m_obj;
};

int Foo(int x) { return x * 2; }

// v1 is NOT a function parameter pack :
template <typename... Types>
void func1(std::vector<Types...> v1)
{}
// v2 IS a function parameter pack:
template <typename... Types>
void func2(std::vector<Types>... v2)
{}

template<typename... Args>
struct function_traits
{
};

int fool1() { return -1; }

struct fool2 {
	int operator()(){ return 0; }
};

struct fool3 {
	int operator()() { return 0; }
};

fool3 fool3_var;

decltype(fool1) fool1_var;
decltype(&fool2::operator()) fool2_var;
decltype(fool3_var()) fool3_var_;

int main(int argc, const char * argv[]) {
    
	function_traits<> funcTrait;
	cout << typeid(fool2_var).name() << endl;
    
	int y = 4;
	auto lazyer1 = lazy(Foo, y);
	cout << lazyer1.Value() << endl;

	Lazy<int> lazyer2 = lazy([] {return 12; });
	cout << lazyer2.Value() << endl;

	function<int(int)> f = [](int x) {return x + 3; };
	auto lazyer3 = lazy(f, 3);
	cout << lazyer3.Value() << endl;

	MyStruct2 t;
	t.Load();

	system("pause");
    return 0;
}
