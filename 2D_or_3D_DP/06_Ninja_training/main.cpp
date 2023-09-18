// Question : https://www.codingninjas.com/codestudio/problems/ninja-s-training_3621003

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int without_dp(vector<vector<int>> &costs, int day, int last)
{
    int val{0}, cur_task;

    if (day == 0)
    {
        for (size_t i = 0; i < 3; i++)
            if (i != last)
                val = std::max(val, costs[day][i]);

        return val;
    }

    if (last != 0)
        val = std::max(without_dp(costs, day - 1, 0) + costs[day][0], val);
    if (last != 1)
        val = std::max(without_dp(costs, day - 1, 1) + costs[day][1], val);
    if (last != 2)
        val = std::max(without_dp(costs, day - 1, 2) + costs[day][2], val);

    return val;
}

int memoization(vector<vector<int>> &costs, int day, int last, vector<vector<int>> &dp)
{
    int val{0};

    if (day == 0)
    {
        for (size_t i = 0; i < 3; i++)
            if (i != last)
                val = std::max(val, costs[day][i]);

        return dp[day][last] = val;
    }

    if (dp[day][last] != -1)
        return dp[day][last];

    for (size_t i = 0; i < 3; i++)
        if (i != last)
            val = std::max(memoization(costs, day - 1, i, dp) + costs[day][i], val);

    return dp[day][last] = val;
}
int tabluation(vector<vector<int>> &costs, int r)
{
    vector<vector<int>> dp(r, vector<int>(4, 0));
    dp[0][0] = std::max(costs[0][1], costs[0][2]);
    dp[0][1] = std::max(costs[0][0], costs[0][2]);
    dp[0][2] = std::max(costs[0][1], costs[0][0]);
    dp[0][3] = std::max(costs[0][1], std::max(costs[0][2], costs[0][0]));

    if (r == 1)
        return dp[0][3];

    for (int day = 1; day < r; day++)
    {
        for (size_t prev = 0; prev < 4; prev++)
        {
            int max_val{0};
            for (size_t cur = 0; cur < 3; cur++)
            {
                if (cur != prev)
                {
                    max_val = std::max(max_val, costs[day][cur] + dp[day - 1][cur]);
                }
            }
            dp[day][prev] = std::max(max_val, dp[day][prev]);
        }
    }
    return dp[r - 1][3];
}
int tabluation_with_SO(vector<vector<int>> &costs, int r)
{
    vector<int> dp(4, 0);
    dp[0] = std::max(costs[0][1], costs[0][2]);
    dp[1] = std::max(costs[0][0], costs[0][2]);
    dp[2] = std::max(costs[0][1], costs[0][0]);
    dp[3] = std::max(costs[0][1], std::max(costs[0][2], costs[0][0]));

    if (r == 1)
        return dp[3];

    for (int i = 1; i < r; i++)
    {
        vector<int> temp(4, 0);
        for (size_t prev = 0; prev < 4; prev++)
        {
            int max_val{0};
            for (size_t cur = 0; cur < 3; cur++)
            {
                if (cur != prev)
                {
                    max_val = std::max(max_val, costs[i][cur] + dp[cur]);
                }
            }
            temp[prev] = std::max(max_val, dp[prev]);
        }
        dp = temp;
    }
    return dp[3];
}

int main()
{
    // input
    int r, c = 3;
    cin >> r;
    vector<vector<int>> costs(r, vector<int>(c));
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int a;
            cin >> a;
            costs[i][j] = a;
        }
    }

    // Without dp
    int ans = without_dp(costs, r - 1, 3);
    cout << "Without DP: " << ans << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: 0(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(r, vector<int>(4, -1));
    int ans2 = memoization(costs, r - 1, 3, dp);
    cout << "Memoization: " << ans2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation
    int ans3 = tabluation(costs, r);
    cout << "Tabluation : " << ans3 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization
    int ans4 = tabluation_with_SO(costs, r);
    cout << "Tabulation With SO : " << ans << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1) " << endl;
}
