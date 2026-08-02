#include <iostream>

template <typename T>
class SP
{
    T* ptr;
    size_t* ref_cnt;

    void decrement()
    {
        if(ref_cnt)
        {
            if(--(*ref_cnt) == 0)
            {
                delete ptr;
                delete ref_cnt;
            }
        }
    }
public:

    ~SP() {decrement();}
    // Normal constructors
    SP():ptr(nullptr), ref_cnt(nullptr){}
    explicit SP(T* ptr):ptr(ptr)
    {
        if(ptr)
        {
            ref_cnt = new size_t(1);
        }
    }

    SP(const T& val):ptr(new T(val))
    {
        ref_cnt = new size_t(1); 
    }

    //copy c
    SP(const SP& obj):ptr(obj.ptr), ref_cnt(obj.ref_cnt)
    {
        if(ref_cnt){(*ref_cnt)++;}
    }

    //copy assn opr
    SP& operator=(const SP& obj)
    {
        if(this == &obj)return *this;
        decrement();
        ptr = obj.ptr;
        ref_cnt = obj.ref_cnt;
        if(ref_cnt){(*ref_cnt)++;}
        return *this;
    }

    // move cons
    SP(SP&& obj) noexcept
        :ptr(obj.ptr), ref_cnt(obj.ref_cnt) 
    {
        obj.ptr = nullptr;
        obj.ref_cnt = nullptr;
    }

    SP& operator=(SP&& obj) noexcept // The STL relies on move operations being noexcept for certain optimizations.
    {
        if(this == &obj)return *this;
        decrement();
        ptr = obj.ptr;
        ref_cnt = obj.ref_cnt;
        obj.ptr = nullptr;
        obj.ref_cnt = nullptr;
        return *this;
    }

    T* operator->(){return ptr;} // TODO: add const versions of these
    T& operator*(){return *ptr;}

    void reset(T* ptr)
    {
        decrement();
        this->ptr = nullptr;
        this->ref_cnt = nullptr;
        this->ptr = ptr;
        if(ptr)
        {
            ref_cnt = new size_t(1);
        }
        else ref_cnt=nullptr;
    }
};

int main()
{
    SP<int>sp;
    SP<float>sp2(4.6f);
    SP<double>sp3(new double(5.6));
}