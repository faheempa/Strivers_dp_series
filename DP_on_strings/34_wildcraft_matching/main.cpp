// Question : https://leetcode.com/problems/wildcard-matching/submissions/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, string &s1, string &s2)
{
    // base conditions
    if (i < 0 and j < 0)
        return true;
    if (i < 0 and j >= 0)
        return false;
    if (j < 0 and i >= 0)
    {
        while (i >= 0)
        {
            if (s1[i] != '*')
                return false;
            i--;
        }
        return true;
    }
    // exploration
    bool match{false}, starAsNothing{false}, startAsSomething{false};
    if (s1[i] == s2[j] or s1[i] == '?')
    {
        match = solve(i - 1, j - 1, s1, s2);
    }
    else if (s1[i] == '*')
    {
        starAsNothing = solve(i - 1, j, s1, s2);
        startAsSomething = solve(i, j - 1, s1, s2);
    }
    // return
    return (match || starAsNothing || startAsSomething);
}

int memoization(int i, int j, string &s1, string &s2, vector<vector<bool>> &dp)
{
    // base conditions
    if (i < 0 and j < 0)
        return true;
    if (i < 0 and j >= 0)
        return false;
    if (j < 0 and i >= 0)
    {
        while (i >= 0)
        {
            if (s1[i] != '*')
                return false;
            i--;
        }
        return true;
    }
    // check if already calculated
    if (dp[i][j])
        return dp[i][j];
    // exploration
    bool match{false}, starAsNothing{false}, startAsSomething{false};
    if (s1[i] == s2[j] or s1[i] == '?')
    {
        match = memoization(i - 1, j - 1, s1, s2, dp);
    }
    else if (s1[i] == '*')
    {
        starAsNothing = memoization(i - 1, j, s1, s2, dp);
        startAsSomething = memoization(i, j - 1, s1, s2, dp);
    }
    // return
    return dp[i][j] = (match || starAsNothing || startAsSomething);
}

int tabulation(string &s1, string &s2)
{
    int n = s1.length(), m = s2.length();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    // base conditions
    dp[0][0] = true;
    for (int i = 1; i <= n; i++)
    {
        if (s1[i - 1] == '*')
            dp[i][0] = dp[i - 1][0];
    }
    // exploration
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1] or s1[i - 1] == '?')
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else if (s1[i - 1] == '*')
            {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
        }
    }
    // return
    return dp[n][m];
}
int tabulation_with_SO(string &s1, string &s2)
{
    int n = s1.length(), m = s2.length();
    vector<bool> dp(m + 1, false);
    // base condition
    dp[0] = true;
    // exploration
    for (int i = 1; i <= n; i++)
    {
        vector<bool> temp(m + 1, false);
        // base condition
        if (s1[i - 1] == '*')
            temp[0] = dp[0];
        for (int j = 1; j <= m; j++)
        {
            char str_i = s1[i - 1], str_j = s2[j - 1];
            if (str_i == str_j or str_i == '?')
            {
                temp[j] = dp[j - 1];
            }
            else if (str_i == '*')
            {
                temp[j] = dp[j] || temp[j - 1];
            }
        }
        dp = temp;
    }
    // return
    return dp[m];
}


int main()
{
    // input
    string s1, s2;
    cin >> s1 >> s2;

    cout << std::boolalpha;
    // Without dp
    int n = s1.length(), m = s2.length();
    bool res = solve(n - 1, m - 1, s1, s2);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: exponential \nSpace complexity: O(n+m) " << endl;
    cout << endl;

    // memoization
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    bool res2 = memoization(n - 1, m - 1, s1, s2, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation
    bool res3 = tabulation(s1, s2);
    cout << "Tabulation : " <<res3<< endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation with space optimization
    bool res4 = tabulation_with_SO(s1, s2);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(m) " << endl;
    cout << endl;
}
