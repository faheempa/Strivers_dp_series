// Question : https://www.codingninjas.com/studio/problems/partition-equal-subset-sum_892980

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
bool tabulation(vector<int> &arr, int n, int k)
{
    vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));
    // base case
    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;
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

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &i : arr)
        cin >> i;

    int sum = std::accumulate(arr.begin(), arr.end(), 0);
    cout << std::boolalpha;

    // memoization
    vector<vector<int>> dp(n, vector<int>((sum / 2) + 1, -1));
    bool res2 = (sum % 2 == 0) ? memoization(arr, n - 1, sum / 2, dp) : false;
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation
    bool res3 = (sum % 2 == 0) ? tabulation(arr, n, sum / 2) : false;
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n*n) \nSpace complexity: O(n*n) " << endl;
    cout << endl;

}
