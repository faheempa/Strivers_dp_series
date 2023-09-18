// Question : https://leetcode.com/problems/longest-increasing-subsequence/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, vector<int> &nums, int prevIndex = -1)
{
    // base
    if (i == nums.size())
        return 0;
    // explore
    int pick{0}, notPick{0};
    notPick = solve(i + 1, nums, prevIndex);
    if (prevIndex == -1 || nums[prevIndex] < nums[i])
        pick = solve(i + 1, nums, i) + 1;
    // return
    return max(pick, notPick);
}

int memoization(int i, vector<int> &nums, vector<vector<int>> &dp, int prevIndex = -1)
{
    // base
    if (i == nums.size())
        return 0;
    // check
    if (dp[i][prevIndex + 1] != -1)
        return dp[i][prevIndex + 1];
    // explore
    int pick{0}, notPick{0};
    notPick = memoization(i + 1, nums, dp, prevIndex);
    if (prevIndex == -1 || nums[prevIndex] < nums[i])
        pick = memoization(i + 1, nums, dp, i) + 1;
    // return
    return dp[i][prevIndex + 1] = max(pick, notPick);
}

int tabulation(vector<int> &nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = n; j >= 0; j--)
        {
            int pick{0}, notPick{0};
            notPick = dp[i + 1][j];
            if (j == 0 || nums[j - 1] < nums[i])
                pick = dp[i + 1][i + 1] + 1;
            dp[i][j] = max(pick, notPick);
        }
    }
    return dp[0][0];
}
int tabulation_with_SO(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n + 1, 0), curr(n + 1, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = n; j >= 0; j--)
        {
            int pick{0}, notPick{0};
            notPick = dp[j];
            if (j == 0 || nums[j - 1] < nums[i])
                pick = dp[i + 1] + 1;
            curr[j] = max(pick, notPick);
        }
        dp = curr;
    }
    return dp[0];
}
int tabulation_with_SO_2(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int prevIndex = 0; prevIndex < i; prevIndex++)
        {
            if (nums[prevIndex] < nums[i])
                dp[i] = max(dp[i], dp[prevIndex] + 1);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto &i : nums)
        cin >> i;

    // Without dp
    int res = solve(0, nums);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    int res2 = memoization(0, nums, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(2^n) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(nums);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n^2) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(nums);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization 2
    int res5 = tabulation_with_SO_2(nums);
    cout << "Tabulation With SO 2 : " << res5 << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n) " << endl;
    cout << endl;

}
