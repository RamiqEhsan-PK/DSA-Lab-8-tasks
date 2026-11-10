#include <iostream>
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
        {
            node->left = insertBST(node->left, key);
        }
        else
        {
            node->right = insertBST(node->right, key);
        }
        return node;
    }

    void insert(int key)
    {
        root = insertBST(root, key);
    }

    Node *searchBST(Node *node, int key, int &out)
    {
        if (!node)
            return nullptr;
        out++;
        if (node->data == key)
            return node;

        if (key < node->data)
            return searchBST(node->left, key, out);
        return searchBST(node->right, key, out);
    }

    void inorder(Node *node, int arr[], int &i)
    {
        if (!node)
            return;

        inorder(node->left, arr, i);
        arr[i++] = node->data;
        inorder(node->right, arr, i);
    }
};

void findnearest(int &lesser, int &greater, int arr[], int key)
{
    int curr = 0;
    for (; curr < 9; curr++)
    {
        if (arr[curr] > key)
            break;
    }

    if (curr < 9)
        greater = arr[curr];
    else
        greater = -1;

    curr = 8;
    for (; curr >= 0; curr--)
    {
        if (arr[curr] < key)
            break;
    }

    if (curr >= 0)
        lesser = arr[curr];
    else
        lesser = -1;
}

int main()
{
    int size = 9;
    cout << "Tree Input: ";
    BST Tree;
    for (int i = 0; i < size; i++)
    {
        int key;
        cin >> key;
        Tree.insert(key);
    }

    int Queries[4];
    cout << "Queries: ";
    for (int i = 0; i < 4; i++)
    {
        cin >> Queries[i];
    }

    int Sorted[9];
    int temp = 0;
    Tree.inorder(Tree.root, Sorted, temp);

    for (int i = 0; i < 4; i++)
    {
        int comparisons = 0;
        cout << Queries[i] << ": ";
        if (Tree.searchBST(Tree.root, Queries[i], comparisons))
        {
            cout << "found, " << comparisons << " comparisons\n";
        }
        else
        {
            int left, right;
            findnearest(left, right, Sorted, Queries[i]);

            cout << "Not found, " << comparisons << " comparsions, smaller ";

            if (left == -1)
                cout << "NONE";
            else
                cout << left;

            cout << ", bigger ";

            if (right == -1)
            {
                cout << "NONE.\n";
            }
            else
                cout << right << ".\n";
        }
    }
    return 0;
}