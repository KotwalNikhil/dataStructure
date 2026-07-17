// Implement your own unordered_map and test it using a custom object as a key- see notebook for what things you need to use custom 
// object as a key in unordered_map

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
using namespace std;

static constexpr float loadFactor = 0.75f;

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

    UnorderedMap(size_t size = 8): buckets_(size, nullptr), size_(0) {}

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

    V& operator [](const K& key)
    {
        Node<K,V>* node = find(key);
        if(node)return node->value;
        auto it = insert(key, V());
        return it->value;
    }

    Node<K, V>* insert(const K& key, const V& value)
    {
        // Map doesn't allow duplicates
        Node<K,V>* node = find(key);
        if(node)
            return node;

        // IMP - check load factor this also tells how many collisions are there currently
        if (static_cast<float>(size_) / buckets_.size() > loadFactor)resizeBucket();
        size_t idx = bucketIndex(key, buckets_.size());
        
        // Insert at head
        Node<K,V>* temp = new Node(key, value);
        temp->next = buckets_[idx];
        buckets_[idx] = temp;
        ++size_;
        
        return buckets_[idx];
    }

    size_t bucketIndex(const K& key, size_t bucketSize) const
    {
        // if constexpr(is_integral_v<K>)
        // {
        //     return key%buckets_.size();
        // }
        // else return 0;
        return std::hash<K>{}(key) % bucketSize;
    }

    Node<K, V>* find(const K& key)
    {
        size_t idx = bucketIndex(key, buckets_.size());
        Node<K,V>* head = buckets_[idx];
        while(head)
        {
            if(head->key == key)return head;
            head = head->next;
        }
        return nullptr;
    }

    void resizeBucket()
    {
        size_t newBucketSize = 2 * buckets_.size();
        vector<Node<K,V>*>newBuckets(newBucketSize, nullptr);
        for(auto head: buckets_)
        {
            while(head)
            {
                Node<K, V>* next = head->next;
                size_t idx = bucketIndex(head->key, newBuckets.size());
                head->next  = newBuckets[idx];
                newBuckets[idx] = head;
                head = next;
            }
        }
        buckets_ = std::move(newBuckets);
    }

};

int main()
{
    UnorderedMap<int, string>mp(2);
    mp[3]="nikhil";
    mp[2]="ans";
    mp[4]="nik";
    if(mp.find(3))
    {
        cout<<"4 is present with value="<<mp.find(3)->value;
    }
}