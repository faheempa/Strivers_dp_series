// Question : https://www.codingninjas.com/codestudio/problems/total-unique-paths_1081470?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int without_dp(int i, int j)
{
    if (i == 0 and j == 0)
        return 1;
    if (i < 0 or j < 0)
        return 0;

    int up = without_dp(i - 1, j);
    int left = without_dp(i, j - 1);

    return up + left;
}

int memoization(int i, int j, vector<vector<int>> &dp)
{
    if (i == 0 and j == 0)
        return 1;

    if (i < 0 or j < 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int up = without_dp(i - 1, j);
    int left = without_dp(i, j - 1);

    return dp[i][j] = up + left;
}
int tabluation(int r, int c)
{
    vector<vector<int>> dp(r, vector<int>(c, 0));
    dp[0][0] = 1;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == 0 and j == 0)
                continue;

            int up{0}, left{0};

            if (i > 0)
                left = dp[i - 1][j];

            if (j > 0)
                up = dp[i][j - 1];

            dp[i][j] = left + up;
        }
    }
    return dp[r - 1][c - 1];
}
int tabluation_with_SO(int r, int c)
{
    vector<int> dp(c, 0);
    for (int i = 0; i < r; i++)
    {
        vector<int> temp(c, 0);
        for (int j = 0; j < c; j++)
        {
            if (i == 0 and j == 0)
                temp[j] = 1;
            else
            {
                int top{0}, left{0};
                if (i > 0)
                    left = dp[j];

                if (j > 0)
                    top = temp[j - 1];

                temp[j] = left + top;
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
    // Without dp
    int ans = without_dp(r - 1, c - 1);
    cout << "Without DP: " << ans << endl;
    cout << "Time complexity: O(2^(r*c)) \nSpace complexity: O(r+c) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(r, vector<int>(c, -1));
    int ans2 = memoization(r - 1, c - 1, dp);
    cout << "Memoization: " << ans2 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(r*c) " << endl;
    cout << endl;

    // tabulation
    int ans3 = tabluation(r, c);
    cout << "Tabluation : " << ans3 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(r*c) " << endl;
    cout << endl;

    // tabulation with space optimization
    int ans4 = tabluation(r, c);
    cout << "Tabulation With SO : " << ans4 << endl;
    cout << "Time complexity: O(r*c) \nSpace complexity: O(c) " << endl;
}

