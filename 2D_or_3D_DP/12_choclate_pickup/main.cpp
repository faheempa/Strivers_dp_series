// Question :

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int without_dp(int i, int j1, int j2, vector<vector<int>> &nums)
{
    // base conditions
    if (j1 < 0 or j2 < 0 or j1 == nums[0].size() or j2 == nums[0].size())
    {
        return INT_MIN;
    }
    if (i == nums.size() - 1)
    {
        if (j1 == j2)
            return nums[i][j1];
        else
            return nums[i][j1] + nums[i][j2];
    }
    // explore all paths
    int ans{INT_MIN};
    for (int d1 = -1; d1 <= 1; d1++)
    {
        for (int d2 = -1; d2 <= 1; d2++)
        {
            int val = without_dp(i + 1, j1 + d1, j2 + d2, nums);
            if (j1 == j2)
                val = val + nums[i][j1];
            else
                val = val + nums[i][j1] + nums[i][j2];
            ans = std::max(ans, val);
        }
    }
    return ans;
}

int memoization(int i, int j1, int j2, vector<vector<int>> &nums, vector<vector<vector<int>>> &dp) // TC
{
    // base conditions
    if (j1 < 0 or j2 < 0 or j1 == nums[0].size() or j2 == nums[0].size())
    {
        return INT_MIN;
    }
    if (i == nums.size() - 1)
    {
        if (j1 == j2)
            return nums[i][j1];
        else
            return nums[i][j1] + nums[i][j2];
    }
    // check if already calculated
    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];
    // explore all paths
    int ans{INT_MIN};
    for (int d1 = -1; d1 <= 1; d1++)
    {
        for (int d2 = -1; d2 <= 1; d2++)
        {
            int val = memoization(i + 1, j1 + d1, j2 + d2, nums, dp);
            if (j1 == j2)
                val = val + nums[i][j1];
            else
                val = val + nums[i][j1] + nums[i][j2];
            ans = std::max(ans, val);
        }
    }
    return dp[i][j1][j2] = ans;
}
int tabulation(vector<vector<int>> &nums)
{
    int r = nums.size(), c = nums[0].size();
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));
    // base conditions (last row)
    for (int j1 = 0; j1 < c; j1++)
    {
        for (int j2 = 0; j2 < c; j2++)
        {
            if (j1 == j2)
                dp[r - 1][j1][j2] = nums[r - 1][j1];
            else
                dp[r - 1][j1][j2] = nums[r - 1][j1] + nums[r - 1][j2];
        }
    }
    // explore all paths
    for (int i = r - 2; i >= 0; i--)
    {
        for (int j1 = 0; j1 < c; j1++)
        {
            for (int j2 = 0; j2 < c; j2++)
            {
                int ans{INT_MIN};
                for (int d1 = -1; d1 <= 1; d1++)
                {
                    for (int d2 = -1; d2 <= 1; d2++)
                    {
                        // base conditions (out of bound)
                        if (j1 + d1 < 0 or j2 + d2 < 0 or j1 + d1 == c or j2 + d2 == c)
                            continue;

                        int val = dp[i + 1][j1 + d1][j2 + d2];
                        if (j1 == j2)
                            val = val + nums[i][j1];
                        else
                            val = val + nums[i][j1] + nums[i][j2];
                        ans = std::max(ans, val);
                    }
                }
                dp[i][j1][j2] = ans;
            }
        }
    }
    return dp[0][0][c - 1];
}
int tabulation_with_SO(vector<vector<int>> &nums)
{
    int r = nums.size(), c = nums[0].size();
    vector<vector<int>> down(c, vector<int>(c, -1));
    // base conditions (last row)
    for (int j1 = 0; j1 < c; j1++)
    {
        for (int j2 = 0; j2 < c; j2++)
        {
            if (j1 == j2)
                down[j1][j2] = nums[r - 1][j1];
            else
                down[j1][j2] = nums[r - 1][j1] + nums[r - 1][j2];
        }
    }
    // explore all paths
    for (int i = r - 2; i >= 0; i--)
    {
        vector<vector<int>> cur(c, vector<int>(c, -1));
        for (int j1 = 0; j1 < c; j1++)
        {
            for (int j2 = 0; j2 < c; j2++)
            {
                int ans{INT_MIN};
                for (int d1 = -1; d1 <= 1; d1++)
                {
                    for (int d2 = -1; d2 <= 1; d2++)
                    {
                        // base conditions (out of bound)
                        if (j1 + d1 < 0 or j2 + d2 < 0 or j1 + d1 == c or j2 + d2 == c)
                            continue;

                        int val = down[j1 + d1][j2 + d2];
                        if (j1 == j2)
                            val = val + nums[i][j1];
                        else
                            val = val + nums[i][j1] + nums[i][j2];
                        ans = std::max(ans, val);
                    }
                }
                cur[j1][j2] = ans;
            }
        }
        down = cur;
    }
    return down[0][c - 1];
}

int main()
{
    // input
    int r, c;
    cin >> r >> c;
    vector<vector<int>> nums(r, vector<int>(c));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> nums[i][j];
        }
    }

    // Without dp
    int res = without_dp(0, 0, c - 1, nums);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(3^n * 3^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));
    int res1 = memoization(0, 0, c - 1, nums, dp);
    cout << "Memoization: " << res1 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^3) " << endl;
    cout << endl;

    // tabulation
    int res2 = tabulation(nums);
    cout << "Tabulation : " << res2 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^3) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res3 = tabulation_with_SO(nums);
    cout << "Tabulation With SO : " << res3 << endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;
}
