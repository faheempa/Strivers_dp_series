// Question : https://leetcode.com/problems/target-sum/

#include <iostream>
#include <vector>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int memoization(vector<int> &nums, int index, int sum, vector<vector<int>> &dp)
{
    // base case
    if (index == 0)
    {
        if (sum == 0 and nums[0] == 0)
            return 2;
        if (sum == 0 or sum == nums[0])
            return 1;
        return 0;
    }
    // check if already calculated
    if (dp[index][sum] != -1)
        return dp[index][sum];
    // explore
    int pick{0};
    if (nums[index] <= sum)
        pick = memoization(nums, index - 1, sum - nums[index], dp);
    int notPick = memoization(nums, index - 1, sum, dp);
    // sum up
    return dp[index][sum] = pick + notPick;
}
int tabulation(vector<int> &nums, int sum)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

    // base conditions
    if (nums[0] == 0)
        dp[0][0] = 2;
    else
        dp[0][0] = 1;

    if (nums[0] <= sum and nums[0] != 0)
        dp[0][nums[0]] = 1;
    // explore
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            int pick{0};
            if (nums[i] <= j)
                pick = dp[i - 1][j - nums[i]];
            int notPick = dp[i - 1][j];
            dp[i][j] = pick + notPick;
        }
    }

    // return
    return dp[n - 1][sum];
}

int main()
{
    // input
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (auto &i : nums)
        cin >> i;
    // logic
    // s1 + s2 + diff = sum
    // s1 + s2 = sum-diff
    // s1==s2 => 2s = sum-diff
    // s = (sum-diff)/2 => target
    // memoization
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    int res{0};
    if ((sum - k) >= 0 and (sum - k) % 2 == 0)
    {
        int target = (sum - k) / 2;
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        res = memoization(nums, n - 1, target, dp);
    }
    cout << "Memoization: " << res << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(n*k) " << endl;
    cout << endl;

    // tabulation
    int res2{0};
    if ((sum - k) >= 0 and (sum - k) % 2 == 0)
    {
        int target = (sum - k) / 2;
        res2 = tabulation(nums, target);
    }
    cout << "Tabulation : " << res2 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(n*k) " << endl;
    cout << endl;
}
