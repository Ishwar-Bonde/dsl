#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NUM_LANDMARKS = 6;

int adjMatrix[NUM_LANDMARKS][NUM_LANDMARKS] = {0};

vector<int> adjList[NUM_LANDMARKS];
string landmarks[NUM_LANDMARKS] = {
    "College Main Gate",
    "Library",
    "Cafeteria",
    "Auditorium",
    "Sports Complex",
    "Hostel"
};

void DFS(int node, vector<bool> &visited)
{
    cout << landmarks[node] << " -> ";
    visited[node] = true;

    for (int i = 0; i < NUM_LANDMARKS; i++)
    {
        if (adjMatrix[node][i] == 1 && !visited[i])
        {
            DFS(i, visited);
        }
    }
}

void BFS(int start)
{
    queue<int> q;
    vector<bool> visited(NUM_LANDMARKS, false);
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        cout << landmarks[node] << " -> ";

        for (int neighbor : adjList[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void addEdge(int u, int v)
{
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1; 

    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

int main()
{
    addEdge(0, 1); // College Main Gate <-> Library
    addEdge(0, 2); // College Main Gate <-> Cafeteria
    addEdge(1, 3); // Library <-> Auditorium
    addEdge(2, 4); // Cafeteria <-> Sports Complex
    addEdge(3, 5); // Auditorium <-> Hostel
    addEdge(4, 5); // Sports Complex <-> Hostel

    cout << "Depth-First Search (DFS) Traversal:\n";
    vector<bool> visited(NUM_LANDMARKS, false);
    DFS(0, visited);
    cout << "END\n\n";

    cout << "Breadth-First Search (BFS) Traversal:\n";
    BFS(0);
    cout << "END\n";

    return 0;
}
