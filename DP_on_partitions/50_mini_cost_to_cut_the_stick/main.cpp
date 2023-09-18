// Question : https://leetcode.com/problems/minimum-cost-to-cut-a-stick/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, vector<int> &cuts)
{
    // base
    if (i > j)
        return 0;
    // explore
    int cost = 1e9;
    for (int cutIndex = i; cutIndex <= j; cutIndex++)
    {
        int CutCost = cuts[j + 1] - cuts[i - 1];
        int leftCutCost = solve(i, cutIndex - 1, cuts);
        int rightCutCost = solve(cutIndex + 1, j, cuts);
        cost = std::min(cost, CutCost + leftCutCost + rightCutCost);
    }
    // return
    return cost;
}

int memoization(int i, int j, vector<int> &cuts, vector<vector<int>> &dp)
{
    // base
    if (i > j)
        return 0;
    // if already solved
    if (dp[i][j] != -1)
        return dp[i][j];
    // explore
    int cost = 1e9;
    for (int cutIndex = i; cutIndex <= j; cutIndex++)
    {
        int CutCost = cuts[j + 1] - cuts[i - 1];
        int leftCutCost = memoization(i, cutIndex - 1, cuts, dp);
        int rightCutCost = memoization(cutIndex + 1, j, cuts, dp);
        cost = std::min(cost, CutCost + leftCutCost + rightCutCost);
    }
    // return
    return dp[i][j] = cost;
}
int tabulation(vector<int> &cuts)
{
    int size = cuts.size();
    int lastCutIndex = size - 2;
    vector<vector<int>> dp(size, vector<int>(size, 1e9));
    // base
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            dp[i][j] = 0;
        }
    }
    // explore
    for (int i = lastCutIndex; i >= 1; i--)
    {
        for (int j = 1; j <= lastCutIndex; j++)
        {
            for (int cutIndex = i; cutIndex <= j; cutIndex++)
            {
                int CutCost = cuts[j + 1] - cuts[i - 1];
                int leftCutCost = dp[i][cutIndex - 1];
                int rightCutCost = dp[cutIndex + 1][j];
                dp[i][j] = std::min(dp[i][j], CutCost + leftCutCost + rightCutCost);
            }
        }
    }
    // return
    return dp[1][lastCutIndex];
}
int tabulation_with_SO()
{
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> cuts(n);
    for (int i = 0; i < n; i++)
        cin >> cuts[i];
    int length;
    cin >> length;

    cuts.push_back(length);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    int size = cuts.size();

    // Without dp
    int res = solve(1, size - 2, cuts);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: exponential \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(size, vector<int>(size, -1));
    int res2 = memoization(1, size - 2, cuts, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(cuts);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;
}
