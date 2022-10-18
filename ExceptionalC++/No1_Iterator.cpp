#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstring>

using namespace std;

class Date
{
public:
	Date(int m=0, int d=0, int y=0): mo(m), da(d), yr(y) {}
	Date(const string& str)
	{
		init(str);
	}
	Date(char* str)
	{
		init(string(str));
	}


	bool operator==(const Date& dt)
	{
		cout << "enter operator==(const Date& dt)" << endl;
		return (mo == dt.mo) && (da == dt.da) && (yr == dt.yr);
	}
	/* */
	bool operator==(const char* str)
	{
		cout << "enter bool operator==(const char* str)" << endl;
		return operator==(Date(str));
	}

	friend istream& operator>>(istream& is, Date& dt);
	friend ostream& operator<<(ostream& os, const Date& dt);

private:
	void init(const string& str)
	{
		char* cstr = new char[strlen(str.c_str()) + 1];
		strcpy(cstr, str.c_str());
		vector<string> res;
		char* temp = strtok(cstr, "/");
		while (temp != NULL)
		{
			res.push_back(string(temp));
			temp = strtok(NULL, "/");
		}
		delete[] cstr;

		mo = atoi(res[0].c_str());
		da = atoi(res[1].c_str());
		yr = atoi(res[2].c_str());
	}

	int mo;
	int da;
	int yr;
};


istream& operator>>(istream& is, Date& dt)
{
	is >> dt.mo >> dt.da >> dt.yr;
	return is;
}
ostream& operator<<(ostream& os, const Date& dt)
{
	os << dt.mo << '/' << dt.da << '/' << dt.yr;
	return os;
}

bool test_implicit_conver0(Date& ld, const Date& rd)
{
	return ld == rd;
}

/* error, if no mem bool operator==(const char* str) in func, Date tmp cannot know how to implicit conversion*/
bool test_implicit_conver1(Date& ld, const char* cstr)
{
	return ld == cstr;
}


int main(int argc, char* argv[])
{
	Date tmp;
	cout << "compare: " << (tmp == "0/0/0") << endl;
	cout << "test_implicit_conver0: " << test_implicit_conver0(tmp, "0/0/1") << endl;
	cout << "test_implicit_conver1: " << test_implicit_conver1(tmp, "0/0/0") << endl;


	Date date0("01/01/95");
	cout << date0 << endl;
	Date date1(string("02/02/96"));
	cout << date1 << endl;


	vector<Date> vdate;
	copy(istream_iterator<Date>(cin), istream_iterator<Date>(), back_inserter(vdate));
	for (Date curdate : vdate)
	{
		cout << curdate << endl;
	}

	vector<Date>::iterator first = find(vdate.begin(), vdate.end(), Date("01/01/95"));
	vector<Date>::iterator last = find(vdate.begin(), vdate.end(), "1/2/3");
	*last = "12/30/95";	//may undefined behav

	copy(first, last, ostream_iterator<Date>(cout, "\n"));
	vdate.insert(--vdate.end(), "99/99/99");//may undefined behav
	vector<int> vint = {1,2,3,4};
	//vdate.insert(--vint.end(), 3);//compile err
	
	//vdate.insert(--vdate.end(), TodayDate());
	//copy(first, last, ostream_iterator<Date>(cout, "\n"));



	return 0;
}