// Question :

#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string solve(int index1, int index2, string &s1, string &s2)
{
    // base
    if (index1 == s1.length() or index2 == s2.length())
        return "";
    // expore
    if (s1[index1] == s2[index2])
        return s1[index1] + solve(index1 + 1, index2 + 1, s1, s2);

    string moveS1 = solve(index1 + 1, index2, s1, s2);
    string moveS2 = solve(index1, index2 + 1, s1, s2);
    return (moveS1.length() > moveS2.length()) ? moveS1 : moveS2;
}
string memoization(int index1, int index2, string &s1, string &s2, vector<vector<string>> &dp)
{
    // base
    if (index1 == s1.length() or index2 == s2.length())
        return "";
    // if already solved
    if (dp[index1][index2] != "")
        return dp[index1][index2];
    // expore
    if (s1[index1] == s2[index2])
        return dp[index1][index2] = s1[index1] + memoization(index1 + 1, index2 + 1, s1, s2, dp);

    string moveS1 = memoization(index1 + 1, index2, s1, s2, dp);
    string moveS2 = memoization(index1, index2 + 1, s1, s2, dp);
    return dp[index1][index2] += (moveS1.length() > moveS2.length()) ? moveS1 : moveS2;
}
string tabulation(string s1, string s2)
{
    if (s1.length() > s2.length())
        s1.swap(s2);
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
    // loop through the dp and get the string
    string res = "";
    int i = n, j = m;
    while (i > 0 and j > 0)
    {
        int dpIndex1 = i;
        int dpIndex2 = j;
        int index1 = i - 1;
        int index2 = j - 1;
        // expore
        if (s1[index1] == s2[index2])
        {
            res += s1[index1];
            i--;
            j--;
        }
        else
        {
            int moveS1 = dp[dpIndex1 - 1][dpIndex2];
            int moveS2 = dp[dpIndex1][dpIndex2 - 1];
            if (moveS1 > moveS2)
                i--;
            else
                j--;
        }
    }
    return res;
}

int main()
{
    // input
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.length(), m = s2.length();

    // without dp
    string res = solve(0, 0, s1, s2);
    cout << "Without DP: " << res << endl;
    cout << "Time complexity: O(2^(n+m)) \nSpace complexity: O(n+m) " << endl;
    cout << endl;

    // memoization
    vector<vector<string>> dp(n, vector<string>(m, ""));
    string res2 = memoization(0, 0, s1, s2, dp);
    cout << "Memoization: " << res << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(m*n) " << endl;
    cout << endl;

    // tabulation
    string res3 = tabulation(s1, s2);
    cout << "Tabulation : " << res3 << endl;
    cout << "Time complexity: O(n*m) \nSpa, dpce complexity: O(n*m) " << endl;
    cout << endl;

}
