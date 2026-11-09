// Question 1

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
        {
            return new Node(key);
        }

        if (node->data == key)
        {
            cout << "Already issued: " << key << endl;
            return node;
        }

        if (key < node->data)
        {
            node->left = insertBST(node->left, key);
        }
        else
            node->right = insertBST(node->right, key);

        return node;
    }

    void inorder(Node *node, int Arr[], int &i)
    {
        if (!node)
            return;
        inorder(node->left, Arr, i);
        Arr[i++] = node->data;
        inorder(node->right, Arr, i);
    }

    void preorder(Node *node, int Arr[], int &i)
    {
        if (!node)
            return;
        Arr[i++] = node->data;
        preorder(node->left, Arr, i);
        preorder(node->right, Arr, i);
    }
};

bool isBackupSafe(int Arr1[], int Arr2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (Arr1[i] != Arr2[i])
            return false;
    }
    return true;
}

void display(int Arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << Arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    BST A, B;
    int size = 8;
    int CallingList[size] = {0}, BackupList[size] = {0}, BackupList2[size] = {0};

    cout << "Input: ";
    for (int i = 0; i < size + 1; i++)
    {
        int key;
        cin >> key;
        A.root = A.insertBST(A.root, key);
    }

    int temp = 0;
    A.inorder(A.root, CallingList, temp);
    temp = 0;
    A.preorder(A.root, BackupList, temp);

    for (int i = 0; i < size; i++)
    {
        B.root = B.insertBST(B.root, BackupList[i]);
    }

    temp = 0;
    B.preorder(B.root, BackupList2, temp);

    bool isSafe = isBackupSafe(BackupList2, BackupList, size);

    cout << "Calling List: ";
    display(CallingList, size);
    cout << "BackupList: ";
    display(BackupList, size);

    if (isSafe)
    {
        cout << "Backup is safe.";
    }
    else
    {
        cout << "Backup is wrong.";
    }
    return 0;
}