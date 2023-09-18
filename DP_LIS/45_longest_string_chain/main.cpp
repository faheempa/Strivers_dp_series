// Question : https://leetcode.com/problems/longest-string-chain/

#include <bits/stdc++.h>
using namespace std;

bool check(string &a, string &b)
{
    if (a.size() != b.size() + 1)
        return false;
    int i = 0, j = 0;
    while (i < a.size())
    {
        if (a[i] == b[j])
            i++, j++;
        else
            i++;
    }
    return (i == a.size() and j == b.size());
}
static bool comp(string &a, string &b)
{
    return a.size() < b.size();
}
int LIS_modified(vector<string> &words)
{
    int n = words.size(), maxLen{0};
    std::sort(words.begin(), words.end(), comp);
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int prevIndex = 0; prevIndex < i; prevIndex++)
        {
            if (check(words[i], words[prevIndex]) and dp[i] < dp[prevIndex] + 1)
            {
                dp[i] = dp[prevIndex] + 1;
            }
        }
        maxLen = std::max(maxLen, dp[i]);
    }
    return maxLen;
}

int main()
{
    // input
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++)
        cin >> words[i];

    // output
    cout << LIS_modified(words) << endl;
    cout << "Time Complexity: O(n^2)" << endl;
    cout << "Space Complexity: O(n)" << endl;
}
