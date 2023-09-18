// Question : https://leetcode.com/problems/longest-palindromic-subsequence/

#include <bits/stdc++.h>
using namespace std;

int longest_common_palindrome_length(string s1)
{
    string s2{s1};
    reverse(s2.begin(), s2.end());

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
    string s;
    cin >> s;
    
    // tabulation with SO
    int len = s.length();
    int res = len - longest_common_palindrome_length(s);
    cout << "Tabulation : " << res << endl;
    cout << "Time complexity: O(n^2) \nSpace complexity: O(n) " << endl;
    cout << endl;
}
