// Question : https://leetcode.com/problems/largest-divisible-subset/

#include <bits/stdc++.h>
using namespace std;

vector<int> LIS_modified(vector<int> &nums)
{
    int n = nums.size();
    std::sort(nums.begin(), nums.end());
    vector<int> dp(n, 1);
    vector<int> prev(n);
    for (int i = 0; i < n; i++)
        prev[i] = i;
    for (int i = 0; i < n; i++)
    {
        for (int prevIndex = 0; prevIndex < i; prevIndex++)
        {
            if (nums[i] % nums[prevIndex] == 0 and dp[i] < dp[prevIndex] + 1)
            {
                dp[i] = dp[prevIndex] + 1;
                prev[i] = prevIndex;
            }
        }
    }

    // get maxIndex and traverse back to get the LIS
    int maxIndex = std::max_element(dp.begin(), dp.end()) - dp.begin();
    vector<int> ans;
    while (prev[maxIndex] != maxIndex)
    {
        ans.push_back(nums[maxIndex]);
        maxIndex = prev[maxIndex];
    }
    ans.push_back(nums[maxIndex]);
    return ans;
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
    vector<int> ans = LIS_modified(nums);
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}
