// Question : minimum number of insertions+deletions to make two strings same.

#include <bits/stdc++.h>
using namespace std;

int lcs(string s1, string s2)
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

    // tabulation with space optimization
    int lenOfLCS = lcs(s1, s2);
    int deletions = s1.length() - lenOfLCS;
    int insertions = s2.length() - lenOfLCS;
    int res = insertions + deletions;
    cout << "Tabulation With SO : " << res << endl;
    cout << "Time complexity: (n*m) \nSpace complexity: O(min(n, m)) " << endl;
    cout << endl;
}
