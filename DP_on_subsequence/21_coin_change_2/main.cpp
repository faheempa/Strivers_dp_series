// Question :

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int memoization(vector<int> &coins, int index, int target, vector<vector<int>> &dp)
{
    // base condition
    if (index == 0)
        return (target % coins[0] == 0);
    // if already solved
    if (dp[index][target] != -1)
        return dp[index][target];
    // explore all possibilities
    int notTake = memoization(coins, index - 1, target, dp);
    int take{0};
    if (coins[index] <= target)
        take = memoization(coins, index, target - coins[index], dp);
    // take minimum
    return dp[index][target] = take + notTake;
}
int tabulation(vector<int> &coins, int n, int target)
{
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));
    // base condition
    for (int t = 0; t <= target; t++)
    {
        dp[0][t] = (t % coins[0] == 0);
    }
    // explore
    for (int i = 1; i < n; i++)
    {
        for (int t = 0; t <= target; t++)
        {
            int notTake = dp[i - 1][t];
            int take{0};
            if (coins[i] <= t)
                take = dp[i][t - coins[i]];
            dp[i][t] = take + notTake;
        }
    }
    // return
    return dp[n - 1][target];
}

int main()
{
    // input
    // input
    int n, m;
    cin >> n >> m;
    vector<int> coins(m);
    for (int i = 0; i < m; i++)
    {
        cin >> coins[i];
    }

    // memoization
    vector<vector<int>> dp(n, vector<int>(m + 1, -1));
    int res = memoization(coins, n - 1, m, dp);
    cout << "Memoization: " << res << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(coins, n, m);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;
}
