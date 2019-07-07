///create distance matrix
double distance(double shirota1,double dolgota1,double shirota2,double dolgota2)
{
    double d = sqrt(pow(shirota1-shirota2,2)+pow(dolgota1-dolgota2,2));
    return d;
}


//track the max value and its position(in res) of three_min
int pickMax(vector<pair<double, vector<int>>> &three_min)
{
    int max_pos = 0;
    pair<double,vector<int>> max = three_min[0];

    if (three_min[1].first > max.first)
    {
        max = three_min[1];
        max_pos=1;
    }

    if (three_min[2].first > max.first)
    {
        max = three_min[2];
        max_pos=2;
    }
    return max_pos;
}


int num_edges=0;
vector<vector<double>> distance_mat(const vector<pair<string, vector<double>>> &coord) {

    //create empty dist_mat;
    vector<vector<double>> res(coord.size());
    for (int i = 0; i < coord.size(); ++i)
        res[i] = vector<double>(coord.size());

    for (int i = 0; i < coord.size(); ++i) {
        for (int j = 0; j < coord.size(); ++j)
            res[i][j] = 0;
    }



    for (int j = 0; j < coord.size(); ++j)
    {
        //create a vector that saves info of three minimum edges for every city
        vector<pair<double, vector<int>>> three_min(3);
        for (int i = 0; i < 3; ++i)
        {
            double d = distance(coord[j].second[0], coord[j].second[1], coord[i].second[0], coord[i].second[1]);
            vector<int> v = {j,i};
            pair<double, vector<int>> p = make_pair(d, v);
            res[j][i] = d;
            three_min[i] = p;
        }

        if(j==0||j==1||j==2)
        {
            double d = distance(coord[j].second[0], coord[j].second[1], coord[3].second[0], coord[3].second[1]);
            vector<int> v = {j, 3};
            pair<double, vector<int>> p = make_pair(d, v);
            res[j][3] = d;
            three_min[j]=p;
        }

//        cout << "In three_min: ";
//        for(auto& p : three_min)
//            cout << p.first << ' ';
//        cout << endl;

        num_edges+=3;

        int mp = pickMax(three_min);
        pair<double,vector<int>> m = three_min[mp];
        //finally,let's fill in our res
        for(int i=3;i<coord.size();++i)
        {
            if (j==i)
            {
                cout << "im at myself"<<endl;
                continue;
            }

            if ((j==0||j==1||j==2) && i==3)
            {
                cout << "im at 2nd if"<<endl;
                continue;
            }


            double d = distance(coord[j].second[0], coord[j].second[1], coord[i].second[0], coord[i].second[1]);


            if (d<m.first)
            {
                vector<int> v = {j,i};
                pair<double,vector<int>> p = make_pair(d,v);
                res[m.second[0]][m.second[1]] = 0;
                three_min[mp]=p;

                mp = pickMax(three_min);
                m = three_min[mp];
                res[j][i] = d;
            }
        }

        for(auto &p: three_min)
        {
            if (res[p.second[0]][p.second[1]] == res[p.second[1]][p.second[0]])
            {
                res[p.second[1]][p.second[0]] = 0;
                --num_edges;
            }
        }
    }

    return res;
}
