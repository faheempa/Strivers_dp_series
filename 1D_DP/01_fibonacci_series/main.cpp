// Question
// find nth fibonacci number

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int solve_without_dp(int n)
{
    if (n == 0 or n == 1)
        return n;
    return solve_without_dp(n - 1) + solve_without_dp(n - 2);
}
int solve(int n, vector<int> &dp)
{
    if (n == 0 or n == 1)
        return n;
    if (dp.at(n) != -1)
        return dp.at(n);
    return dp.at(n) = solve(n - 1, dp) + solve(n - 2, dp);
}

int main()
{
    // input
    int n;
    cin >> n;

    // Without dp
    int ans1 = solve_without_dp(n);
    cout << "Without Dp: " << ans1 << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<int> dp(n + 1, -1);
    int ans2 = solve(n, dp);
    cout << "Memoization: " << ans2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n)+O(n) " << endl;
    cout << endl;

    // tabulation
    vector<int> dp2(n + 1, -1);
    dp2.at(0) = 0;
    dp2.at(1) = 1;
    for (int i = 2; i <= n; i++)
    {
        dp2.at(i) = dp2.at(i - 1) + dp2.at(i - 2);
    }
    int ans3 = dp2.at(n);
    cout << "Tabluation : " << ans3 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization
    int prev2 = 0, prev1 = 1, value;
    for (int i = 2; i <= n; i++)
    {
        value = prev1 + prev2;
        prev2 = prev1;
        prev1 = value;
    }
    int ans4 = value;
    cout << "Tabulation With SO : " << ans4 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1) " << endl;

    return 0;
}
