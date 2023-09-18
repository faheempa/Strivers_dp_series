// Question : https://leetcode.com/problems/longest-increasing-subsequence/

#include <bits/stdc++.h>
using namespace std;

int tabulation_with_binary_search(vector<int> &nums)
{
    int n = nums.size();
    vector<int> temp;
    temp.push_back(nums[0]);
    for (int i = 1; i < n; i++)
    {
        if(nums[i]>temp.back())
        {
            temp.push_back(nums[i]);
        }
        else
        {
            auto it = std::lower_bound(temp.begin(), temp.end(), nums[i]);
            *it = nums[i];
        }
    }
    return temp.size();
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto &i : nums)
        cin >> i;

    // tabulation with binary search (we cant print the sequence)
    int res = tabulation_with_binary_search(nums);
    cout << "Tabulation With Binary Search : " << res << endl;
    cout << "Time complexity: O(nlogn) \nSpace complexity: O(n) " << endl;
    cout << endl;
}
