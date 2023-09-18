// Question : https://www.codingninjas.com/studio/problems/0-1-knapsack_920542

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int solve(vector<int> &wt, vector<int> &val, int index, int remainingWt)
{
    // base conditions
    if (index == 0)
    {
        if (wt[0] <= remainingWt)
            return val[0];
        return 0;
    }
    // explore all possibilities
    int notTake = solve(wt, val, index - 1, remainingWt);
    int take{0};
    if (wt[index] <= remainingWt)
        take = val[index] + solve(wt, val, index - 1, remainingWt - wt[index]);
    // get max
    return std::max(take, notTake);
}

int memoization(vector<int> &wt, vector<int> &val, int index, int remainingWt, vector<vector<int>> &dp)
{
    // base conditions
    if (index == 0)
    {
        if (wt[0] <= remainingWt)
            return val[0];
        return 0;
    }
    // check if already solved
    if (dp[index][remainingWt] != -1)
        return dp[index][remainingWt];
    // explore all possibilities
    int notTake = memoization(wt, val, index - 1, remainingWt, dp);
    int take{0};
    if (wt[index] <= remainingWt)
        take = val[index] + memoization(wt, val, index - 1, remainingWt - wt[index], dp);
    // get max
    return dp[index][remainingWt] = std::max(take, notTake);
}
int tabulation(vector<int> &wts, vector<int> &val, int n, int maxWt)
{
    vector<vector<int>> dp(n, vector<int>(maxWt + 1, 0));
    // base condition
    for (int j = wts[0]; j <= maxWt; j++)
        dp[0][j] = val[0];
    // build the dp
    for (int index = 1; index < n; index++)
    {
        for (int wt = 0; wt <= maxWt; wt++)
        {
            // explore all possibilities
            int notTake = dp[index - 1][wt];
            int take{0};
            if (wts[index] <= wt)
                take = val[index] + dp[index - 1][wt - wts[index]];
            // get max
            dp[index][wt] = std::max(take, notTake);
        }
    }
    return dp[n - 1][maxWt];
}
int tabulation_with_SO(vector<int> &wts, vector<int> &val, int n, int maxWt)
{
    vector<int> dp(maxWt + 1, 0);
    // base condition
    for (int j = wts[0]; j <= maxWt; j++)
        dp[j] = val[0];
    // build the dp
    for (int index = 1; index < n; index++)
    {
        for (int wt = maxWt; wt >= 0; wt--)
        {
            // explore all possibilities
            int notTake = dp[wt];
            int take{0};
            if (wts[index] <= wt)
                take = val[index] + dp[wt - wts[index]];
            // get max
            dp[wt] = std::max(take, notTake);
        }
    }
    return dp[maxWt];
}

int main()
{
    // input
    int n, w;
    cin >> n;
    vector<int> weights(n);
    vector<int> values(n);
    for (auto &i : weights)
        cin >> i;
    for (auto &i : values)
        cin >> i;
    cin >> w;
    // Without dp
    int res = solve(weights, values, n - 1, w);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n, vector<int>(w + 1, -1));
    int res2 = memoization(weights, values, n - 1, w, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n*w) \nSpace complexity: O(n*w) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(weights, values, n, w);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n*w) \nSpace complexity: O(n*w) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(weights, values, n, w);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n*w) \nSpace complexity: O(w) " << endl;
    cout << endl;
}
