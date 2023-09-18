// Question : print longest common substring

#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string tabulation(string s1, string s2)
{
    int n = s1.length(), m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // base
    // here 0 is considered as -1, we need to set all values in oth row and 0th col to 0, its already done by defualt
    // compute all
    int len{0}, start{0};
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
                if (dp[dpIndex1][dpIndex2] > len)
                {
                    len = dp[dpIndex1][dpIndex2];
                    start = dpIndex1 - len;
                }
            }
            else
            {
                dp[dpIndex1][dpIndex2] = 0;
            }
        }
    }
    return s1.substr(start, len);
}
string tabulation_with_SO(string s1, string s2)
{
    if (s1.length() < s2.length())
        s1.swap(s2);
    int n = s1.length(), m = s2.length();
    vector<int> dp(m + 1, 0);
    int len{0}, start{0};
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
                if (temp[dpIndex2] > len)
                {
                    len = temp[dpIndex2];
                    start = dpIndex1 - len;
                }
            }
            else
            {
                temp[dpIndex2] = 0;
            }
        }
        dp = temp;
    }
    return s1.substr(start, len);
}

int main()
{
    // input
    string s1, s2;
    cin >> s1 >> s2;

    // tabulation
    string res = tabulation(s1, s2);
    cout << "Tabulation : " << res << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(n*m) " << endl;
    cout << endl;

    // tabulation with space optimization
    string res2 = tabulation_with_SO(s1, s2);
    cout << "Tabulation With SO : " << res2 << endl;
    cout << "Time complexity: O(n*m) \nSpace complexity: O(max(n,m)) " << endl;
    cout << endl;
}
