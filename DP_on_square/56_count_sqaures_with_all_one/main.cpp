// Question :

#include <bits/stdc++.h>
using namespace std;

int tabulation(vector<vector<int>> &matrix)
{
    int rows = matrix.size(), cols = matrix[0].size();
    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++)
        dp[i][0] = matrix[i][0];

    for (int j = 0; j < cols; j++)
        dp[0][j] = matrix[0][j];

    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] == 0)
                dp[i][j] = 0;
            else
                dp[i][j] = std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
        }
    }
    int sum{0};
    for (auto &row : dp)
    {
        for (auto &var : row)
        {
            sum += var;
        }
    }
    return sum;
}
int tabulation_with_SO(vector<vector<int>> &matrix)
{
    int rows = matrix.size(), cols = matrix[0].size();
    vector<int> dp(cols, 0), cur(cols, 0);
    for (int j = 0; j < cols; j++)
    {
        dp[j] = matrix[0][j];
    }
    
    int sum = std::accumulate(dp.begin(), dp.end(), 0);
    for (int i = 1; i < rows; i++)
    {
        cur[0] = matrix[i][0];
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] == 0)
                cur[j] = 0;
            else
                cur[j] = std::min({dp[j - 1], dp[j], cur[j - 1]}) + 1;
        }
        dp = cur;
        sum += std::accumulate(dp.begin(), dp.end(), 0);
    }
    return sum;
}


int main()
{
    // input
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
        }
    }

    // tabulation
    int res = tabulation(matrix);
    cout << "Tabulation : " << res << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res2 = tabulation_with_SO(matrix);
    cout << "Tabulation with SO: " << res << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n) " << endl;
    cout << endl;
}
