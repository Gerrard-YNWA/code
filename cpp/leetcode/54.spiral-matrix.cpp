/*
 * @lc app=leetcode id=54 lang=cpp
 *
 * [54] Spiral Matrix
 */
#include <iostream>
#include <vector>

#include "printHelper.hpp"
using namespace std;

// @lc code=start
class Solution {
   public:
    // matrix (m x n) in spiral order
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        auto m = matrix.size();
        if (m == 0)
            return res;
        if (m == 1)
            return matrix[0];
        auto n = matrix[0].size();
        int start_x = 0, start_y = 0, end_x = m - 1, end_y = n - 1;
        while (start_x <= end_x && start_y <= end_y) {
            for (auto i = start_y; i <= end_y; i++) {
                res.push_back(matrix[start_x][i]);
            }
            start_x++;

            for (auto i = start_x; i <= end_x; i++) {
                res.push_back(matrix[i][end_y]);
            }
            end_y--;

            if (start_x <= end_x) {
                for (auto i = end_y; i >= start_y; i--) {
                    res.push_back(matrix[end_x][i]);
                }
                end_x--;
            }

            if (start_y <= end_y) {
                for (auto i = end_x; i >= start_x; i--) {
                    res.push_back(matrix[i][start_y]);
                }
                start_y++;
            }
        }
        return res;
    }
};
// @lc code=end

int main() {
    // Input:
    // [
    //  [ 1, 2, 3 ],
    //  [ 4, 5, 6 ],
    //  [ 7, 8, 9 ]
    // ]
    // Output: [1,2,3,6,9,8,7,4,5]
    vector<vector<int>> vec;
    vec.push_back(vector<int>{1, 2, 3});
    vec.push_back(vector<int>{4, 5, 6});
    vec.push_back(vector<int>{7, 8, 9});
    printVectorVector(vec);
    Solution s;
    printVector(s.spiralOrder(vec));
    // [
    //  [1, 2, 3, 4],
    //  [5, 6, 7, 8],
    //  [9,10,11,12]
    // ]
    // Output: [1,2,3,4,8,12,11,10,9,5,6,7]
    vec.clear();
    vec.push_back(vector<int>{1, 2, 3, 4});
    vec.push_back(vector<int>{5, 6, 7, 8});
    vec.push_back(vector<int>{9, 10, 11, 12});
    printVectorVector(vec);
    printVector(s.spiralOrder(vec));
    return 0;
}
