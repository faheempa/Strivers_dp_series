// Question : https://leetcode.com/problems/palindrome-partitioning-ii/

#include <bits/stdc++.h>
using namespace std;
bool isPalindrome(string &s)
{
    int i = 0, j = s.length() - 1;
    while (i < j && s[i] == s[j])
    {
        i++;
        j--;
    }
    return i >= j;
}
int solve(int i, string &s)
{
    // base
    if (i == s.length())
        return 0;
    // explore
    string temp;
    int res = 1e9;
    for (int j = i; j < s.length(); j++)
    {
        temp += s[j];
        if (isPalindrome(temp))
        {
            int cost = 1 + solve(j + 1, s);
            res = std::min(res, cost);
        }
    }
    // return
    return res;
}

int memoization(int i, string &s, vector<int> &dp)
{
    // base
    if (i == s.length())
        return 0;
    // already solve?
    if (dp[i] != -1)
        return dp[i];
    // explore
    string temp;
    int res = 1e9;
    for (int j = i; j < s.length(); j++)
    {
        temp += s[j];
        if (isPalindrome(temp))
        {
            int cost = 1 + memoization(j + 1, s, dp);
            res = std::min(res, cost);
        }
    }
    // return
    return dp[i] = res;
}
int tabulation(string &s)
{
    int n = s.length();
    vector<int> dp(n + 1, 1e9);
    // base
    dp[n] = 0;
    // explore
    for (int i = n - 1; i >= 0; i--)
    {
        string temp;
        for (int j = i; j < n; j++)
        {
            temp += s[j];
            if (isPalindrome(temp))
            {
                int cost = 1 + dp[j + 1];
                dp[i] = std::min(dp[i], cost);
            }
        }
    }
    return dp[0]-1;
}

int main()
{
    // input
    string s;
    cin >> s;

    // Without dp
    int res = solve(0, s) - 1;
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(exponential) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    int n = s.length();
    vector<int> dp(n, -1);
    int res2 = memoization(0, s, dp) - 1;
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(s);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;
}
