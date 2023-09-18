// Question : https://leetcode.com/problems/edit-distance/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, string &s1, string &s2)
{
    // base
    if (i < 0)
        return j + 1;
    if (j < 0)
        return i + 1;
    // exploration
    int match{(int)1e9}, insert{(int)1e9}, dlt{(int)1e9}, replace{(int)1e9};
    if (s1[i] == s2[j])
    {
        match = 0 + solve(i - 1, j - 1, s1, s2);
    }
    else
    {
        insert = 1 + solve(i, j - 1, s1, s2);
        dlt = 1 + solve(i - 1, j, s1, s2);
        replace = 1 + solve(i - 1, j - 1, s1, s2);
    }
    // minimize
    return std::min({match, insert, dlt, replace});
}

int memoization(int i, int j, string &s1, string &s2, vector<vector<int>> &dp)
{
    // base
    if (i < 0)
        return j + 1;
    if (j < 0)
        return i + 1;
    // check
    if (dp[i][j] != -1)
        return dp[i][j];
    // exploration
    int match{(int)1e9}, insert{(int)1e9}, dlt{(int)1e9}, replace{(int)1e9};
    if (s1[i] == s2[j])
    {
        match = 0 + memoization(i - 1, j - 1, s1, s2, dp);
    }
    else
    {
        insert = 1 + memoization(i, j - 1, s1, s2, dp);
        dlt = 1 + memoization(i - 1, j, s1, s2, dp);
        replace = 1 + memoization(i - 1, j - 1, s1, s2, dp);
    }
    // minimize
    return dp[i][j] = std::min({match, insert, dlt, replace});
}

int tabulation(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, (int)1e9));
    // base
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;
    // exploration
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int str_i{i - 1}, str_j{j - 1};
            if (s1[str_i] == s2[str_j])
            {
                dp[i][j] = 0 + dp[i - 1][j - 1];
            }
            else
            {
                int insert = 1 + dp[i][j - 1];
                int dlt = 1 + dp[i - 1][j];
                int replace = 1 + dp[i - 1][j - 1];
                dp[i][j] = std::min({insert, dlt, replace});
            }
        }
    }
    return dp[n][m];
}
int tabulation_with_SO(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<int> dp(m + 1, 0), temp(m + 1, 0);
    // base
    for (int j = 0; j <= m; j++)
        dp[j] = j;
    // exploration
    for (int i = 1; i <= n; i++)
    {
        temp[0] = i; // base
        for (int j = 1; j <= m; j++)
        {
            int str_i{i - 1}, str_j{j - 1};
            if (s1[str_i] == s2[str_j])
            {
                temp[j] = 0 + dp[j - 1];
            }
            else
            {
                int insert = 1 + temp[j - 1];
                int dlt = 1 + dp[j];
                int replace = 1 + dp[j - 1];
                temp[j] = std::min({insert, dlt, replace});
            }
        }
        dp = temp;
    }
    return dp[m];
}

int main()
{
    // input
    string s1, s2;
    cin >> s1 >> s2;

    // Without dp
    int n = s1.size(), m = s2.size();
    int res = solve(n - 1, m - 1, s1, s2);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: exponential \nSpace complexity: O(n+m) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    int res2 = memoization(n - 1, m - 1, s1, s2, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(s1, s2);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(s1, s2);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(m) " << endl;
    cout << endl;
}
