/*
 * @lc app=leetcode id=64 lang=cpp
 *
 * [64] Minimum Path Sum
 */
#include <iostream>
#include <vector>

#include "printHelper.hpp"

using namespace std;
// @lc code=start
class Solution {
   public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> res(m, vector<int>(n, grid[0][0]));
        for (auto i = 1; i < m; i++) {
            res[i][0] = res[i - 1][0] + grid[i][0];
        }
        for (auto j = 1; j < n; j++) {
            res[0][j] = res[0][j - 1] + grid[0][j];
        }
        for (auto i = 1; i < m; i++) {
            for (auto j = 1; j < n; j++) {
                res[i][j] = min(res[i - 1][j], res[i][j - 1]) + grid[i][j];
            }
        }

        // printVectorVector(grid);
        // printVectorVector(res);
        return res[m - 1][n - 1];
    }
};
// @lc code=end

int main() {
    // 7
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};

    Solution s;
    cout << s.minPathSum(grid) << endl;
    // 12
    grid = {{1, 2, 3}, {4, 5, 6}};
    cout << s.minPathSum(grid) << endl;
    return 0;
}
