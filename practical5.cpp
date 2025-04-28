#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string data;
    Node *left;
    Node *right;

    Node(string d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

void postOrder(Node *node)
{
    if (node == NULL)
        return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}
void deleteTree(Node *node)
{
    if (node == NULL)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main()
{
    Node *f = new Node("+");
    Node *s = new Node("-");
    Node *t = new Node("-");
    Node *fo = new Node("a");
    Node *fi = new Node("*");
    Node *si = new Node("b");
    Node *se = new Node("c");
    Node *e = new Node("/");
    Node *n = new Node("d");
    Node *te = new Node("e");
    Node *el = new Node("f");

    s->left = t;
    s->right = e;
    t->left = fo;
    t->right = fi;
    fi->left = si;
    fi->right = se;
    e->left = n;
    e->right = te;
    f->left = s;
    f->right = el;

    cout << "Post-order Traversal: ";
    postOrder(f);
    cout << endl;

    deleteTree(f);

    return 0;
}
