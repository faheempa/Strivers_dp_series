// Question : find longest common subsequence in the qiven strings

#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int solve(int index1, int index2, string &s1, string &s2)
{
    // base
    if (index1 < 0 or index2 < 0)
        return 0;
    // expore
    if (s1[index1] == s2[index2])
        return 1 + solve(index1 - 1, index2 - 1, s1, s2);

    int moveS1 = solve(index1 - 1, index2, s1, s2);
    int moveS2 = solve(index1, index2 - 1, s1, s2);
    return std::max(moveS1, moveS2);
}

int memoization(int index1, int index2, string &s1, string &s2, vector<vector<int>> &dp)
{
    // base
    if (index1 < 0 or index2 < 0)
        return 0;
    // if already solved
    if (dp[index1][index2] != -1)
        return dp[index1][index2];
    // expore
    if (s1[index1] == s2[index2])
        return dp[index1][index2] = 1 + memoization(index1 - 1, index2 - 1, s1, s2, dp);

    int moveS1 = memoization(index1 - 1, index2, s1, s2, dp);
    int moveS2 = memoization(index1, index2 - 1, s1, s2, dp);
    return dp[index1][index2] = std::max(moveS1, moveS2);
}
int tabulation(string s1, string s2)
{
    int n = s1.length(), m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // base
    // here 0 is considered as -1, we need to set all values in oth row and 0th col to 0, its already done by defualt
    // compute all
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int dpIndex1 = i;
            int dpIndex2 = j;
            int index1 = i - 1;
            int index2 = j - 1;
            // expore
            if (s1[index1] == s2[index2])
            {
                dp[dpIndex1][dpIndex2] = 1 + dp[dpIndex1 - 1][dpIndex2 - 1];
            }
            else
            {
                int moveS1 = dp[dpIndex1 - 1][dpIndex2];
                int moveS2 = dp[dpIndex1][dpIndex2 - 1];
                dp[dpIndex1][dpIndex2] = std::max(moveS1, moveS2);
            }
        }
    }
    return dp[n][m];
}
int tabulation_with_SO(string s1, string s2)
{
    if (s1.length() < s2.length())
        s1.swap(s2);
    int n = s1.length(), m = s2.length();
    vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        vector<int> temp(m + 1, 0);
        for (int j = 1; j <= m; j++)
        {
            int dpIndex1 = i;
            int dpIndex2 = j;
            int index1 = i - 1;
            int index2 = j - 1;
            // expore
            if (s1[index1] == s2[index2])
            {
                temp[dpIndex2] = 1 + dp[dpIndex2 - 1];
            }
            else
            {
                int moveS1 = dp[dpIndex2];
                int moveS2 = temp[dpIndex2 - 1];
                temp[dpIndex2] = std::max(moveS1, moveS2);
            }
        }
        dp = temp;
    }
    return dp[m];
}

int main()
{
    // input
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.length(), m = s2.length();
    // Without dp
    int res = solve(n - 1, m - 1, s1, s2);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(m+n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(n, vector<int>(m, -1));
    int res2 = memoization(n - 1, m - 1, s1, s2, dp);
    cout << "Memoization: " << res2 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(m*n) " << endl;
    cout << endl;

    // tabulation
    int res3 = tabulation(s1, s2);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n*m) \nSpa, dpce complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation with space optimization
    int res4 = tabulation_with_SO(s1, s2);
    cout << "Tabulation With SO : " << res4 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(min(n, m)) " << endl;
    cout << endl;
}
