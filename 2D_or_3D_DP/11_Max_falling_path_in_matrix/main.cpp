// Question : https://leetcode.com/problems/minimum-falling-path-sum/

#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int without_dp(vector<vector<int>> &nums, int i, int j)
{
    if (j < 0 or j == nums[0].size())
        return INT_MIN;

    if (i == 0)
        return nums[i][j];

    int top = without_dp(nums, i - 1, j);
    int leftDIagonal = without_dp(nums, i - 1, j - 1);
    int rightDIagonal = without_dp(nums, i - 1, j + 1);

    return nums[i][j] + std::max(top, std::max(leftDIagonal, rightDIagonal));
}

int memoization(vector<vector<int>> &nums, int i, int j, vector<vector<int>> &dp)
{
    if (j < 0 or j == nums[0].size())
        return INT_MIN;

    if (i == 0)
        return nums[i][j];

    if (dp[i][j] != -1)
        return dp[i][j];

    int top = memoization(nums, i - 1, j, dp);
    int leftDIagonal = memoization(nums, i - 1, j - 1, dp);
    int rightDIagonal = memoization(nums, i - 1, j + 1, dp);

    return dp[i][j] = nums[i][j] + std::max(top, std::max(leftDIagonal, rightDIagonal));
}
int tabulation(vector<vector<int>> &nums)
{
    if (nums.size() == 0)
        return 0;
    int c = nums.size(), r = nums[0].size();
    vector<vector<int>> dp(r, vector<int>(c, 0));
    for (int j = 0; j < c; j++)
    {
        dp[0][j] = nums[0][j];
    }
    for (int i = 1; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int top{INT_MIN}, leftDiagonal{INT_MIN}, rightDiagonal{INT_MIN};
            top = dp[i - 1][j];
            if (j > 0)
                leftDiagonal = dp[i - 1][j - 1];
            if (j < c - 1)
                rightDiagonal = dp[i - 1][j + 1];
            dp[i][j] = nums[i][j] + std::max(top, std::max(leftDiagonal, rightDiagonal));
        }
    }
    auto lastRow = dp[r - 1];
    return *max_element(lastRow.begin(), lastRow.end());
}
int tabulation_with_SO(vector<vector<int>> &nums)
{
    if (nums.size() == 0)
        return 0;
    int c = nums.size(), r = nums[0].size();
    vector<int> dp(c, 0);
    for (int j = 0; j < c; j++)
    {
        dp[j] = nums[0][j];
    }
    for (int i = 1; i < r; i++)
    {
        vector<int> next(c, 0);
        for (int j = 0; j < c; j++)
        {
            int top{INT_MIN}, leftDiagonal{INT_MIN}, rightDiagonal{INT_MIN};
            top = dp[j];
            if (j > 0)
                leftDiagonal = dp[j - 1];
            if (j < c - 1)
                rightDiagonal = dp[j + 1];
            next[j] = nums[i][j] + std::max(top, std::max(leftDiagonal, rightDiagonal));
        }
        dp=next;
    }
    return *max_element(dp.begin(), dp.end());
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
    int res{INT_MIN};
    for (int j = 0; j < c; j++)
    {
        res = std::max(res, without_dp(nums, r - 1, j));
    }
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(3^r) \nSpace complexity: O(r) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp1(r, vector<int>(c, -1));
    int res2{INT_MIN};
    for (int j = 0; j < c; j++)
    {
        res2 = std::max(res, memoization(nums, r - 1, j, dp1));
    }
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(r*c) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(nums);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(r*c) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(nums);
    cout << "Tabulation With SO : "<<res4 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(c) " << endl;
}
