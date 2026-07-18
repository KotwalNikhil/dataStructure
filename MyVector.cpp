
// Implement your own vector class

#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;

template <typename T>
class MyVector
{
    T* data_;
    size_t capacity_;
    size_t size_;

public:
    MyVector() : data_(nullptr), capacity_(0), size_(0) {}

    explicit MyVector(size_t capacity)
        : data_(capacity > 0 ? new T[capacity] : nullptr), capacity_(capacity), size_(0) {}

    ~MyVector() { delete[] data_; }

    MyVector(const MyVector& other)
        : data_(other.capacity_ > 0 ? new T[other.capacity_] : nullptr),
          capacity_(other.capacity_),
          size_(other.size_)
    {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    MyVector& operator=(const MyVector& other)
    {
        if (this != &other) {
            MyVector temp(other);
            swap(temp);
        }
        return *this;
    }

    MyVector(MyVector&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_), size_(other.size_)
    {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    MyVector& operator=(MyVector&& other) noexcept
    {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            capacity_ = other.capacity_;
            size_ = other.size_;

            other.data_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    void swap(MyVector& other) noexcept
    {
        using std::swap;
        swap(data_, other.data_);
        swap(capacity_, other.capacity_);
        swap(size_, other.size_);
    }

    // Follow Rule of 5

    void enlarge(int newCapacity)
    {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    void push_back(const T& val) {
        if (size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            enlarge(newCapacity);
        }

        data_[size_] = val;
        size_++;
    }

    void pop_back()
    {
        if (size_ > 0) size_--;
    }

    T& operator[](size_t idx)
    {
        // Note: operator doesn't do bound checking at() method does that
        if (idx >= size_) { throw std::out_of_range("Index out of bound"); }
        return data_[idx];
    }
};


// Note: in stl vector memory is not default constructed but assigned using opeartor new and obj const'r with placement new 
// So this version wont complile because T doesn't have a default const'r and our new T[] will fail with Order object.
class Order
{
public:
    //Order() = default; 
    Order(int) {}
};

int main()
{
    MyVector<Order> v(10);
    MyVector<int> vec;
    vec.push_back(88);
}