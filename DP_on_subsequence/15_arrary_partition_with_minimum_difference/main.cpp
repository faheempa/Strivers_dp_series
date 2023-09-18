// Question : https://www.codingninjas.com/studio/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494

#include <iostream>
#include <vector>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

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
vector<vector<bool>> tabulation(vector<int> &arr, int n, int k)
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
    return dp;
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    int sum = std::accumulate(arr.begin(), arr.end(), 0);

    // memoization
    int res{-1};
    vector<vector<int>> dp(n, vector<int>((sum / 2) + 1, -1));
    for (int target = sum / 2; target >= 0; target--)
    {
        if (memoization(arr, n - 1, target, dp))
        {
            res = sum - (2 * target);
            break;
        }
    }
    cout << "Memoization: " << res << endl;
    cout << "Time complexity: O(n*sum) \nSpace complexity: O(n*sum) " << endl;
    cout << endl;

    // tabulation
    auto dp2 = tabulation(arr, n, sum / 2);
    int res2{-1};
    for (int target = sum / 2; target >= 0; target--)
    {
        if (dp2[n][target])
        {
            res2 = sum - (2 * target);
            break;
        }
    }
    cout << "Tabulation : " << res2 << endl;
    cout << "Time complexity: O(n*sum) \nSpace complexity: O(n*sum) " << endl;
    cout << endl;
}
