// Write your own string implementation in c++

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node* right;

    Node(int val):data(val), left(nullptr), right(nullptr)
    {}
};

class BST
{
    Node* root_;

private:

    // Time complexity is O(logn) and O(n) in worst case (skewed tree)
    Node* insertUtil(Node* root, int val)
    {
        if(!root)
        {
            return new Node(val);
        }

        if(val < root->data)
            root->left = insertUtil(root->left, val);
        else
            root->right = insertUtil(root->right, val);
        
        return root;
    }


    // Time complexity is O(logn) and O(n) in worst case (skewed tree)
    bool findUtil(Node* root, int val)
    {
        if(!root) return false;
        if(root->data == val)return true;
        if(root->data > val)return findUtil(root->left, val);
        else return findUtil(root->right, val);
    }

    void inOrderUtil(Node* root)
    {
        if (!root)return;
        inOrderUtil(root->left);
        cout<<root->data<<" ";
        inOrderUtil(root->right);
    }

    void preOrderUtil(Node* root)
    {
        if (!root)return;
        cout<<root->data<<" ";
        preOrderUtil(root->left);
        preOrderUtil(root->right);
    }

    void postOrderUtil(Node* root)
    {
        if (!root)return;
        postOrderUtil(root->left);
        postOrderUtil(root->right);
        cout<<root->data<<" ";
    }

    void levelOrderUtil(queue<Node*>& q)
    {
        while(!q.empty())
        {
            int N = q.size(); // useful when printing level by level.
            for(size_t i = 0; i < N; ++i)
            {
                Node* temp = q.front();
                q.pop();

                cout<<temp->data<<" ";
                if(temp->left)q.push(temp->left);
                if(temp->right)q.push(temp->right);
            }
        }
    }

    // For max go to the rightmost
    Node* miniUtil(Node* root)
    {
        if(!root->left)return root;
        return miniUtil(root->left);
    }

    void deleteNode(Node* root)
    {
        if(!root) return;
        if(root->left)deleteNode(root->left);
        if(root->right)deleteNode(root->right);
        delete root;
    }

    //height(root) = 1 + max(height(left), height(right))

    Node* successor(Node* root, int key)
    {
        Node* succ = nullptr;

        while(root)
        {
            if(key < root->data)
            {
                succ = root;
                root = root->left;
            }
            else if(key > root->data)
            {
                root = root->right;
            }
            else
            {
                if(root->right)
                    return miniUtil(root->right);

                break;
            }
        }

        return succ;
    }

    Node* predecessor(Node* root, int key)
    {
        Node* pred = nullptr;

        while(root)
        {
            if(key > root->data)
            {
                pred = root;
                root = root->right;
            }
            else if(key < root->data)
            {
                root = root->left;
            }
            else
            {
                if(root->left)
                    return maxiUtil(root->left); // TODO: complete maxiUtil method

                break;
            }
        }

        return pred;
    }


public:
    BST():root_(nullptr){}
    ~BST()
    {
        deleteNode(root_);
    }

    void insert(int val)
    {
        root_ = insertUtil(root_, val);
    }

    bool find(int val)
    {
        return findUtil(root_, val);
    }

    void inOrder()
    {
        inOrderUtil(root_);
    }

    void preOrder()
    {
        preOrderUtil(root_);
    }

    void postOrder()
    {
        postOrderUtil(root_);
    }

    void levelOrder() {
        if(!root_)return;
        queue<Node*>q;
        q.push(root_);
        levelOrderUtil(q);
    }

    Node* mini()
    {
        return miniUtil(root_);
    }

    
};

int main()
{
    BST tree;
    tree.insert(50);
    tree.insert(30);

    tree.insert(20);
    tree.insert(70);
    tree.insert(80);

    cout<<tree.find(40);
    tree.insert(60);
    cout<<tree.find(40);

    cout<<endl;
    tree.levelOrder();
    cout<<endl;

    Node* temp = tree.mini();
    cout<<temp->data<<endl;
    
    
    cout<<"hello";
}
