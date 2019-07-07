#include <iostream>
#include "boruvka.h"

using namespace std;

int main(){

    for(auto& p: info)
        cout << p.first << endl;

    vector<vector<double>> adjusted_mat = distance_mat(info);


//    for(int i=0;i<adjusted_mat.size();++i)
//    {
//        for(int j=0;j<adjusted_mat[0].size();++j)
//            cout << adjusted_mat[i][j]<<' ';
//        cout << endl;
//    }


    ///Create graph
    Graph* g = createGraph(info.size(),num_edges);

    int index = 0;

    for(int i=0; i<info.size();++i)
    {
        for (int j=0; j<info.size();++j)
        {
            if (adjusted_mat[i][j] != 0)
            {
                g->edge[index].source = i;
                g->edge[index].dest = j;
                g->edge[index].weight = adjusted_mat[i][j];
                ++index;
            }
        }
    }

    vector<vector<int>> result = Boruvka(g);


    ofstream File;
    File.open("adj_mat.txt");
    for(int i=0; i<info.size(); ++i)
    {
        for(int j=0; j<info.size(); ++j)
            File << result[i][j] << ' ';
        File << endl;
    }

}
