// Write your own string implementation in c++

#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
    char* data;
    size_t size;
    size_t capacity;

public:
    MyString():size(0), capacity(0) {
        data = new char[1];
        data[0] = '\0';
    }

    explicit MyString(const char* str) {
        if (str) {
            size = strlen(str);
            capacity = size;
            data = new char[size+1];
            memcpy(data, str, size+1);
            return;
        }
        data = new char[1];
        data[0] = '\0';
        size = capacity = 0;
        
    }

    ~MyString()
    {
        delete[] data;
    }

    size_t sizeFun() const
    {
        return size;
    }

    const char* c_str() const
    {
        return data;
    }

    const char& at(size_t index) const
    {
        if(index >= size)throw std::out_of_range("index out of bound");
        return data[index];
    }

    bool operator==(const MyString& obj) const
    {
        if(size != obj.sizeFun())return false;
        for(size_t i=0;i<size;++i)
        {
            if(data[i] != obj.at(i))return false;
        }

        return true;
    }

    //copy const
    MyString(const MyString& obj)
    {
        data = new char[obj.sizeFun() + 1];
        memcpy(data, obj.c_str(), obj.sizeFun()+1);
        size = obj.sizeFun();
        capacity = size;
    }


    //copy assgn opr
    MyString& operator=(const MyString& obj)
    {
        if (this == &obj)return *this;
        delete[] data;
        data = new char[obj.sizeFun() + 1];
        memcpy(data, obj.c_str(), obj.sizeFun()+1);
        size = obj.sizeFun();
        capacity = size;
        return *this;
    }

    //move const
    MyString(MyString&& obj):data(obj.data), size(obj.size), capacity(size)
    {
        obj.data = nullptr;
        obj.size = 0;
        obj.capacity = 0;
    }

    //move assgn opr
    MyString& operator=(MyString&& obj)
    {
        if (this == &obj)return *this;
        delete[] data;

        data = obj.data;
        size = obj.size;
        capacity = size;
        obj.data = nullptr;
        obj.size = 0;
        obj.capacity = 0;
        return *this;
    }
};


int main()
{
    
    MyString s("Hello");
    MyString str;
    MyString s2(nullptr);
    
    cout<<"hello";
}
