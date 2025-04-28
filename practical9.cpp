#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
struct Node
{
    string keyword;
    string meaning;
    Node *left;
    Node *right;
    int height;

    Node(string key, string mean) : keyword(key), meaning(mean), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    Node *root;

    int height(Node *node)
    {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalance(Node *node)
    {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }
    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node *insert(Node *node, string keyword, string meaning)
    {
        if (node == nullptr)
            return new Node(keyword, meaning);

        if (keyword < node->keyword)
            node->left = insert(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = insert(node->right, keyword, meaning);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && keyword < node->left->keyword)
            return rightRotate(node);

        if (balance < -1 && keyword > node->right->keyword)
            return leftRotate(node);

        if (balance > 1 && keyword > node->left->keyword)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && keyword < node->right->keyword)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    Node *deleteNode(Node *root, string keyword)
    {
        if (root == nullptr)
            return root;

        if (keyword < root->keyword)
            root->left = deleteNode(root->left, keyword);
        else if (keyword > root->keyword)
            root->right = deleteNode(root->right, keyword);
        else
        {
            if (root->left == nullptr || root->right == nullptr)
            {
                Node *temp = root->left ? root->left : root->right;
                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                {
                    *root = *temp;
                }
                delete temp;
            }
            else
            {
                Node *temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    void inOrder(Node *root)
    {
        if (root != nullptr)
        {
            inOrder(root->left);
            cout << root->keyword << ": " << root->meaning << endl;
            inOrder(root->right);
        }
    }

    Node *search(Node *root, string keyword)
    {
        if (root == nullptr || root->keyword == keyword)
            return root;

        if (keyword < root->keyword)
            return search(root->left, keyword);
        else
            return search(root->right, keyword);
    }

public:
    AVLTree() : root(nullptr) {}
    void insertEntry(string keyword, string meaning)
    {
        root = insert(root, keyword, meaning);
    }

    void deleteEntry(string keyword)
    {
        root = deleteNode(root, keyword);
    }
    void searchKeyword(string keyword)
    {
        Node *result = search(root, keyword);
        if (result)
        {
            cout << "Found: " << result->keyword << ": " << result->meaning << endl;
        }
        else
        {
            cout << "Keyword not found!" << endl;
        }
    }

    void updateEntry(string keyword, string newMeaning)
    {
        Node *result = search(root, keyword);
        if (result)
        {
            result->meaning = newMeaning;
            cout << "Updated: " << result->keyword << ": " << result->meaning << endl;
        }
        else
        {
            cout << "Keyword not found!" << endl;
        }
    }
    void displayDictionary()
    {
        cout << "Dictionary Entries (Sorted Order):" << endl;
        inOrder(root);
    }
};
int main()
{
    AVLTree dictionary;

    dictionary.insertEntry("Algorithm", "A step-by-step procedure for solving a problem.");
    dictionary.insertEntry("Binary Search", "An efficient algorithm for finding an item from a sorted list of items.");
    dictionary.insertEntry("Data Structure", "A particular way of organizing and storing data.");

    cout << "Initial Dictionary:" << endl;
    dictionary.displayDictionary();

    cout << "\nSearching for 'Algorithm':" << endl;
    dictionary.searchKeyword("Algorithm");

    cout << "\nUpdating 'Binary Search':" << endl;
    dictionary.updateEntry("Binary Search", "A search algorithm that finds the position of a target value.");

    cout << "\nDeleting 'Data Structure':" << endl;
    dictionary.deleteEntry("Data Structure");

    cout << "\nUpdated Dictionary:" << endl;
    dictionary.displayDictionary();

    return 0;
}