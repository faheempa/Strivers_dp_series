// Question :

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int without_dp(int i, int j, vector<vector<int>> &triangle)
{
    if (i == triangle.size() - 1)
        return triangle[i][j];

    int down = without_dp(i + 1, j, triangle);
    int diagonal = without_dp(i + 1, j + 1, triangle);

    return triangle[i][j] + std::min(down, diagonal);
}

int memoization(int i, int j, vector<vector<int>> &triangle, vector<vector<int>> &dp)
{
    if (i == triangle.size() - 1)
        return triangle[i][j];

    if (dp[i][j] != -1)
        return dp[i][j];

    int down = memoization(i + 1, j, triangle, dp);
    int diagonal = memoization(i + 1, j + 1, triangle, dp);

    return dp[i][j] = triangle[i][j] + std::min(down, diagonal);
}
int tabulation(vector<vector<int>> &triangle)
{
    int h = triangle.size();
    if (h == 1)
        return triangle[0][0];

    vector<vector<int>> dp(h, vector<int>(h, -1));
    for (size_t j = 0; j < h; j++)
    {
        dp[h - 1][j] = triangle[h - 1][j];
    }
    for (int i = h - 2; i >= 0; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            int down = dp[i + 1][j];
            int diagonal = dp[i + 1][j + 1];
            dp[i][j] = triangle[i][j] + std::min(down, diagonal);
        }
    }
    return dp[0][0];
}
int tabulation_with_SO(vector<vector<int>> &triangle)
{
    int h = triangle.size();
    if (h == 1)
        return triangle[0][0];

    vector<int> pre(h, -1);
    for (size_t j = 0; j < h; j++)
    {
        pre[j] = triangle[h - 1][j];
    }
    for (int i = h - 2; i >= 0; i--)
    {
        vector<int> cur(i + 1, 0);
        for (int j = i; j >= 0; j--)
        {
            int down = pre[j];
            int diagonal = pre[j + 1];
            cur[j] = triangle[i][j] + std::min(down, diagonal);
        }
        pre = cur;
    }
    return pre[0];
}

int main()
{
    // input
    int h;
    cin >> h;
    vector<vector<int>> triangle(h, vector<int>(h, 0));
    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            int a;
            cin >> a;
            triangle[i][j] = a;
        }
    }

    // Without dp
    int ans = without_dp(0, 0, triangle);
    cout << "Without DP: " << ans << endl;
    cout << "Time complexity: O(2^n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // memoization
    vector<vector<int>> dp(h, vector<int>(h, -1));
    int ans2 = memoization(0, 0, triangle, dp);
    cout << "Memoization: " << ans2 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation
    int ans3 = tabulation(triangle);
    cout << "Tabulation : " << ans3 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
    cout << endl;

    // tabulation with space optimization
    int ans4 = tabulation_with_SO(triangle);
    cout << "Tabulation With SO : " << ans4 << endl;
    cout << "Time complexity: O(n) \nSpace complexity: O(n) " << endl;
}
