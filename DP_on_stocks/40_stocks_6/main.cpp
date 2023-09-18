// Question : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

#include <bits/stdc++.h>
using namespace std;

int memoization(int i, int canBuy, vector<int> &prices, vector<vector<int>> &dp, int &fee)
{
    // base conditions
    if (i == prices.size())
        return 0;
    // if already solved
    if (dp[i][canBuy] != -1)
        return dp[i][canBuy];
    // explorations
    int profit{0};
    if (canBuy)
    {
        int buy = memoization(i + 1, 0, prices, dp, fee) - prices[i] - fee;
        int notBuy = memoization(i + 1, 1, prices, dp, fee);
        profit = max(buy, notBuy);
    }
    else
    {
        int sell = memoization(i + 1, 1, prices, dp, fee) + prices[i];
        int notsell = memoization(i + 1, 0, prices, dp, fee);
        profit = max(sell, notsell);
    }
    // return
    return dp[i][canBuy] = profit;
}

int tabulation_with_SO(vector<int> &prices, int &fee)
{
    int n = prices.size();
    vector<int> dp(2, 0), cur(2, 0);
    // loop
    for (int i = n - 1; i >= 0; i--)
    {
        cur[1] = max(dp[1], dp[0] - prices[i] - fee);
        cur[0] = max(dp[0], dp[1] + prices[i]);
        dp = cur;
    }
    // return
    return dp[1];
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> prices(n);
    for (auto &i : prices)
        cin >> i;
    int fee;
    cin >> fee;

    // memoization
    vector<vector<int>> dp(n, vector<int>(2, -1));
    int res2 = memoization(0, 1, prices, dp, fee);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(prices, fee);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1) " << endl;
    cout << endl;
}
