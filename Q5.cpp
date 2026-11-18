#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int data;
    int coins;
    Node *left;
    Node *right;

    Node(int d, int c)
    {
        data = d;
        coins = c;
        left = right = nullptr;
    }
};

class SimpleTree
{
public:
    Node *root;
    vector<int> bestpath;
    SimpleTree() { root = new Node(1, 5); }

    void insertLeft(int parent, int key, int coins)
    {
        Node *temp = search(root, parent);
        if (!temp)
            return;
        if (!temp->left)
            temp->left = new Node(key, coins);
    }
    void insertRight(int parent, int key, int coins)
    {
        Node *temp = search(root, parent);
        if (!temp)
            return;
        if (!temp->right)
            temp->right = new Node(key, coins);
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

    void findRoutes(Node *node, int &count)
    {
        if (!node)
        {
            return;
        }
        if (!node->left && !node->right)
        {
            count++;
            return;
        }

        findRoutes(node->left, count);
        findRoutes(node->right, count);
    }

    void findBest(Node *node, int coins, int &max, vector<int> path)
    {
        if (!node)
            return;
        path.push_back(node->data);
        coins += node->coins;
        if (!node->left && !node->right)
        {
            if (max < coins)
            {
                max = coins;
                bestpath = path;
            }
        }

        findBest(node->left, coins, max, path);
        findBest(node->right, coins, max, path);
    }
};

int main()
{
    SimpleTree cave;
    cave.insertLeft(1, 2, -3);
    cave.insertRight(1, 3, 4);
    cave.insertLeft(2, 4, 6);
    cave.insertRight(2, 5, 2);
    cave.insertRight(3, 6, -2);
    cave.insertLeft(5, 7, 9);
    cave.insertLeft(6, 8, 3);
    cave.insertRight(6, 9, 1);
    cave.insertLeft(8, 10, -1);

    int routes = 0;

    cave.findRoutes(cave.root, routes);
    cout << routes << " routes, ";
    int max = -9999;
    vector<int> temp;
    cave.findBest(cave.root, 0, max, temp);
    cout << "Best route: ";
    for (int i = 0; i < cave.bestpath.size(); i++)
    {
        cout << cave.bestpath[i] << " ";
    }
    cout << "with " << max << " coins";

    return 0;
}