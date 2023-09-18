// Question :

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> lcs_tabulation(string s1, string s2)
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
    return dp;
}

string getSuperSequence(vector<vector<int>> &dp, string s1, string s2)
{
    string res = "";
    int i = dp.size() - 1;
    int j = dp[0].size() - 1;
    while (i > 0 && j > 0)
    {
        int dpIndex1 = i;
        int dpIndex2 = j;
        int index1 = i - 1;
        int index2 = j - 1;
        if (s1[index1] == s2[index2])
        {
            res.push_back(s1[index1]);
            i--;
            j--;
        }
        else
        {
            int moveS1 = dp[dpIndex1 - 1][dpIndex2];
            int moveS2 = dp[dpIndex1][dpIndex2 - 1];
            if (moveS1 > moveS2)
            {
                res.push_back(s1[index1]);
                i--;
            }
            else
            {
                res.push_back(s2[index2]);
                j--;
            }
        }
    }
    while (i > 0)
    {
        int index1 = i - 1;
        res.push_back(s1[index1]);
        i--;
    }
    while (j > 0)
    {
        int index2 = j - 1;
        res.push_back(s2[index2]);
        j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    // input
    string s1, s2;
    cin >> s1 >> s2;

    // tabulation
    vector<vector<int>> dp = lcs_tabulation(s1, s2);
    string res = getSuperSequence(dp, s1, s2);
    cout << "Tabulation : " << res << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m)";
    cout << endl;
}
