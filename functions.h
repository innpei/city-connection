// leave only near cities
vector<vector<double>> near(const vector<vector<double>> &matrix)
{
    vector<vector<double>> newMatrix = matrix;
    vector<double> row;
    double thirdMin;

    for (int i = 0; i < matrix.size(); i++)
    {
        row = matrix[i];
        sort(row.begin(), row.end());
        thirdMin = row[3];
        for (int j = 0; j < row.size(); j++)
            if (matrix[i][j] > thirdMin)
                newMatrix[i][j] = 0;
            else newMatrix[i][j] = matrix[i][j];
    }
    return newMatrix;
};

vector<vector<double>> after(const vector<vector<double>> &m1, const vector<vector<int>> &alg)
{
    vector<vector<double>> m2 = m1;
    for (int i = 0; i < m1.size(); i++)
        for (int j = 0; j < m1[0].size(); j++)
            if (alg[i][j] == 0)
                m2[i][j] = 0;
            else m2[i][j] = m1[i][j];
    return m2;
}
