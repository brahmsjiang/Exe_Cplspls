#pragma once 

#include <iostream>
#include <string>
#include <iterator>

class istream_line_reader
{
public:
    class iterator
    {
    public:
        typedef ptrdiff_t difference_type;
        typedef std::string value_type;
        typedef const value_type* pointer;
        typedef const value_type& reference;
        typedef std::input_iterator_tag iterator_category;

        iterator() noexcept
            : stream_(nullptr) {}

        explicit iterator(std::istream& is)
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
		std::istream* stream_;
		std::string line_;
    };

    istream_line_reader() noexcept
        : stream_(nullptr) {}
    explicit istream_line_reader(std::istream& is) noexcept
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
	std::istream* stream_;
};

