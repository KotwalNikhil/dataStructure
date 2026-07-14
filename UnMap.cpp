// Implement your own unordered_map and test it using a custom object as a key

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template< typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;

    Node(const K& key, const V& value) : key(key), value(value), next(nullptr) {}
};

template <typename K, typename V>
class UnorderedMap
{
    vector<Node<K, V>*>buckets_;
    size_t size_; // track the number of elements stored
public:

    UnorderedMap(size_t size = 8): buckets_(size), size_(0) {}

    ~UnorderedMap()
    {
        for(auto head : buckets_)
        {
            while(head)
            {
                Node<K, V>* next = head->next;
                delete head;
                head = next;
            }
        }
    }

    Node<K, V>* insert(const K& key, const V& value);
    size_t bucketIndex(const K& key) const;
    Node<K, V>* find(const K& key);
    V& operator [](const K& key);

};

int main()
{
    UnorderedMap<int, string>mp;
}