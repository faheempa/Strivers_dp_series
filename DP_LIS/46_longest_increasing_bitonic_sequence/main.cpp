// Question : https://www.codingninjas.com/studio/problems/longest-bitonic-sequence_1062688

#include <bits/stdc++.h>
using namespace std;

int LIS_modified(vector<int> &nums)
{
    // increasing from left to right
    int n = nums.size();
    vector<int> dp1(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int prevIndex = 0; prevIndex < i; prevIndex++)
        {
            if (nums[prevIndex] < nums[i] and dp1[i] < dp1[prevIndex] + 1)
            {
                dp1[i] = dp1[prevIndex] + 1;
            }
        }
    }
    // increasing from right to left
    vector<int> dp2(n, 1);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int prevIndex = n - 1; prevIndex > i; prevIndex--)
        {
            if (nums[prevIndex] < nums[i] and dp2[i] < dp2[prevIndex] + 1)
            {
                dp2[i] = dp2[prevIndex] + 1;
            }
        }
    }
    // sum up
    int res;
    for (int i = 0; i < n; i++)
    {
        res = std::max(res, dp1[i] + dp2[i] - 1);
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
    cout << "max lenght: " << res << endl;
    cout << "Time Complexity: O(n^2)" << endl;
    cout << "Space Complexity: O(n)" << endl;
}
