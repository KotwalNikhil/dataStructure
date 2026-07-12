// Write your own AVL implementation in c++

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node* right;
    int height; // height is added on BST node

    Node(int val):data(val), left(nullptr), right(nullptr), height(1)
    {}
};

class AVL
{
    Node* root_;

private:

    // height
    void updateHeight(Node* root)
    {
        if(!root) return;
        root->height = 1 + max(height(root->left), height(root->right)); 
    }

    int height(Node* node)
    {
        return node ? node->height : 0;
    }

    int balance(Node* root)
    {
        if(!root) return 0;
        return height(root->left) - height(root->right);
    }

    Node* RotateToLeft(Node* root)
    {
        Node* rc = root->right;
        Node* orphan = rc->left;
        rc->left = root;
        root->right = orphan;
        updateHeight(root);
        updateHeight(rc);

        return rc;
    }

    Node* RotateToRight(Node* root)
    {
        Node* rc = root->left;
        Node* orphan = rc->right;
        rc->right = root;
        root->left = orphan;
        updateHeight(root);
        updateHeight(rc);

        return rc;
    }

    Node* rotateIfNeed(Node* root)
    {
        if(balance(root) > 1)
        {
            if(balance(root->left) >= 0)
            {
                root = RotateToRight(root);
            }
            else {
                root->left = RotateToLeft(root->left);
                root = RotateToRight(root);
            }
        }
        else if(balance(root) < -1){
            if(balance(root->right) <= 0)
            {
                root = RotateToLeft(root);
            }
            else{
                root->right = RotateToRight(root->right);
                root = RotateToLeft(root);
            }
        }

        return root;
    }

    // Time complexity is O(logn) and O(logn) in worst case too as tree is rotated to balance on each insert and delete
    Node* insertUtil(Node* root, int val)
    {
        if(!root)
        {
            return new Node(val);
        }

        if(val < root->data)
            root->left = insertUtil(root->left, val);
        else if(val > root->data) // This will not allow duplicate entry
            root->right = insertUtil(root->right, val);
        
        updateHeight(root);
        root = rotateIfNeed(root);
        return root;
    }


    // Time complexity is O(logn) and O(logn) in worst case as AVL tree
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
        if(root == nullptr)
            return nullptr;

        if(!root->left)return root;
        return miniUtil(root->left);
    }

    Node* maxiUtil(Node* root)
    {
        if(root == nullptr)
            return nullptr;

        if(!root->right)return root;
        else return maxiUtil(root->right);
    }

    void deleteTree(Node* root)
    {
        if(!root) return;
        deleteTree(root->left);
        deleteTree(root->right);
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

    // delete is updated to rotate and make tree balance on each delete
    Node* deleteNode(Node* root, int key)
    {
        if(root == nullptr)
            return nullptr;

        if(key < root->data)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->data){
            root->right = deleteNode(root->right, key);
        }
        else // root == key
        {
            // if root is a leaf node
            if(root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }

            // If root has a single child
            else if(!root->left ^ !root->right)
            {
                Node* temp;
                if(root->left)
                {
                    temp = root->left;
                }
                else 
                {
                    temp = root->right;
                    
                }
                delete root;
                return temp;
            }

            // if both childs are present then replace with either successor or predecessor
            // find successor
            Node* succ = successor(root, root->data);
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }

        updateHeight(root);
        return rotateIfNeed(root);
    }


public:
    AVL():root_(nullptr){}
    ~AVL()
    {
        deleteTree(root_);
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

    void deletePublic(int key)
    {
        root_ = deleteNode(root_, key);
    }
};

int main()
{
    AVL tree;
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);

    cout<<endl;
    tree.levelOrder();
    cout<<endl;
    
    cout<<"hello";
}
