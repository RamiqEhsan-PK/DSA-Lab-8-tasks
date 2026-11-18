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

    Node *deleteMin(Node *node)
    {
        if (!node->left)
        {
            Node *rightChild = node->right;
            delete node;
            return rightChild;
        }
        node->left = deleteMin(node->left);
        return node;
    }

    Node *deleteBST(Node *node, int key)
    {
        if (!node)
        {
            cout << key << " Code not found\n";
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
                cout << key << " no sub-branch\n";
                delete node;
                return nullptr;
            }

            if (!node->right)
            {
                one++;
                cout << key << " one sub-branch\n";
                Node *temp = node->left;
                delete node;
                return temp;
            }

            if (!node->left)
            {
                one++;
                cout << key << " one sub-branch\n";
                Node *temp = node->right;
                delete node;
                return temp;
            }

            two++;
            Node *temp = findMin(node->right);
            cout << key << " two sub-branches, replaced by " << temp->data << "\n";
            node->data = temp->data;
            node->right = deleteMin(node->right);
        }
        return node;
    }

    void printPreOrder(Node *node)
    {
        if (!node)
            return;
        cout << node->data << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
};

int main()
{
    BST tree;

    int insertValues[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    for (int val : insertValues)
    {
        tree.root = tree.insertBST(tree.root, val);
    }

    int removeValues[] = {20, 70, 30, 50, 99};
    for (int val : removeValues)
    {
        tree.root = tree.deleteBST(tree.root, val);
    }

    cout << "Remaining: ";
    tree.printPreOrder(tree.root);
    cout << "\n";

    int treeHeight = tree.height(tree.root);
    if (treeHeight > 0)
        treeHeight--;
    cout << "Height " << treeHeight << "\n";

    cout << "Kinds: none " << none << ", one " << one << ", two " << two << "\n";

    return 0;
}