#include <iostream>
#include <climits>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
};
Node *createNode(int data)
{
    Node *newNode = new Node();
    if (!newNode)
    {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
Node *insertNode(Node *root, int data)
{
    if (root == NULL)
    {
        root = createNode(data);
        return root;
    }
    if (data <= root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else
    {
        root->right = insertNode(root->right, data);
    }
    return root;
}
void swapBinaryTree(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    Node *temp = root->left;

    root->left = root->right;
    root->right = temp;
    swapBinaryTree(root->left);
    swapBinaryTree(root->right);
}
void printInorder(Node *root)
{
    if (root)
    {
        printInorder(root->left);
        cout << root->data << " ";
        printInorder(root->right);
    }
}
int findHeight(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}
int findMinValue(Node *root)
{
    if (root == NULL)
    {
        return INT_MAX;
    }
    int minValue = root->data;
    int leftMin = findMinValue(root->left);
    int rightMin = findMinValue(root->right);
    return min(minValue, min(leftMin, rightMin));
}
int main()
{
    Node *root = NULL;
    int choice, data;
    while (true)
    {
        cout << "Binary Search Tree Operations\n";
        cout << "1. Insert Node\n";
        cout << "2. Print Inorder Traversal\n";
        cout << "3. Find Height of Tree\n";
        cout << "4. Find Minimum Value in Tree\n";
        cout << "5. Swap the positions\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter data to insert: ";
            cin >> data;
            root = insertNode(root, data);
            break;
        case 2:
            cout << "Inorder traversal of the binary search tree: ";
            printInorder(root);
            cout << endl;
            break;
        case 3:
            cout << "Height of the tree: " << findHeight(root) << endl;
            break;
        case 4:
            cout << "Minimum value in the tree: " << findMinValue(root) << endl;
            break;
        case 5:

            swapBinaryTree(root);

            cout << "Swapped Success!!" << endl;

            break;
        case 6:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}