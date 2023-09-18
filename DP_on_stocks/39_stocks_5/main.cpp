// Question : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, int canBuy, vector<int> &prices)
{
    // base conditions
    if (i >= prices.size())
        return 0;
    // explorations
    int profit{0};
    if (canBuy)
    {
        int buy = solve(i + 1, 0, prices) - prices[i];
        int notBuy = solve(i + 1, 1, prices);
        profit = max(buy, notBuy);
    }
    else
    {
        int sell = solve(i + 2, 1, prices) + prices[i];
        int notsell = solve(i + 1, 0, prices);
        profit = max(sell, notsell);
    }
    // return
    return profit;
}

int memoization(int i, int canBuy, vector<int> &prices, vector<vector<int>> &dp)
{
    // base conditions
    if (i >= prices.size())
        return 0;
    // if already solved
    if (dp[i][canBuy] != -1)
        return dp[i][canBuy];
    // explorations
    int profit{0};
    if (canBuy)
    {
        int buy = memoization(i + 1, 0, prices, dp) - prices[i];
        int notBuy = memoization(i + 1, 1, prices, dp);
        profit = max(buy, notBuy);
    }
    else
    {
        int sell = memoization(i + 2, 1, prices, dp) + prices[i];
        int notsell = memoization(i + 1, 0, prices, dp);
        profit = max(sell, notsell);
    }
    // return
    return dp[i][canBuy] = profit;
}
int tabulation(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n + 2, vector<int>(2, 0));
    // loop
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i][1] = max(dp[i + 1][1], dp[i + 1][0] - prices[i]);
        dp[i][0] = max(dp[i + 1][0], dp[i + 2][1] + prices[i]);
    }
    // return
    return dp[0][1];
}
int tabulation_with_SO(vector<int> &prices)
{
    int n = prices.size();
    vector<int> ahead1(2, 0), ahead2(2, 0), cur(2, 0);
    // loop
    for (int i = n - 1; i >= 0; i--)
    {
        cur[1] = max(ahead1[1], ahead1[0] - prices[i]);
        cur[0] = max(ahead1[0], ahead2[1] + prices[i]);
        ahead2 = ahead1;
        ahead1 = cur;
    }
    // return
    return cur[1];  
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
    int res = solve(0, 1, prices);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: (2^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n+1, vector<int>(2, -1));
    int res2 = memoization(0, 1, prices, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(prices);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(prices);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1) " << endl;
    cout << endl;
}
