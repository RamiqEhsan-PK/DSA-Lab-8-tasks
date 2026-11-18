#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int d)
    {
        data = d;
        left = right = nullptr;
    }
};

class SimpleTree
{
public:
    Node *root;
    SimpleTree() { root = new Node(1); }

    void insertLeft(int parent, int key)
    {
        Node *manager = search(root, parent);
        if (!manager)
            return;
        if (!manager->left)
            manager->left = new Node(key);
    }
    void insertRight(int parent, int key)
    {
        Node *manager = search(root, parent);
        if (!manager)
            return;
        if (!manager->right)
            manager->right = new Node(key);
    }

    Node *search(Node *node, int key)
    {
        if (!node || node->data == key)
            return node;

        Node *leftSearch = search(node->left, key);
        if (leftSearch)
            return leftSearch;
        return search(node->right, key);
    }

    void levelOrder()
    {
        queue<Node *> q;
        q.push(root);
        int level = 0;
        int maxlevel;
        while (!q.empty())
        {

            cout << "Level " << level << ": ";
            int count = q.size();
            for (int i = 0; i < count; i++)
            {
                Node *curr = q.front();
                q.pop();
                cout << curr->data << " ";

                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
            cout << endl;
            maxlevel = level;
            level++;
        }
        cout << "Height " << maxlevel << endl;
    }

    void printLeaves()
    {
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();

            if (!curr->left && !curr->right)
            {
                cout << curr->data << " ";
            }

            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
    }

    Node *findParent(Node *node, Node *child)
    {
        if (!node || node->left == child || node->right == child)
            return node;

        Node *found = nullptr;

        found = findParent(node->left, child);
        if (found)
            return found;
        return findParent(node->right, child);
    }

    void getChain(int key)
    {
        Node *child = search(root, key);
        if (!child)
            return;

        if (child == root)
        {
            cout << " " << child->data;
            return;
        }
        Node *parent = findParent(root, child);

        if (!parent)
            return;
        getChain(parent->data);
        cout << " " << child->data;
    }

    void printChain(int key)
    {
        cout << "For " << key << ": chain";
        getChain(key);
        cout << ", colleague ";

        Node *child = search(root, key);
        Node *parent = findParent(root, child);

        if (parent)
        {
            if (parent->left == child)
            {
                if (parent->right)
                    cout << parent->right->data;
                else
                    cout << "None";
            }
            else if (parent->right == child)
            {
                if (parent->left)
                    cout << parent->left->data;
                else
                    cout << "None";
            }
        }
        cout << endl;
    }
};

int main()
{

    SimpleTree Tree;

    Tree.insertLeft(1, 2);
    Tree.insertRight(1, 3);
    Tree.insertLeft(2, 4);
    Tree.insertRight(2, 5);
    Tree.insertRight(3, 6);
    Tree.insertLeft(5, 7);
    Tree.insertLeft(6, 8);
    Tree.insertRight(6, 9);
    Tree.insertLeft(8, 10);

    Tree.levelOrder();

    cout << "No one under them: ";
    Tree.printLeaves();
    cout << endl;

    Tree.printChain(10);
    Tree.printChain(5);
    return 0;
}