// Question : https://leetcode.com/problems/minimum-path-sum/

#include <iostream>
#include <vector>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int without_dp(int i, int j, vector<vector<int>> &nums)
{
    if (i < 0 or j < 0)
        return INT_MAX;

    if (i == 0 and j == 0)
        return nums[i][j];

    return nums[i][j] + std::min(without_dp(i, j - 1, nums), without_dp(i - 1, j, nums));
}

int memoization(int i, int j, vector<vector<int>> &nums, vector<vector<int>> &dp)
{

    if (i == 0 and j == 0)
        return nums[i][j];

    if (i < 0 or j < 0)
        return INT_MAX;

    if (dp[i][j] != -1)
        return dp[i][j];

    return dp[i][j] = nums[i][j] + std::min(memoization(i, j - 1, nums, dp), memoization(i - 1, j, nums, dp));
}
int tabluation(vector<vector<int>> &nums)
{
    int r = nums.size(), c = nums[0].size();
    vector<vector<int>> dp(r, vector<int>(c, -1));
    dp[0][0] = nums[0][0];
    for (size_t i = 0; i < r; i++)
    {
        for (size_t j = 0; j < c; j++)
        {
            if (i == 0 and j == 0)
                continue;

            int top{INT_MAX}, left{INT_MAX};
            if (i > 0)
                top = dp[i - 1][j];

            if (j > 0)
                left = dp[i][j - 1];

            dp[i][j] = nums[i][j] + std::min(top, left);
        }
    }
    return dp[r - 1][c - 1];
}
int tabluation_with_SO(vector<vector<int>> &nums)
{
    int r = nums.size(), c = nums[0].size();
    vector<int> pre(c, 0);
    pre[0] = nums[0][0];
    for (size_t i = 0; i < r; i++)
    {
        vector<int> cur{pre};
        for (size_t j = 0; j < c; j++)
        {
            if (i == 0 and j == 0)
                continue;

            int top{INT_MAX}, left{INT_MAX};
            if (i > 0)
                top = pre[j];

            if (j > 0)
                left = cur[j - 1];

            cur[j] = nums[i][j] + std::min(top, left);
        }
        pre = cur;
    }
    return pre[c - 1];
}

int main()
{
    // input
    int r, c;
    cin >> r >> c;
    vector<vector<int>> nums(r, vector<int>(c));
    for (size_t i = 0; i < r; i++)
    {
        for (size_t j = 0; j < c; j++)
        {
            int a;
            cin >> a;
            nums[i][j] = a;
        }
    }

    // Without dp
    int ans = without_dp(r - 1, c - 1, nums);
    cout << "Without DP: " << ans << endl;
    cout << "Time complexity: O(2^r*c) \nSpace complexity: O(r+c) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(r, vector<int>(c, -1));
    int ans2 = memoization(r - 1, c - 1, nums, dp);
    cout << "Memoization: " << ans2 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(r*c) " << endl;
    cout << endl;

    // tabulation
    int ans3 = tabluation(nums);
    cout << "Tabluation : " << ans3 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(r*c) " << endl;
    cout << endl;

    // tabulation with space optimization
    int ans4 = tabluation_with_SO(nums);
    cout << "Tabulation With SO : " << ans4 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(c) " << endl;
}
