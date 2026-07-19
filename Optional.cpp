// implement your own optional

#include <string>
using namespace std;

template <typename T>
class Optional
{
    /*
    alignas is used so that starting mem addr satisfy the alignment requirement of T
    Because the CPU fetches memory efficiently in aligned chunks.
    Imagine the CPU reads 8 bytes at a time.
    if the double starts at 1000 the cpu will read it at one memory access
    if it starts with 1003 it would need two reads more instructions, as the value now lies in two memory blocks
    1000------1007
          1008------1015

      |------double------| 
    */
    alignas(T) unsigned char storage[sizeof(T)];
    bool has_value;
public:

    Optional()
    {
        has_value = false;
    }

    ~Optional()
    {
        if(has_value)
        {
            ptr()->~T(); // explicit desctructor on objects constructed using palcement new
        }
    }

    Optional& operator=(const T& val)
    {
        if(has_value)
        {
            *ptr() = val;
        }
        else
        {
            new (ptr()) T(val); // syntax of placement new operator
            has_value = true;
        }
        return *this;
    }

    T* ptr()
    {
        return reinterpret_cast<T*>(storage);
    }

    void reset()
    {
        if(has_value)
        {
            ptr()->~T();
            has_value = false;

        }
    }

    T& value(); // can throw if has_value is false
    bool hasvalue();
    T& operator*();
};

int main()
{
    Optional<string>o;
    o="nikhil";
    o.reset();
    o="kotwal";
}