// Question:  https://www.codingninjas.com/codestudio/problems/maze-obstacles_977241?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int without_dp(int i, int j, vector<vector<int>> &nums)
{
    if (i < 0 or j < 0 or nums[i][j] == 1)
        return 0;

    if (i == 0 and j == 0)
        return 1;

    int up = without_dp(i - 1, j, nums);
    int left = without_dp(i, j - 1, nums);

    return up + left;
}

int memoization(int i, int j, vector<vector<int>> &nums, vector<vector<int>> &dp)
{
    if (i < 0 or j < 0 or nums[i][j] == 1)
        return 0;

    if (i == 0 and j == 0)
        return 1;

    if (dp[i][j] != -1)
        return dp[i][j];

    int up = memoization(i - 1, j, nums, dp);
    int left = memoization(i, j - 1, nums, dp);

    return dp[i][j] = up + left;
}
int tabluation(int r, int c, vector<vector<int>> &nums)
{
    vector<vector<int>> dp(r, vector<int>(c, 0));
    dp[0][0] = (nums[0][0] == 0) ? 1 : 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == 0 and j == 0)
                continue;

            if (nums[i][j] == 1)
            {
                dp[i][j] = 0;
            }
            else
            {
                if (i > 0) // up
                    dp[i][j] += dp[i - 1][j];

                if (j > 0) // left
                    dp[i][j] += dp[i][j - 1];
            }
        }
    }
    return dp[r - 1][c - 1];
}
int tabluation_with_SO(int r, int c, vector<vector<int>> &nums)
{
    vector<int> dp(c, 0);
    for (int i = 0; i < r; i++)
    {
        vector<int> temp(c, 0);
        for (int j = 0; j < c; j++)
        {
            if (i == 0 and j == 0)
            {
                temp[j] = (nums[0][0] == 0) ? 1 : 0;
            }
            else if (nums[i][j] == 1)
            {
                temp[j] = 0;
            }
            else
            {
                if (i > 0) // up
                    temp[j] += dp[j];

                if (j > 0) // left
                    temp[j] += temp[j - 1];
            }
        }
        dp = temp;
    }
    return dp[c - 1];
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
            int a;
            cin >> a;
            nums[i][j] = a;
        }
    }
    // Without dp
    int ans = without_dp(r - 1, c - 1, nums);
    cout << "Without DP: " << ans << endl;
    cout << "Time complexity: O(2^(r*c)) \nSpace complexity: O(r+c) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(r, vector<int>(c, -1));
    int ans2 = memoization(r - 1, c - 1, nums, dp);
    cout << "Memoization: " << ans2 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(r*c) " << endl;
    cout << endl;

    // tabulation
    int ans3 = tabluation(r, c, nums);
    cout << "Tabluation : " << ans3 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(r*c) " << endl;
    cout << endl;

    // tabulation with space optimization
    int ans4 = tabluation_with_SO(r, c, nums);
    cout << "Tabulation With SO : " << ans4 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(c) " << endl;
}
