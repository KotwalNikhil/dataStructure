// implement unique pointer

template<typename T>
class Upointer
{
T* data;

public:

    Upointer():data(nullptr){}
    Upointer(const T& val)
    {
        data = new T(val);
    }

    Upointer(T* ptr):data(ptr){}

    // remember to add destructor
    ~Upointer()
    {
        delete data;
    }

    Upointer(const Upointer& other) = delete;
    Upointer& operator=(const Upointer& other) = delete;

    Upointer(Upointer&& other) : data(other.data)
    {
        other.data = nullptr;
    }

    Upointer& operator=(Upointer&& other)
    {
        if(this == &other)return *this;
        delete data;
        data = other.data;
        other.data = nullptr;
        return *this;
    }

    T* operator->() const{
        return data;
    }

    T& operator*() const {
        return *data;
    }

    T* get() const {
        return data;
    }

    void reset(const T& ptr = nullptr)
    {
        delete data;
        data = ptr;
    }
};

int main()
{
    Upointer<int> ptr(4);
    
}