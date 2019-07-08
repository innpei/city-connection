#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>
#include <sstream>


using namespace std;

struct Edge
{
    string source;
    string dest;
    int weight;
};

struct Subset
{
    string parent;
    int rank;
};


class Graph
{
public:
    int V, E;
    Edge* edge;
};

//----------------------------------------------------------------------------------------------------------------------

///save data from csv file
vector<pair<string, vector<double>>> SaveData()
{


    ifstream inFile("C:\\Users\\msalm\\Desktop\\file.csv");
    vector<pair<string, vector<double>>> all_info;

    string city, s, d, line;
    double shirota, dolgota;

    while(getline(inFile, line))
    {
        stringstream ss(line);
        getline(ss, city, ',');
        getline(ss, s, ',');
        getline(ss, d);
        shirota = stod(s);
        dolgota = stod(d);

        pair<string, vector<double>> p;
        vector<double> coordinates;
        coordinates.push_back(shirota);
        coordinates.push_back(dolgota);
        p = make_pair(city, coordinates);
        all_info.push_back(p);
    }

    return all_info;
}

vector<pair<string, vector<double>>> info = SaveData();


Graph* createGraph(int v,int e)
{
    Graph* graph = new Graph;
    graph->V = v;
    graph->E = e;
    graph->edge = new Edge[e];
    return graph;

}
