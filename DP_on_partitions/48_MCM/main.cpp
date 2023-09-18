// Question : https://www.codingninjas.com/studio/problems/matrix-chain-multiplication_624880

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, vector<int> &arr)
{
    // base
    if (i == j)
        return 0;
    // explore
    int res = 1e9;
    for (int k = i; k < j; k++)
    {
        int step = arr[i - 1] * arr[k] * arr[j] + solve(i, k, arr) + solve(k + 1, j, arr);
        res = std::min(res, step);
    }
    // return
    return res;
}

int memoization(int i, int j, vector<int> &arr, vector<vector<int>> &dp)
{
    // base
    if (i == j)
        return 0;
    // if already solved
    if (dp[i][j] != -1)
        return dp[i][j];
    // explore
    int res = 1e9;
    for (int k = i; k < j; k++)
    {
        int step = arr[i - 1] * arr[k] * arr[j] + memoization(i, k, arr, dp) + memoization(k + 1, j, arr, dp);
        res = std::min(res, step);
    }
    // return
    return dp[i][j] = res;
}
int tabulation(vector<int> &arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 1e9));
    // base
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;
    // explore
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = i; k < j; k++)
            {
                int step = arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j];
                dp[i][j] = std::min(dp[i][j], step);
            }
        }
    }
    // return
    return dp[1][n - 1];
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &i : arr)
        cin >> i;

    // Without dp
    int res = solve(1, n - 1, arr);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: exponetial \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    int res2 = memoization(1, n - 1, arr, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(arr);
    cout << "Tabulation : "<<res3 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

}
