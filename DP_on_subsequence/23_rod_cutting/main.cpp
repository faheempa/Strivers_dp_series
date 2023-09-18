// Question : https://www.codingninjas.com/studio/problems/rod-cutting-problem_800284

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int solve(int index, vector<int> &prices, int target)
{
    // base condition
    if (index == 0)
    {
        return target * prices[0];
    }
    // explore all possibilities
    int notTake = solve(index - 1, prices, target);
    int take{0};
    if (index + 1 <= target)
        take = prices[index] + solve(index, prices, target - (index + 1));
    // get max
    return std::max(take, notTake);
}
int memoization(int index, vector<int> &prices, int target, vector<vector<int>> &dp)
{
    // base condition
    if (index == 0)
    {
        return target * prices[0];
    }
    // if already found
    if (dp[index][target] != -1)
        return dp[index][target];
    // explore all possibilities
    int notTake = memoization(index - 1, prices, target, dp);
    int take{0};
    if (index + 1 <= target)
        take = prices[index] + memoization(index, prices, target - (index + 1), dp);
    // get max
    return dp[index][target] = std::max(take, notTake);
}

int tabulation(vector<int> &prices, int n)
{
    vector<vector<int>> dp(n, vector<int>(n + 1, 0));
    // base condition
    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j * prices[0];
    }
    // compute all
    for (int index = 1; index < n; index++)
    {
        for (int target = 0; target <= n; target++)
        {
            // explore all possibilities
            int notTake = dp[index - 1][target];
            int take{0};
            if (index + 1 <= target)
                take = prices[index] + dp[index][target - (index + 1)];
            // get max
            dp[index][target] = std::max(take, notTake);
        }
    }
    return dp[n-1][n];
}
int tabulation_with_SO(vector<int> &prices, int n)
{
    vector<int> dp(n + 1, 0);
    // base condition
    for (int j = 0; j <= n; j++)
    {
        dp[j] = j * prices[0];
    }
    // compute all
    for (int index = 1; index < n; index++)
    {
        for (int target = 0; target <= n; target++)
        {
            // explore all possibilities
            int notTake = dp[target];
            int take{0};
            if (index + 1 <= target)
                take = prices[index] + dp[target - (index + 1)];
            // get max
            dp[target] = std::max(take, notTake);
        }
    }
    return dp[n];
}


int main()
{
    // input
    int n;
    cin >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
    }

    // Without dp
    int res = solve(n - 1, prices, n);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: exponential \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    int res2 = memoization(n - 1, prices, n, dp);
    cout << "Memoization: " << res << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(prices, n);
    cout << "Tabulation : "<<res3 << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(prices, n);
    cout << "Tabulation With SO : "<<res4 << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n) " << endl;
    cout << endl;
}
