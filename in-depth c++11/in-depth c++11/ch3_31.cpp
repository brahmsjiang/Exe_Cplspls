#include <type_traits>
#include <iostream>
#include <string>
#include <utility>

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
    T const& operator*() const {
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

int main(int argc, const char * argv[]) {
    
    TestOptional();
    
    return 0;
}
