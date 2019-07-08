using namespace std;
///create distance matrix
double distance(double shirota1, double dolgota1, double shirota2, double dolgota2)
{
    double d = sqrt(pow(shirota1 - shirota2, 2) + pow(dolgota1 - dolgota2, 2));
    return d;
}

//track the max value and its position(in res) of h_min
int pickMax(vector<pair<double, vector<int>>> &h_min)
{
    int max_pos = 0;
    pair<double,vector<int>> max = h_min[0];

    for(int i = 1; i < 100; ++i)
    {
        if (h_min[i].first > max.first)
        {
            max = h_min[i];
            max_pos = i;
        }
    }
    return max_pos;
}


int num_edges = 0;
vector<vector<double>> distance_mat(const vector<pair<string, vector<double>>> &coord)
{

    //create empty dist_mat;
    vector<vector<double>> res(coord.size());
    for (int i = 0; i < coord.size(); ++i)
        res[i] = vector<double>(coord.size());

    for (int i = 0; i < coord.size(); ++i)
    {
        for (int j = 0; j < coord.size(); ++j)
            res[i][j] = 0;
    }
    
    for (int j = 0; j < coord.size(); ++j)
    {
        //create a vector that saves info of three minimum edges for every city
        vector<pair<double, vector<int>>> h_min;
        for (int i = 0; i < 100; ++i)
        {
            double d;
            vector<int> v;
            if(i == j)
            {
                d = distance(coord[j].second[0], coord[j].second[1], coord[100].second[0], coord[100].second[1]);
                v = {j, 100};
                res[j][100] = d;
            }

            else
            {
                d = distance(coord[j].second[0], coord[j].second[1], coord[i].second[0], coord[i].second[1]);
                v = {j, i};
                res[j][i] = d;
            }
            pair<double, vector<int>> p = make_pair(d, v);
            h_min.push_back(p);
        }
        
        num_edges+=100;

        int mp = pickMax(h_min);
        pair<double,vector<int>> m = h_min[mp];
        //finally,let's fill in our res
        for(int i = 100; i < coord.size(); ++i)
        {
            if (j == i)
                continue;
            if(j >=0 && j <= 99 && i == 100)
                continue;

            double d = distance(coord[j].second[0], coord[j].second[1], coord[i].second[0], coord[i].second[1]);
            
            if (d<m.first)
            {
                vector<int> v = {j, i};
                pair<double,vector<int>> p = make_pair(d, v);
                res[m.second[0]][m.second[1]] = 0;
                h_min[mp]=p;

                mp = pickMax(h_min);
                m = h_min[mp];
                res[j][i] = d;
            }
        }

    return res;
}
