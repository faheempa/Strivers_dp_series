// Question : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

#include <bits/stdc++.h>
using namespace std;

int memoization(int i, vector<int> &prices, int count, vector<vector<int>> &dp, int &k)
{
    // base conditions
    if (i == prices.size() or count == 2 * k)
        return 0;
    // if already solved
    if (dp[i][count] != -1)
        return dp[i][count];
    // exploration
    int profit{0};
    if (count % 2 == 0) // buy
    {
        int buy = memoization(i + 1, prices, count + 1, dp, k) - prices[i];
        int notbuy = memoization(i + 1, prices, count, dp, k);
        profit = std::max(buy, notbuy);
    }
    else // sell
    {
        int sell = memoization(i + 1, prices, count + 1, dp, k) + prices[i];
        int notSell = memoization(i + 1, prices, count, dp, k);
        profit = std::max(sell, notSell);
    }
    // return
    return dp[i][count] = profit;
}

int tabulation_with_SO(vector<int> &prices, int &k)
{
    int maxCount = 2 * k;
    int n = prices.size();
    vector<int> dp(maxCount + 1, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int count = 0; count < maxCount; count++)
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
    int k;
    cin >> k;

    // memoization
    vector<vector<int>> dp(n, vector<int>(2 * k, -1));
    int res1 = memoization(0, prices, 0, dp, k);
    cout << "Memoization: " << res1 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res2 = tabulation_with_SO(prices, k);
    cout << "Tabulation With SO : " << res2 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(k) " << endl;
    cout << endl;
}
