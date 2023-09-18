// Question : https://www.codingninjas.com/studio/problems/minimum-elements_3843091

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int solve(vector<int> &coins, int index, int target)
{
    // base condition
    if (index == 0)
    {
        if (target % coins[0] == 0)
            return target / coins[0];
        return 1e9;
    }
    if (target == 0)
        return 1e9;
    if (target == coins[index])
        return 1;
    // explore all possibilities
    int notTake = 0 + solve(coins, index - 1, target);
    int take{INT_MAX};
    if (coins[index] <= target)
        take = 1 + solve(coins, index, target - coins[index]);
    // take minimum
    return std::min(take, notTake);
}

int memoization(vector<int> &coins, int index, int target, vector<vector<int>> &dp)
{
    // base condition
    if (index == 0)
    {
        if (target % coins[0] == 0)
            return target / coins[0];
        return 1e9;
    }
    if (target == 0)
        return 1e9;
    if (target == coins[index])
        return 1;
    // if already solved
    if (dp[index][target] != -1)
        return dp[index][target];
    // explore all possibilities
    int notTake = 0 + memoization(coins, index - 1, target, dp);
    int take{int(1e9)};
    if (coins[index] <= target)
        take = 1 + memoization(coins, index, target - coins[index], dp);
    // take minimum
    return dp[index][target] = std::min(take, notTake);
}
int tabulation(vector<int> coins, int n, int target)
{
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));
    // base condition
    if (target == 0)
        return 1e9;
    for (int t = 1; t <= target; t++)
    {
        if (t % coins[0] == 0)
            dp[0][t] = t / coins[0];
        else
            dp[0][t] = 1e9;
    }
    // explore
    for (int i = 1; i < n; i++)
    {
        for (int t = 1; t <= target; t++)
        {
            int notTake = dp[i - 1][t];
            int take = (coins[i] <= t) ? 1 + dp[i][t - coins[i]] : 1e9;
            dp[i][t] = std::min(take, notTake);
        }
    }
    // return
    return (dp[n - 1][target] >= 1e9) ? -1 : dp[n - 1][target];
}
int tabulation_with_SO(vector<int> &coins, int n, int target)
{
    vector<int> dp(target + 1, 0);
    // base condition
    if (target == 0)
        return 1e9;
    for (int t = 1; t <= target; t++)
    {
        if (t % coins[0] == 0)
            dp[t] = t / coins[0];
        else
            dp[t] = 1e9;
    }
    // explore
    for (int i = 1; i < n; i++)
    {
        vector<int> temp(target + 1, 0);
        for (int t = 1; t <= target; t++)
        {
            int notTake = dp[t];
            int take = (coins[i] <= t) ? 1 + temp[t - coins[i]] : 1e9;
            temp[t] = std::min(take, notTake);
        }
        dp = temp;
    }
    // return
    return (dp[target] >= 1e9) ? -1 : dp[target];
}

int main()
{
    // input
    int n, m;
    cin >> n >> m;
    vector<int> coins(m);
    for (int i = 0; i < m; i++)
    {
        cin >> coins[i];
    }

    // Without dp
    int res = solve(coins, n - 1, m);
    res = (res >= 1e9) ? -1 : res;
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n, vector<int>(m + 1, -1));
    int res2 = memoization(coins, n - 1, m, dp);
    res2 = (res2 >= 1e9) ? -1 : res2;
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(coins, n, m);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(coins, n, m);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(m) " << endl;
    cout << endl;
}
