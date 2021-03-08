#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class istream_line_reader
{
public:
    class iterator
    {
    public:
        typedef ptrdiff_t difference_type;
        typedef string value_type;
        typedef const value_type* pointer;
        typedef const value_type& reference;
        typedef input_iterator_tag iterator_category;

        iterator() noexcept
            : stream_(nullptr) {}

        explicit iterator(istream& is)
            : stream_(&is)
        {
            ++*this; //operator priority from right to left, '++' and '*' seems the same
        }

        reference operator*() const noexcept
        {
            return line_;
        }
        pointer operator->() const noexcept
        {
            return &line_;
        }
        iterator& operator++()
        {
            getline(*stream_, line_);
            if (!*stream_) {
                stream_ = nullptr;
            }
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++*this;
            return temp;
        }
        bool operator==(const iterator& rhs) const noexcept
        {
            return stream_ == rhs.stream_;
        }
        bool operator!=(const iterator& rhs) const noexcept
        {
            return !operator==(rhs);
        }

    private:
        istream* stream_;
        string line_;
    };

    istream_line_reader() noexcept
        : stream_(nullptr) {}
    explicit istream_line_reader(istream& is) noexcept
        : stream_(&is) {}

    iterator begin()
    {
        return iterator(*stream_);
    }
    iterator end() const noexcept
    {
        return iterator();
    }

private:
    istream* stream_;
};

int main(int argc, char* argv[])
{
    vector<int> v1{ 1,2,3,4,5 };
    vector<int> v2;
    copy(v1.begin(), v1.end(), back_inserter(v2));

    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
}