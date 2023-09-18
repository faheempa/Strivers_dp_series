// Question : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> &prices)
{
    int profit = 0, min = 1e4;
    for (int &x : prices)
    {
        min = std::min(min, x);
        profit = std::max(profit, x - min);
    }
    return profit;
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &i : arr)
        cin >> i;
    int ans = solve(arr);
    cout << "Max profit: " << ans << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1) " << endl;
    cout << endl;
}
