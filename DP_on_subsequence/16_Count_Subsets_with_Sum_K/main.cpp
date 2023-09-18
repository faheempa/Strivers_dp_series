// Question : https://www.codingninjas.com/studio/problems/number-of-subsets_3952532

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int solve(vector<int> &nums, int index, int sum)
{
    // base case
    if (index == 0)
    {
        if (sum == 0 and nums[0] == 0)
            return 2;
        if (sum == 0 or sum == nums[0])
            return 1;
        return 0;
    }
    // explore
    int pick{0};
    if (nums[index] <= sum)
        pick = solve(nums, index - 1, sum - nums[index]);
    int notPick = solve(nums, index - 1, sum);
    // sum up
    return pick + notPick;
}

int memoization(vector<int> &nums, int index, int sum, vector<vector<int>> &dp)
{
    // base case
    if (index == 0)
    {
        if (sum == 0 and nums[0] == 0)
            return 2;
        if (sum == 0 or sum == nums[0])
            return 1;
        return 0;
    }
    // check if already calculated
    if (dp[index][sum] != -1)
        return dp[index][sum];
    // explore
    int pick{0};
    if (nums[index] <= sum)
        pick = memoization(nums, index - 1, sum - nums[index], dp);
    int notPick = memoization(nums, index - 1, sum, dp);
    // sum up
    return dp[index][sum] = pick + notPick;
}

int tabulation(vector<int> &nums, int sum)
{
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

    // base conditions
    if (nums[0] == 0)
        dp[0][0] = 2;
    else
        dp[0][0] = 1;

    if (nums[0] <= sum and nums[0] != 0)
        dp[0][nums[0]] = 1;
    // explore
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            int pick{0};
            if (nums[i] <= j)
                pick = dp[i - 1][j - nums[i]];
            int notPick = dp[i - 1][j];
            dp[i][j] = pick + notPick;
        }
    }

    // return
    return dp[n - 1][sum];
}
int tabulation_with_SO(vector<int> &nums, int sum)
{
    int n = nums.size();
    vector<int> dp(sum + 1, 0);
    if (nums[0] == 0)
        dp[0] = 2;
    else
        dp[0] = 1;
    if (nums[0] <= sum and nums[0] != 0)
        dp[nums[0]] = 1;
    // explore
    for (int index = 1; index < n; index++)
    {
        vector<int> temp(sum + 1, 0);
        temp[0] = 1;
        for (int target = 0; target <= sum; target++)
        {
            int pick{0};
            if (nums[index] <= target)
                pick = dp[target - nums[index]];
            int notPick = dp[target];
            temp[target] = pick + notPick;
        }
        dp = temp;
    }
    // return
    return dp[sum];
}

int main()
{
    // input
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (auto &a : nums)
        cin >> a;

    // Without dp
    int res = solve(nums, n - 1, k);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
    int res2 = memoization(nums, n - 1, k, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(n*k) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(nums, k);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(n*k) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(nums, k);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n*k) \nSpace complexity: O(k) " << endl;
    cout << endl;
}
