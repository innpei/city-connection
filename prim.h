#include "graph.h"
#include <algorithm>

using namespace std;


// Number of vertices in the graph
int n = distance_mat().size();

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int m = 360, min_index;

    for (int v = 0; v < n; v++)
        if (!mstSet[v] && key[v] < m)
            m = key[v], min_index = v;

    return min_index;
}


// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
vector<vector<int>> Prim(vector<vector<double>> graph)
{
    vector<vector<int>> adj_mat_Prim;
    vector<int> v;
    for(int i = 0; i < distance_mat().size(); i++)
        v.push_back(0);
    for(int i = 0; i < distance_mat().size(); i++)
        adj_mat_Prim.push_back(v);


    // Array to store constructed MST
    int parent[n];

    // Key values used to pick minimum weight edge in cut
    int key[n];

    // To represent set of vertices not yet included in MST
    bool mstSet[n];

    // Initialize all keys as INFINITE
    for (int i = 0; i < n; i++)
        key[i] = 360, mstSet[i] = false;

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < n - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < n; v++)

            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    for (int i = 1; i < n; i++)
    {
        int a = min(parent[i], i);
        int b = max(parent[i], i);
        adj_mat_Prim[a][b] = 1;
    }

    return adj_mat_Prim;
}
