// Question : https://www.codingninjas.com/studio/problems/boolean-evaluation_1214650

#include <bits/stdc++.h>
using namespace std;

int calculateWays(int leftTrue, int leftFalse, int rightTrue, int rightFalse, char op, int isTrue)
{
    int totalWays = (leftTrue + leftFalse) * (rightTrue + rightFalse);
    int totalTrueWays = 0;
    if (op == '&')
        totalTrueWays = leftTrue * rightTrue;
    else if (op == '|')
        totalTrueWays = leftTrue * rightTrue + leftTrue * rightFalse + leftFalse * rightTrue;
    else if (op == '^')
        totalTrueWays = leftTrue * rightFalse + leftFalse * rightTrue;

    return isTrue ? totalTrueWays : totalWays - totalTrueWays;
}

int solve(int i, int j, string &s, int isTrue = 1)
{
    // base
    if (i > j)
        return 0;
    if (i == j)
    {
        if (isTrue)
            return s[i] == 'T';
        else
            return s[i] == 'F';
    }
    // explore
    int res{0};
    for (int k = i + 1; k < j; k += 2)
    {
        int leftTrue = solve(i, k - 1, s, 1);
        int leftFalse = solve(i, k - 1, s, 0);
        int rightTrue = solve(k + 1, j, s, 1);
        int rightFalse = solve(k + 1, j, s, 0);
        int ways = calculateWays(leftTrue, leftFalse, rightTrue, rightFalse, s[k], isTrue);
        res += ways;
    }
    // return
    return res;
}

int memoization(int i, int j, string &s, int isTrue, vector<vector<vector<int>>> &dp)
{
    // base
    if (i > j)
        return 0;
    if (i == j)
    {
        if (isTrue)
            return s[i] == 'T';
        else
            return s[i] == 'F';
    }
    // already solved?
    if (dp[i][j][isTrue] != -1)
        return dp[i][j][isTrue];
    // explore
    int res{0};
    for (int k = i + 1; k < j; k += 2)
    {
        int leftTrue = memoization(i, k - 1, s, 1, dp);
        int leftFalse = memoization(i, k - 1, s, 0, dp);
        int rightTrue = memoization(k + 1, j, s, 1, dp);
        int rightFalse = memoization(k + 1, j, s, 0, dp);
        int ways = calculateWays(leftTrue, leftFalse, rightTrue, rightFalse, s[k], isTrue);
        res += ways;
    }
    // return
    return dp[i][j][isTrue] = res;
}
int tabulation(string &s)
{
    int n = s.length();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
    // base
    for (int i = 0; i < n; i += 2)
    {
        if (s[i] == 'T')
            dp[i][i][1] = 1;
        else
            dp[i][i][0] = 1;
    }
    // explore
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i; j < n; j++)
        {
            for (int isTrue = 0; isTrue < 2; isTrue++)
            {
                for (int k = i + 1; k < j; k += 2)
                {
                    int leftTrue = dp[i][k - 1][1];
                    int leftFalse = dp[i][k - 1][0];
                    int rightTrue = dp[k + 1][j][1];
                    int rightFalse = dp[k + 1][j][0];
                    int ways = calculateWays(leftTrue, leftFalse, rightTrue, rightFalse, s[k], isTrue);
                    dp[i][j][isTrue] += ways;
                }
            }
        }
    }
    // return
    return dp[0][n - 1][1];
}
int tabulation_with_SO()
{
}

int main()
{
    // input
    string s;
    cin >> s;

    int n = s.length();
    // Without dp
    int res = solve(0, n - 1, s);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: exponential \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
    int res2 = memoization(0, n - 1, s, 1, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(s);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

}
