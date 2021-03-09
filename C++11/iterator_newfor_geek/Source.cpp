#include "istream_line_reader.h"
#include <algorithm>
#include <vector>


using namespace std;


int main(int argc, char* argv[])
{
    vector<int> v1{ 1,2,3,4,5 };
    vector<int> v2;
    copy(v1.begin(), v1.end(), back_inserter(v2));
	copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    std::string filename = "D:\\Learningproject\\Exe_Cplspls\\tmpprj\\analysis";//better to use absolute dir
    std::ifstream iftrm(filename, std::ios::binary);

    if (!iftrm.is_open()) {
        cout << "file can't open" << endl;
    }
    else {
#ifdef NEWFOR
        for (const string& line : istream_line_reader(iftrm)) {
            cout << line << endl;
        }
#else
        auto&& r = istream_line_reader(iftrm);
        for (auto it = r.begin(); it != r.end(); it++) {
            const string& line = *it;
            cout << line << endl;
        }
#endif

    }


}