#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int d) : data(d)
    {
        left = right = nullptr;
    }
};

int none = 0, one = 0, two = 0;

class BST
{
public:
    Node *root;
    BST() { root = nullptr; }

    Node *insertBST(Node *node, int key)
    {
        if (!node)
            return new Node(key);

        if (key < node->data)
            node->left = insertBST(node->left, key);
        else
            node->right = insertBST(node->right, key);
        return node;
    }

    int height(Node *node)
    {
        if (!node)
            return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    Node *findMin(Node *node)
    {
        if (node)
        {
            while (node->left != nullptr)
                node = node->left;
        }
        return node;
    }

    Node *deleteBST(Node *node, int key)
    {
        if (!node)
        {
            cout << key << ": Code not found\n";
            return nullptr;
        }
        if (key < node->data)
        {
            node->left = deleteBST(node->left, key);
        }
        else if (key > node->data)
        {
            node->right = deleteBST(node->right, key);
        }
        else
        {
            if (!node->right && !node->left)
            {
                none++;
                delete node;
                return nullptr;
            }

            if (!node->right)
            {
                one++;
                Node *temp = node->left;
                delete node;
                return temp;
            }

            if (!node->left)
            {
                one++;
                Node *temp = node->right;
                delete node;
                return temp;
            }
            two++;
            Node *temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteBST(node->right, temp->data);
        }
        return node;
    }
};

int main()
{
    return 0;
}