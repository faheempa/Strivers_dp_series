// Question
// https://www.codingninjas.com/codestudio/problems/maximum-sum-of-non-adjacent-elements_843261?

#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int solve_without_dp(vector<int> &arr, int idx)
{
    if (idx == 0)
        return arr.at(idx);
    if (idx < 0)
        return 0;

    int pick = arr.at(idx) + solve_without_dp(arr, idx - 2);
    int notpick = 0 + solve_without_dp(arr, idx - 1);
    return std::max(pick, notpick);
}
int solve(vector<int> &arr, int idx, vector<int> &dp)
{
    if (idx == 0)
        return arr.at(idx);
    if (idx < 0)
        return 0;
    if (dp.at(idx) != -1)
        return dp.at(idx);

    int pick = arr.at(idx) + solve(arr, idx - 2, dp);
    int notpick = 0 + solve(arr, idx - 1, dp);
    return dp.at(idx) = std::max(pick, notpick);
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        arr.push_back(a);
    }
    // Without dp
    int sum0 = solve_without_dp(arr, n - 1);
    cout << "Without Dp: " << sum0 << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n)" << endl;
    cout << endl;

    // memoization
    vector<int> dp(n, -1);
    int sum1 = solve(arr, n - 1, dp);
    cout << "Memoization: " << sum1 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n)" << endl;
    cout << endl;

    // tabulation
    vector<int> dp2(n, -1);
    dp2[0] = arr[0];
    int negative = -1;
    for (int i = 1; i < n; i++)
    {
        int pick = arr.at(i);
        if (i - 2 > negative)
            pick += dp2.at(i - 2);
        int notpick = dp2.at(i - 1);
        dp2.at(i) = std::max(pick, notpick);
    }
    int sum2 = dp2.at(n - 1);
    cout << "Tabluation : " << sum2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n)" << endl;
    cout << endl;

    // tabulation with space optimization
    int prev1 = arr[0], prev2 = 0;
    for (int i = 1; i < n; i++)
    {
        int pick = arr.at(i) + prev2;
        int notpick = prev1;
        prev2 = prev1;
        prev1 = std::max(pick, notpick);
    }
    int sum3 = prev1;
    cout << "Tabulation With SO : " << sum3 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1)" << endl;

    return 0;
}
