///Auxiliary methods
int find(Subset components[], int i)
{
    if (components[i].parent != i)
        components[i].parent =
                find(components, components[i].parent);

    return components[i].parent;
}

void connect(Subset components[], int comp1, int comp2)
{
    int first_root = find(components, comp1);
    int second_root = find(components, comp2);

    components[second_root].parent = first_root;
}

//----------------------------------------------------------------------------------------------------------------------

vector<vector<int>> Boruvka(Graph* g)
{
    vector<vector<int>> adj_mat(info.size());
    for(int i=0;i<info.size();++i)
        adj_mat[i]= vector<int>(info.size());

    for(int i=0; i<info.size(); ++i)
    {
        for(int j=0; j<info.size();++j)
            adj_mat[i][j]=0;
    }

    int V = g->V;
    int E = g->E;
    Subset* comps = new Subset[V];
    int* cheapest = new int[V];

    for (int i=0; i<V; ++i)
    {
        comps[i].parent = i;
        cheapest[i]=-1;
    }

    int numComps = V;
    double MSTweight = 0.;

    while (numComps > 1)
    {
        for (int i = 0; i < V; ++i)
            cheapest[i] = -1;

        //determine cheapest edge
        for (int i=0; i<E; i++)
        {
            int comp1 = find(comps,g->edge[i].source);
            int comp2 = find(comps,g->edge[i].dest);

            if (comp1 == comp2)
                continue;

            if (cheapest[comp1] == -1 ||g->edge[cheapest[comp1]].weight > g->edge[i].weight)
                cheapest[comp1] = i;

            if (cheapest[comp2] == -1 ||g->edge[cheapest[comp2]].weight > g->edge[i].weight)
                cheapest[comp2] = i;
        }

        //add to MST
        for (int i=0; i<V; i++)
        {
            if (cheapest[i] != -1)
            {
                int comp1 = find(comps, g->edge[cheapest[i]].source);
                int comp2 = find(comps, g->edge[cheapest[i]].dest);

                if (comp1 == comp2)
                    continue;
                MSTweight += g->edge[cheapest[i]].weight;
                adj_mat[g->edge[cheapest[i]].source][g->edge[cheapest[i]].dest] = 1;

                connect(comps, comp1,comp2);
                --numComps;
            }
        }
    }
    return adj_mat;
}
