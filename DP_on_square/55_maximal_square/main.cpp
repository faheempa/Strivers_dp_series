// Question : https://leetcode.com/problems/maximal-rectangle/description/

#include <bits/stdc++.h>
using namespace std;

int largestRectangleArea(vector<int> &heights)
{
    int res{INT_MIN};
    stack<pair<int, int>> stk;
    for (int i = 0; i < heights.size(); i++)
    {
        int start{i};
        while (stk.empty() == false and stk.top().second > heights[i])
        {
            int index = stk.top().first;
            int height = stk.top().second;
            int width = i - index;
            stk.pop();

            res = max(res, height * width);
            start = index;
        }
        stk.push({start, heights[i]});
    }
    while (stk.empty() == false)
    {
        int height = stk.top().second;
        int width = heights.size() - stk.top().first;
        stk.pop();

        res = max(res, height * width);
    }
    return res;
}
int tabulation(vector<vector<char>> &matrix)
{
    int maxVal{0};
    int rows = matrix.size(), cols = matrix[0].size();
    vector<int> heights(cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == '1')
                heights[j]++;
            else
                heights[j] = 0;
        }
        maxVal = max(maxVal, largestRectangleArea(heights));
    }
    return maxVal;
}

int main()
{
    // input
    int n, m;
    cin >> n >> m;
    vector<vector<char>> matrix(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
        }
    }

    // tabulation
    int res = tabulation(matrix);
    cout << "Tabulation : " <<res<< endl;
    cout << "Time complexity: O(n^3) \nSpace complexity: O(n^2) " << endl;
    cout << endl;
}
