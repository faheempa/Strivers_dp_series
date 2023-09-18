// Question
// https://www.codingninjas.com/codestudio/problems/house-robber_839733?source=youtube&campaign=striver_dp_videos&utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_dp_videos

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int without_dp(vector<int> &arr, int idx, int limit)
{
    if (idx == limit)
        return arr.at(idx);
    if (idx < limit)
        return 0;

    int pick = arr.at(idx) + without_dp(arr, idx - 2, limit);
    int notpick = 0 + without_dp(arr, idx - 1, limit);
    return std::max(pick, notpick);
}

int memoization(vector<int> &arr, int idx, int limit, vector<int> &dp)
{
    if (idx < limit)
        return 0;
    if (dp[idx] != -1)
        return dp[idx];
    if (idx == limit)
        return arr.at(idx);

    int pick = arr.at(idx) + memoization(arr, idx - 2, limit, dp);
    int notpick = 0 + memoization(arr, idx - 1, limit, dp);
    return dp[idx] = std::max(pick, notpick);
}
int tabluation(vector<int> &arr, int start, int limit)
{
    vector<int> dp(start + 1, -1);
    int ans;
    dp[limit] = arr[limit];

    for (int i = limit + 1; i <= start; i++)
    {
        int pick = arr[i];
        if (i - 2 > limit)
            pick += dp[i - 2];

        int no_pick = dp[i - 1];
        dp[i] = std::max(pick, no_pick);
    }
    return dp[start];
}
int tabluation_with_SO(vector<int> &arr, int end, int limit)
{
    int prev1 = arr[limit], prev2 = 0;
    for (int i = limit + 1; i <= end; i++)
    {
        int pick = arr.at(i) + prev2;
        int notpick = prev1;
        prev2 = prev1;
        prev1 = std::max(pick, notpick);
    }
    return prev1;
}

int main()
{
    // input
    vector<int> nums;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        nums.push_back(a);
    }

    // Without dp
    int ans = std::max(without_dp(nums, n - 1, 1), without_dp(nums, n - 2, 0));
    cout << "Without DP: " << ans << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<int> dp(n, -1);
    int ans2 = std::max(memoization(nums, n - 1, 1, dp), memoization(nums, n - 2, 0, dp));
    cout << "Memoization: " << ans2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation
    int ans3 = std::max(tabluation(nums, n - 1, 1), tabluation(nums, n - 2, 0));
    cout << "Tabluation : " << ans3 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization
    int ans4 = std::max(tabluation_with_SO(nums, n - 1, 1), tabluation_with_SO(nums, n - 2, 0));
    cout << "Tabulation With SO : " << ans4 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1) " << endl;
}
