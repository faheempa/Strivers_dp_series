// Question : https://leetcode.com/problems/partition-array-for-maximum-sum/

#include <bits/stdc++.h>
using namespace std;

int solve(int i, vector<int> &nums, int n, int k)
{
    // base
    if (i == n)
        return 0;
    // explore
    int res{0}, maxIndex{i}, len{0};
    for (int j = i; j < min(n, i + k); j++)
    {
        len++;
        if (nums[j] > nums[maxIndex])
            maxIndex = j;
        int sum = len * nums[maxIndex] + solve(j + 1, nums, n, k);
        res = max(res, sum);
    }
    // return
    return res;
}
int memoization(int i, vector<int> &nums, int n, int k, vector<int> &dp)
{
    // base
    if (i == n)
        return 0;
    // already solved?
    if (dp[i] != -1)
        return dp[i];
    // explore
    int res{0}, maxIndex{i}, len{0};
    for (int j = i; j < min(n, i + k); j++)
    {
        len++;
        if (nums[j] > nums[maxIndex])
            maxIndex = j;
        int sum = len * nums[maxIndex] + memoization(j + 1, nums, n, k, dp);
        res = max(res, sum);
    }
    // return
    return dp[i] = res;
}
int tabulation(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<int> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        int res{0}, maxIndex{i}, len{0};
        for (int j = i; j < min(n, i + k); j++)
        {
            len++;
            if (nums[j] > nums[maxIndex])
                maxIndex = j;
            int sum = len * nums[maxIndex] + dp[j + 1];
            res = max(res, sum);
        }
        dp[i] = res;
    }
    return dp[0];
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto &i : nums)
        cin >> i;
    int k;
    cin >> k;

    // // Without dp
    int res = solve(0, nums, nums.size(), k);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(exponential) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<int> dp(nums.size() + 1, -1);
    int res2 = memoization(0, nums, nums.size(), k, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(nums, k);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;
}
