#include <iostream>
#include <map>
#include <string>
#include <climits>

using namespace std;

const int MAX_DISTANCE = INT_MAX;

class Graph {
private:
    int **adjacencyMatrix;
    int vertexCount;
    int edgeCount;
    map<string, int> cityIndices;
    map<int, string> cityNames;

    void addEdge(string city1, string city2, int distance) {
        adjacencyMatrix[cityIndices[city1]][cityIndices[city2]] = distance;
        adjacencyMatrix[cityIndices[city2]][cityIndices[city1]] = distance;
    }

    int getMinimumKeyIndex(int key[], bool mst[]) {
        int minKey = INT_MAX;
        int minIndex = -1;
        for (int v = 0; v < vertexCount; ++v) {
            if (!mst[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

public:
    Graph() {
        vertexCount = 0;
        edgeCount = 0;
        adjacencyMatrix = nullptr;
    }

    ~Graph() {
        if (adjacencyMatrix != nullptr) {
            for (int i = 0; i < vertexCount; ++i)
                delete[] adjacencyMatrix[i];
            delete[] adjacencyMatrix;
        }
    }

    void initializeGraph(int V, int E) {
        vertexCount = V;
        edgeCount = E;

        adjacencyMatrix = new int*[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            adjacencyMatrix[i] = new int[vertexCount];
            for (int j = 0; j < vertexCount; j++)
                adjacencyMatrix[i][j] = 0;
        }

        cout << "Add cities in order: " << endl;
        for (int i = 0; i < vertexCount; i++) {
            string cityName;
            cin >> cityName;
            cityIndices.insert(make_pair(cityName, i));
            cityNames.insert(make_pair(i, cityName));
        }

        cout << "Add the " << edgeCount << " edges" << endl;

        for (int i = 0; i < edgeCount; i++) {
            string city1, city2;
            int distance;
            cout << "City 1: ";
            cin >> city1;
            cout << "City 2: ";
            cin >> city2;
            cout << "Distance: ";
            cin >> distance;
            addEdge(city1, city2, distance);
        }
    }

    void displayGraph() {
        cout << "\nAdjacency Matrix of the graph:" << endl;
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                cout << adjacencyMatrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void findMinimumSpanningTree() {
        int parent[vertexCount];
        int key[vertexCount];
        bool mst[vertexCount];

        for (int i = 0; i < vertexCount; i++) {
            key[i] = INT_MAX;
            mst[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < vertexCount - 1; count++) {
            int minKeyIndex = getMinimumKeyIndex(key, mst);
            mst[minKeyIndex] = true;

            for (int v = 0; v < vertexCount; v++) {
                if (adjacencyMatrix[minKeyIndex][v] != 0 && !mst[v] && adjacencyMatrix[minKeyIndex][v] < key[v]) {
                    parent[v] = minKeyIndex;
                    key[v] = adjacencyMatrix[minKeyIndex][v];
                }
            }
        }

        cout << "\n\nMinimum Spanning Tree (MST) of the given graph is: \n" << endl;
        cout << "\nEdge \t\t Weight\n";
        int mstCost = 0;
        for (int i = 1; i < vertexCount; i++) {
            cout << cityNames[parent[i]] << " <-> " << cityNames[i] << " \t " << adjacencyMatrix[i][parent[i]] << endl;
            mstCost += adjacencyMatrix[i][parent[i]];
        }
        cout << "\nTotal cost of the MST: " << mstCost << endl;
    }
};

int main() {
    Graph g;
    int choice, V, E;

    do {
        cout << "\n**** MENU ****" << endl;
        cout << "1. Create Graph" << endl;
        cout << "2. Display Graph" << endl;
        cout << "3. Find Minimum Spanning Tree" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter number of vertices: ";
                cin >> V;
                cout << "Enter number of edges: ";
                cin >> E;
                g.initializeGraph(V, E);
                break;
            case 2:
                g.displayGraph();
                break;
            case 3:
                g.findMinimumSpanningTree();
                break;
            case 4:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 4);

    return 0;
}















Kunal; 

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> vis(V, 0);
        pq.push({0, 0});
        int sum = 0;
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;

            if (vis[node] == 1)
                continue;
            
            vis[node] = 1;
            sum += wt;
            for (auto it : adj[node]) {
                int adjNode = it[0];
                int edWt = it[1];
                if (!vis[adjNode]) {
                    pq.push({edWt, adjNode});
                }
            }
        }
        return sum;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> edges;
    cout << "Enter the edges (node1 node2 weight):" << endl;
    for (int i = 0; i < E; i++) {
        int node1, node2, weight;
        cout << "Edge " << i + 1 << ": ";
        cin >> node1 >> node2 >> weight;
        edges.push_back({node1, node2, weight});
    }

    cout << "Edges entered:" << endl;
    for (const auto &edge : edges) {
        for (int val : edge) {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<vector<int>> adj[V];
    for (auto it : edges) {
        vector<int> tmp(2);
        tmp[0] = it[1];
        tmp[1] = it[2];
        adj[it[0]].push_back(tmp);

        tmp[0] = it[0];
        tmp[1] = it[2];
        adj[it[1]].push_back(tmp);
    }

    Solution obj;
    int sum = obj.spanningTree(V, adj);
    cout << "The sum of all the edge weights: " << sum << endl;

    return 0;
}


