#include <iostream>
#include <vector>
#include <limits>
#include <numeric>

using namespace std;

class Node
{
public:
    int key;
    double probability;
    Node *left;
    Node *right;

    Node(int k, double p) : key(k), probability(p), left(nullptr), right(nullptr) {}
};

Node *optimal_bst(const vector<int> &keys, const vector<double> &probabilities)
{
    int n = keys.size();
    vector<vector<double>> cost(n, vector<double>(n, 0));
    vector<vector<Node *>> root(n, vector<Node *>(n, nullptr));

    for (int i = 0; i < n; ++i)
    {
        cost[i][i] = probabilities[i];
        root[i][i] = new Node(keys[i], probabilities[i]);
    }
    for (int length = 2; length <= n; ++length)
    {
        for (int i = 0; i <= n - length; ++i)
        {
            int j = i + length - 1;
            double min_cost = numeric_limits<double>::infinity();
            for (int r = i; r <= j; ++r)
            {
                double left_cost = (r == i) ? 0 : cost[i][r - 1];
                double right_cost = (r == j) ? 0 : cost[r + 1][j];
                double total_cost = left_cost + right_cost + accumulate(probabilities.begin() + i, probabilities.begin() + j + 1, 0.0);

                if (total_cost < min_cost)
                {
                    min_cost = total_cost;
                    root[i][j] = new Node(keys[r], accumulate(probabilities.begin() + i, probabilities.begin() + j + 1, 0.0));
                    root[i][j]->left = (r > i) ? root[i][r - 1] : nullptr;
                    root[i][j]->right = (r < j) ? root[r + 1][j] : nullptr;
                }
            }
            cost[i][j] = min_cost;
        }
    }

    return root[0][n - 1];
}

void print_bst(Node *node, int level = 0)
{
    if (node != nullptr)
    {
        print_bst(node->right, level + 1);
        cout << string(4 * level, ' ') << "-> " << node->key << " (" << node->probability << ")" << endl;
        print_bst(node->left, level + 1);
    }
}

int main()
{
    vector<int> keys = {10, 20, 30, 40, 50};
    vector<double> probabilities = {0.1, 0.2, 0.3, 0.2, 0.2};

    Node *root = optimal_bst(keys, probabilities);
    print_bst(root);

    return 0;
}