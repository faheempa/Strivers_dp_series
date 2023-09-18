// Question : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, vector<int> &prices, int count)
{
    // base conditions
    if (i == prices.size() or count == 4)
        return 0;
    // exploration
    int profit{0};
    if (count % 2 == 0) // buy
    {
        int buy = solve(i + 1, prices, count + 1) - prices[i];
        int notbuy = solve(i + 1, prices, count);
        profit = std::max(buy, notbuy);
    }
    else // sell
    {
        int sell = solve(i + 1, prices, count + 1) + prices[i];
        int notSell = solve(i + 1, prices, count);
        profit = std::max(sell, notSell);
    }
    // return
    return profit;
}

int memoization(int i, vector<int> &prices, int count, vector<vector<int>> &dp)
{
    // base conditions
    if (i == prices.size() or count == 4)
        return 0;
    // if already solved
    if (dp[i][count] != -1)
        return dp[i][count];
    // exploration
    int profit{0};
    if (count % 2 == 0) // buy
    {
        int buy = memoization(i + 1, prices, count + 1, dp) - prices[i];
        int notbuy = memoization(i + 1, prices, count, dp);
        profit = std::max(buy, notbuy);
    }
    else // sell
    {
        int sell = memoization(i + 1, prices, count + 1, dp) + prices[i];
        int notSell = memoization(i + 1, prices, count, dp);
        profit = std::max(sell, notSell);
    }
    // return
    return dp[i][count] = profit;
}
int tabulation(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n + 1, vector<int>(5, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int count = 0; count < 4; count++)
        {
            int profit{0};
            if (count % 2 == 0) // buy
            {
                int buy = dp[i + 1][count + 1] - prices[i];
                int notbuy = dp[i + 1][count];
                profit = std::max(buy, notbuy);
            }
            else // sell
            {
                int sell = dp[i + 1][count + 1] + prices[i];
                int notSell = dp[i + 1][count];
                profit = std::max(sell, notSell);
            }
            dp[i][count] = profit;
        }
    }
    return dp[0][0];
}
int tabulation_with_SO(vector<int> &prices)
{
    int n = prices.size();
    vector<int> dp(5, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int count = 0; count < 4; count++)
        {
            int profit{0};
            if (count % 2 == 0) // buy
            {
                int buy = dp[count + 1] - prices[i];
                int notbuy = dp[count];
                profit = std::max(buy, notbuy);
            }
            else // sell
            {
                int sell = dp[count + 1] + prices[i];
                int notSell = dp[count];
                profit = std::max(sell, notSell);
            }
            dp[count] = profit;
        }
    }
    return dp[0];
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> prices(n);
    for (auto &i : prices)
        cin >> i;

    // Without dp
    int res = solve(0, prices, 0);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n, vector<int>(4, -1));
    int res2 = memoization(0, prices, 0, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(prices);
    cout << "Tabulation : " <<res3<< endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(prices);
    cout << "Tabulation With SO : "<<res4 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1) " << endl;
    cout << endl;
}
