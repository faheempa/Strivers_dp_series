// Question
// https://takeuforward.org/data-structure/dynamic-programming-frog-jump-dp-3/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int solve_without_dp(int n)
{
    if (n <= 1)
        return 1;
    int one_step = solve_without_dp(n - 1);
    int two_step = solve_without_dp(n - 2);
    return one_step + two_step;
}

int solve(int n, vector<int> &dp)
{
    if (n <= 1)
        return 1;
    if (dp.at(n) != -1)
        return dp.at(n);
    int one_step = solve(n - 1, dp);
    int two_step = solve(n - 2, dp);
    return dp.at(n) = one_step + two_step;
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
    dp2.at(0) = 1;
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
    int one_step, two_step, value;
    one_step = 1;
    two_step = 1;
    for (int i = 2; i <= n; i++)
    {
        value = one_step + two_step;
        one_step = two_step;
        two_step = value;
    }
    int ans4=value;
    cout << "Tabulation With SO : "<<ans4 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(1) " << endl;
}
