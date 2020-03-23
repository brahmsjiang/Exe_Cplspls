#include <iostream>
#include <string>

using namespace std;

class String
{
public:
	String(const char* str = nullptr);
	~String();

	String(const String& str);	//copy constructor
	String& operator=(const String& str);	//operator=, return ref
	String operator+(const String& str) const;	//const func, return val
	String& operator+=(const String& str);	//operator+=, return ref
	char& operator[](int n) const;
	bool operator==(const String& str) const;//only one parameter

	int size() const;
	const char* c_str() const;	//convert string to char*
	
private:
	char* data;
	int length;
};

String::String(const char* str)
{
	//first judge null, the length is 0 however data isn't because need a '\0'
	if (nullptr == str) {
		length = 0;	//length not include '\0'
		data = new char[1];
		*data = '\0';
	}
	else {
		length = strlen(str);
		data = new char[length + 1];
		strcpy(data, str);	//must use strcpy, would copy '\0' in ori str
	}
}

String::String(const String& str)
{
	//deep copy, need not use delete, because it's constructor and the obj doesn't exist first
	length = str.size();
	data = new char[length + 1];
	strcpy(data, str.c_str());
}

String::~String()
{
	delete[] data;
	data = nullptr;
	length = 0;
}

//可以认为，资源管理类的赋值运算符的套路里，都要先delete自己，因为自己即将指向其他对象了
String& String::operator=(const String& str)
{
	if (*this == str) return *this;	//1.solve self-assignment， 赋值运算符都要先判断这个
	delete[] data;	//2.delete ori data,不需要判空，以为走到构造函数的话势必构造成功，构造成功说明new成功

	length = str.size();
	data = new char[length + 1];
	strcpy(data, str.c_str());//3.deep copy

	return *this;	//4.return *this
}

//加运算符肯定返回一个右值
String String::operator+(const String& str) const
{
	//create space for new obj, copy two str, return new obj
	String newString;
	newString.length = length + str.size();
	newString.data = new char[newString.length + 1];//这个构造函数中一样，给‘\0’保留空间
	strcpy(newString.data, data);
	strcat(newString.data, str.data);	//stcat would cover dest str's '\0'
	return newString;
}

String& String::operator+=(const String& str)
{
	//create new space, copy two str, delete ori space, assign to new space, return ref
	length += str.size();
	char* newdata = new char[length + 1];
	strcpy(newdata, data);
	strcat(newdata, str.c_str());	//stcat would cover dest str's '\0'
	delete[] data;
	data = newdata;
	return *this;
}

char& String::operator[](int n) const
{
	if (n >= length)
		return data[length - 1];	//overstep the boundary, return last char(not '\0')
	else
		return data[n];
}

bool String::operator==(const String& str) const
{
	if (length != str.size())
		return false;
	return !strcmp(data, str.c_str());
}

int String::size() const
{
	return length;
}

const char* String::c_str() const
{
	return data;
}

int main()
{
	char a[] = "Hello", b[] = "World!";
	String s1(a), s2(b);
	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;
	s1 += s2;
	cout << s1.c_str() << endl;
	s1 = s2;
	cout << s1.c_str() << endl;
	cout << (s1 + s2).c_str() << endl;
	cout << s1.size() << endl;
	cout << s1[1] << endl;

	if (s1 == s2)
		cout << "相等" << endl;
}




















