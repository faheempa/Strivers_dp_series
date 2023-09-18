// Question : Given a string, print the longest palindromic subsequence.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

string print_lcs(string s1, string s2)
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
    string s;
    cin >> s;
    // get reverse of s
    string s2 = s;
    std::reverse(s2.begin(), s2.end());
    // tabulation with space optimization
    string res = print_lcs(s, s2);
    cout << "Tabulation : " << res << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n^2) " << endl;
    cout << endl;
}
