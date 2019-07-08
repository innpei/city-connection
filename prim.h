#include "graph.h"
#include <algorithm>

using namespace std;

//int n = distance_mat(info).size();
int n = 300;

int minKey(vector<double> key, vector<bool> mstSet) // find a vertex with min key (edge with min weight
{
    double m = 360;
    int min_index = 0;

    for (int i = 0; i < n; i++)
        if (!mstSet[i] && key[i] < m)
        {
            m = key[i];
            min_index = i;
        }
    return min_index;
}

vector<vector<int>> Prim(vector<vector<double>> graph)
{
    vector<vector<int>> adj_mat_Prim;
    vector<int> v;
    for(int i = 0; i < n; i++)
        v.push_back(0);
    for(int i = 0; i < n; i++)
        adj_mat_Prim.push_back(v);

    vector<int> source(n); // construct MST
    vector<double> key(n);
    vector<bool> mstSet(n);

    for (int i = 0; i < n; i++)
    {
        key[i] = 360;
        mstSet[i] = false;
    }

    key[0] = 0;
    source[0] = -1;

    for (int i = 0; i < n - 1; i++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int j = 0;j < n; j++)
            if (graph[u][j] != 0 && !mstSet[j] && graph[u][j] < key[j])
            {
                source[j] = u;
                key[j] = graph[u][j];
            }
    }

    for (int i = 1; i < n; i++)
    {
        int a = min(source[i], i);
        int b = max(source[i], i);
        adj_mat_Prim[a][b] = 1;
    }

    return adj_mat_Prim;
}
