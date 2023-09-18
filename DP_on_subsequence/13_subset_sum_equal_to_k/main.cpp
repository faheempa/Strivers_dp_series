// Question : https://www.codingninjas.com/studio/problems/subset-sum-equal-to-k_1550954

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

bool solve(vector<int> &arr, int index, int target)
{
    // base case
    if (target == 0)
        return true;
    if (index == 0)
        return arr[index] == target;
    // explore
    bool leave = solve(arr, index - 1, target);
    bool take{false};
    if (arr[index] <= target)
        take = solve(arr, index - 1, target - arr[index]);

    return leave || take;
}

bool memoization(vector<int> &arr, int index, int target, vector<vector<int>> &dp)
{
    // base case
    if (target == 0)
        return true;
    if (index == 0)
        return arr[index] == target;
    if (dp[index][target] != -1)
        return dp[index][target];
    // explore
    bool leave = memoization(arr, index - 1, target, dp);
    bool take{false};
    if (arr[index] <= target)
        take = memoization(arr, index - 1, target - arr[index], dp);

    return dp[index][target] = leave || take;
}
bool tabulation(vector<int> &arr, int n, int k)
{
    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));
    // base case
    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;
    if (arr[0] <= k)
        dp[0][arr[0]] = true;
    // explore
    for (int index = 1; index <= n; ++index)
    {
        for (int target = 1; target <= k; ++target)
        {
            bool leave = dp[index - 1][target];
            bool take{false};
            if (arr[index] <= target)
                take = dp[index - 1][target - arr[index]];

            dp[index][target] = leave || take;
        }
    }
    return dp[n][k];
}
bool tabulation_with_SO(vector<int> &arr, int n, int k)
{
    vector<bool> dp(k + 1, false);
    // base case
    dp[0] = true;
    dp[arr[0]] = true;
    // explore
    for (int index = 1; index <= n; ++index)
    {
        vector<bool> temp(k + 1, false);
        for (int target = 1; target <= k; ++target)
        {
            bool leave = dp[target];
            bool take{false};
            if (arr[index] <= target)
                take = dp[target - arr[index]];

            temp[target] = leave || take;
        }
        dp = temp;
    }
    return dp[k];
}

int main()
{
    // input
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cout << std::boolalpha;
    // Without dp
    bool res = solve(arr, n - 1, k);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
    bool res1 = memoization(arr, n - 1, k, dp);
    cout << "Memoization: " << res1 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(n*k) " << endl;
    cout << endl;

    // tabulation
    bool res2 = tabulation(arr, n, k);
    cout << "Tabulation : " << res2 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(n*k) " << endl;
    cout << endl;

    // tabulation with space optimization
    bool res3 = tabulation_with_SO(arr, n, k);
    cout << "Tabulation With SO : " << res3 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(k) " << endl;
    cout << endl;
}
