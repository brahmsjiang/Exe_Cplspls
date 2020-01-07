#pragma once

#include <utility>
#include <iostream> 

using namespace std;

class shared_count
{
public:
    shared_count() noexcept
        : count_(1) {}

    void add_count() noexcept
    {
        ++count_;
    }
    long reduce_count() noexcept
    {
        return --count_;
    }
    long get_count() const noexcept
    {
        return count_;
    }

private:
    long count_;
};

template <typename T>
class smart_ptr
{
public:
    template <typename U>
    friend class smart_ptr;

    explicit smart_ptr(T* ptr = nullptr)
        : ptr_(ptr)
    {
        if (ptr) {
            shared_count_ = new shared_count();
        }
    }

    ~smart_ptr()
    {
        if (ptr_ && !shared_count_->reduce_count()) {
            delete ptr_;
            delete shared_count_;
        }
    }

    smart_ptr(const smart_ptr& other)
    {
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    template <typename U>
    smart_ptr(const smart_ptr<U>& other) noexcept
    {
        cout << "template <typename U> smart_ptr(const smart_ptr<U>& other)" << endl;
        ptr_ = other.ptr_;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    template <typename U>
    smart_ptr(smart_ptr<U>&& other) noexcept
    {
        cout << "template <typename U> smart_ptr(smart_ptr<U>&& other)" << endl;
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.ptr_ = nullptr;
        }
    }

    template <typename U>
    smart_ptr(const smart_ptr<U>& other, T* ptr) noexcept
    {
        ptr_ = ptr;
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }

    smart_ptr& operator=(smart_ptr rhs) noexcept
    {
        cout << "smart_ptr& operator=(smart_ptr rhs)" << endl;
        rhs.swap(*this);
        return *this;
    }

    T* get() const noexcept
    {
        return ptr_;
    }

    long use_count() const noexcept
    {
        if (ptr_) {
            return shared_count_->get_count();
        }
        else {
            return 0;
        }
    }

    void swap(smart_ptr& rhs) noexcept
    {
        swap(ptr_, rhs.ptr_);
        swap(shared_count_, rhs.shared_count_);
    }

    T& operator*() const noexcept
    {
        cout << "T& operator*() const" << endl;
        return *ptr_;
    }

    T* operator->() const noexcept
    {
        cout << "T* operator->() const" << endl;
        return ptr_;
    }

    operator bool() const noexcept
    {
        cout << "operator bool() const" << endl;
        return ptr_;
    }

private:
    T* ptr_;
    shared_count* shared_count_;
};

