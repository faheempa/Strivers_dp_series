// Question : https://leetcode.com/problems/distinct-subsequences/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, string &s1, string &s2)
{
    // base conditions
    if (j < 0)
        return 1;
    if (i < 0)
        return 0;
    // explore
    int take{0}, notTake{0};
    notTake = solve(i - 1, j, s1, s2);
    if (s1[i] == s2[j])
    {
        take = solve(i - 1, j - 1, s1, s2);
    }
    // sum up
    return take + notTake;
}

int memoization(int i, int j, string &s1, string &s2, vector<vector<int>> &dp)
{
    // base conditions
    if (j < 0)
        return 1;
    if (i < 0)
        return 0;
    // if alread solved
    if (dp[i][j] != -1)
        return dp[i][j];
    // explore
    int take{0}, notTake{0};
    notTake = memoization(i - 1, j, s1, s2, dp);
    if (s1[i] == s2[j])
    {
        take = memoization(i - 1, j - 1, s1, s2, dp);
    }
    // sum up
    return dp[i][j] = take + notTake;
}
int tabulation(string s1, string s2)
{
    int n = s1.length();
    int m = s2.length();
    if (n == m)
        return s1 == s2;
    int dp[n + 1][m + 1];
    memset(dp, 0, sizeof(dp));
    // base case
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;
    // explore
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int s1Index = i - 1;
            int s2Index = j - 1;
            if (s1[s1Index] == s2[s2Index])
            {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][m];
}
int tabulation_with_SO(string s1, string s2)
{
    int n = s1.length();
    int m = s2.length();
    if (n == m)
        return s1 == s2;
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    // base case
        dp[0] = 1;
    // explore
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int s1Index = i - 1;
            int s2Index = j - 1;
            if (s1[s1Index] == s2[s2Index])
            {
                dp[j] = dp[j - 1] + dp[j];
            }
            else
            {
                dp[j] = dp[j];
            }
        }
    }
    return dp[m];
}

int main()
{
    // input
    string s1, s2;
    cin >> s1;
    cin >> s2;

    int n = s1.length();
    int m = s2.length();

    // Without dp
    int res = solve(n - 1, m - 1, s1, s2);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: Exponential \nSpace complexity: O(n+m) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n, vector<int>(m, -1));
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
    cout << "Tabulation With SO : "<<res4 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(m) " << endl;
    cout << endl;
}
