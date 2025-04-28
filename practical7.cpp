#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string, int>>> adjList;

public:
    // Add an edge between two cities with the given cost
    void addEdge(string city1, string city2, int cost) {
        adjList[city1].push_back({city2, cost});
        adjList[city2].push_back({city1, cost});
    }

    // Display the graph as adjacency list
    void displayGraph() {
        for (auto &city : adjList) {
            cout << city.first << " -> ";
            for (auto &neighbor : city.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // Depth-First Search (DFS)
    void DFS(string city, unordered_map<string, bool> &visited) {
        visited[city] = true;
        for (auto &neighbor : adjList[city]) {
            if (!visited[neighbor.first]) {
                DFS(neighbor.first, visited);
            }
        }
    }

    // Check if the graph is connected
    bool isConnected() {
        if (adjList.empty()) return false;

        unordered_map<string, bool> visited;
        for (auto &city : adjList) 
            visited[city.first] = false;

        string startCity = adjList.begin()->first;
        DFS(startCity, visited);

        for (auto &city : visited) {
            if (!city.second)
                return false;
        }
        return true;
    }
};

int main() {
    Graph g;

    g.addEdge("New York", "Los Angeles", 6);
    g.addEdge("Los Angeles", "Chicago", 4);
    g.addEdge("Chicago", "Houston", 3);
    g.addEdge("Houston", "Miami", 5);
    g.addEdge("Miami", "New York", 8);

    cout << "Flight Graph (Adjacency List): \n";
    g.displayGraph();

    if (g.isConnected()) {
        cout << "\nThe graph is connected." << endl;
    } else {
        cout << "\nThe graph is NOT connected." << endl;
    }

    return 0;
}
