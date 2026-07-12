// Implement your own ordered map using AVL keep in mind that in std:: map is implemented using Red Black tree
#include <iostream>
#include <utility>

using namespace std;

template <typename KEY_TYPE, typename VALUE_TYPE>
struct Node
{
    std::pair<const KEY_TYPE, VALUE_TYPE> data;
    Node* left;
    Node* right;
    size_t height;

    Node(const KEY_TYPE& key, const VALUE_TYPE& value) : data({key, value}), left(nullptr), right(nullptr), height(1) {}
};

template<typename K, typename V>
class Map
{
Node* root;

public:
    void insert(const K& key, const V& value); // insertUtil in AVL.cpp

    void erase(const K& key); // same as deleteNode in AVL.cpp

    bool contains(const K& key) const; // use find inside

    Node* find(const K& key); // findUtil in AVL.cpp

    
    /*
        1. Find if key is present
        Exist?
            Yes->return value reference
            No-> Insert with (key and V()) and return value reference
    */
    V& operator[](const K& key);
    
    void inorder();
};