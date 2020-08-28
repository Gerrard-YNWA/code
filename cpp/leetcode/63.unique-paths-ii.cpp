/*
 * @lc app=leetcode id=63 lang=cpp
 *
 * [63] Unique Paths II
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start

class Solution {
   public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        auto m = obstacleGrid.size();
        if (m <= 0) {
            return 0;
        }

        auto n = obstacleGrid[0].size();
        if (n <= 0 or obstacleGrid[0][0] == 1 or obstacleGrid[m - 1][n - 1] == 1) {
            return 0;
        }

        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (auto i = 0; i < m; i++) {
            if (!obstacleGrid[i][0]) {
                dp[i][0] = 1;
            } else {
                break;
            }
        }
        for (auto i = 0; i < n; i++) {
            if (!obstacleGrid[0][i]) {
                dp[0][i] = 1;
            } else {
                break;
            }
        }

        for (auto i = 1; i < m; i++) {
            for (auto j = 1; j < n; j++) {
                if (!obstacleGrid[i][j]) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
// @lc code=end

int main() {
    Solution s;
    // vector<vector<int>> obstacleGrid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    // vector<vector<int>> obstacleGrid = {{0, 0}, {1, 0}};
    vector<vector<int>> obstacleGrid = {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
    // vector<vector<int>> obstacleGrid = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    cout << s.uniquePathsWithObstacles(obstacleGrid) << endl;
    return 0;
}
