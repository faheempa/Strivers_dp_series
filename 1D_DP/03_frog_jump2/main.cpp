// Question
// https://takeuforward.org/data-structure/dynamic-programming-frog-jump-dp-3/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int solve_without_dp(vector<int> &arr, int n)
{
    if (n < 2)
        return 0;
    int one_step = 0, two_step = 0;
    one_step = solve_without_dp(arr, n - 1) + abs(arr.at(n) - arr.at(n - 1));
    two_step = solve_without_dp(arr, n - 2) + abs(arr.at(n) - arr.at(n - 2));
    return std::min(one_step, two_step);
}

int solve(vector<int> &arr, int n, vector<int> &dp)
{
    if (n < 2)
        return 0;
    if (dp.at(n) != -1)
        return dp.at(n);
    int one_step = 0, two_step = 0;
    one_step = solve(arr, n - 1, dp) + abs(arr.at(n) - arr.at(n - 1));
    two_step = solve(arr, n - 2, dp) + abs(arr.at(n) - arr.at(n - 2));
    return dp.at(n) = std::min(one_step, two_step);
}

int main()
{
    // input
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
    int ans0 = solve_without_dp(arr, n - 1);
    cout << "Without Dp: " << ans0 << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n)" << endl;
    cout << endl;

    // memoization
    vector<int> dp(n, -1);
    int ans1 = solve(arr, n - 1, dp);
    cout << "Memoization: " << ans1 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n)+O(n)" << endl;
    cout << endl;

    // tabulation
    vector<int> dp2(n, -1);
    dp2.at(0) = 0;
    dp2.at(1) = abs(arr.at(0) - arr.at(1));
    int one_step, two_step;
    for (int i = 2; i < n; i++)
    {
        one_step = dp2.at(i - 1) + abs(arr.at(i) - arr.at(i - 1));
        two_step = dp2.at(i - 2) + abs(arr.at(i) - arr.at(i - 2));
        dp2.at(i) = std::min(one_step, two_step);
    }
    int ans2 = dp2.at(n - 1);
    cout << "Tabluation : " << ans2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n)" << endl;
    cout << endl;

    // tabulation with space optimization
    int prev2 = 0, prev1 = abs(arr.at(0) - arr.at(1));
    for (int i = 2; i < n; i++)
    {
        int one_step = prev1 + abs(arr.at(i) - arr.at(i - 1));
        int two_step = prev2 + abs(arr.at(i) - arr.at(i - 2));
        prev2 = prev1;
        prev1 = std::min(one_step, two_step);
    }
    int ans3 = prev1;
    cout << "Tabulation With SO : " << ans2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1)" << endl;
}
