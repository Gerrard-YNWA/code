/*
 * @lc app=leetcode id=59 lang=cpp
 *
 * [59] Spiral Matrix II
 */
#include <iostream>
#include <vector>

#include "printHelper.hpp"

using namespace std;

// @lc code=start
class Solution {
   public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n));
        auto i = 0, start = 0, end = n - 1;
        while (i < n * n) {
            for (auto j = start; j <= end; j++) {
                res[start][j] = ++i;
            }
            for (auto j = start + 1; j <= end; j++) {
                res[j][end] = ++i;
            }
            for (auto j = end - 1; j >= start; j--) {
                res[end][j] = ++i;
            }
            end--;
            for (auto j = end; j >= start + 1; j--) {
                res[j][start] = ++i;
            }
            start++;
        }
        return res;
    }
};
// @lc code=end

int main() {
    Solution s;
    auto res = s.generateMatrix(1);
    printVectorVector(res);
    res = s.generateMatrix(2);
    printVectorVector(res);
    res = s.generateMatrix(3);
    printVectorVector(res);
    res = s.generateMatrix(4);
    printVectorVector(res);
    res = s.generateMatrix(5);
    printVectorVector(res);
    res = s.generateMatrix(6);
    printVectorVector(res);
    return 0;
}
