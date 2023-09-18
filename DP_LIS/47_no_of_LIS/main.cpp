// Question : https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/

#include <bits/stdc++.h>
using namespace std;

int LIS_modified(vector<int> &nums)
{
    int n = nums.size(), maxLen{0};
    vector<int> dp(n, 1);
    vector<int> count(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int prevIndex = 0; prevIndex < i; prevIndex++)
        {
            if (nums[prevIndex] < nums[i])
            {
                if (dp[prevIndex] + 1 > dp[i])
                {
                    dp[i] = dp[prevIndex] + 1;
                    count[i] = count[prevIndex];
                }
                else if (dp[prevIndex] + 1 == dp[i])
                {
                    count[i] += count[prevIndex];
                }
            }
        }
        maxLen = max(maxLen, dp[i]);
    }
    int res{0};
    for (int i = 0; i < n; i++)
    {
        if (dp[i] == maxLen)
            res += count[i];
    }
    return res;
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto &i : nums)
        cin >> i;

    // output
    int res = LIS_modified(nums);
    cout << "No of LIS: " << res << endl;
    cout << "Time Complexity: O(n^2)" << endl;
    cout << "Space Complexity: O(n)" << endl;
}