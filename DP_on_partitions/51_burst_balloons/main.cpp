// Question : https://leetcode.com/problems/burst-balloons/description/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, vector<int> &nums)
{
    // base
    if (i > j)
        return 0;
    // explore
    int res{0};
    for (int k = i; k <= j; k++)
    {
        int coins = nums[i - 1] * nums[k] * nums[j + 1];
        int leftCoin = solve(i, k - 1, nums);
        int rightCoin = solve(k + 1, j, nums);
        coins += leftCoin + rightCoin;
        res = std::max(res, coins);
    }
    // return
    return res;
}

int memoization(int i, int j, vector<int> &nums, vector<vector<int>> &dp)
{
    // base
    if (i > j)
        return 0;
    // if already solve
    if (dp[i][j] != -1)
        return dp[i][j];
    // explore
    int res{0};
    for (int k = i; k <= j; k++)
    {
        int coins = nums[i - 1] * nums[k] * nums[j + 1];
        int leftCoin = memoization(i, k - 1, nums, dp);
        int rightCoin = memoization(k + 1, j, nums, dp);
        coins += leftCoin + rightCoin;
        res = std::max(res, coins);
    }
    // return
    return dp[i][j] = res;
}

int tabulation(vector<int> &nums)
{
    // nums.push_back(1); - already done
    // nums.insert(nums.begin(), 1); - already done
    int n = nums.size();
    int start = 1;
    int end = nums.size() - 2;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    // base - already set
    // explore
    for (int i = end; i >= start; i--)
    {
        for (int j = start; j <= end; j++)
        {
            for (int k = i; k <= j; k++)
            {
                int coins = nums[i - 1] * nums[k] * nums[j + 1];
                int leftCoin = dp[i][k - 1];
                int rightCoin = dp[k + 1][j];
                coins += leftCoin + rightCoin;
                dp[i][j] = std::max(dp[i][j], coins);
            }
        }
    }
    // return
    return dp[start][end];
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto &i : nums)
        cin >> i;

    //  put 1 on both sides
    nums.push_back(1);
    nums.insert(nums.begin(), 1);

    // Without dp
    int res = solve(1, n, nums);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: exponential \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    int res2 = memoization(1, n, nums, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(nums);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;
}
