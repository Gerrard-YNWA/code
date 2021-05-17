/*
 * @lc app=leetcode id=120 lang=cpp
 *
 * [120] Triangle
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    int minimumTotal(vector<vector<int>>& triangle) {
        /*
        auto n = triangle.size();
        // init NxN vector
        vector<vector<int>> res(n, vector<int>(n));
        res[0][0] = triangle[0][0];
        for (int i = 1; i < n; i++) {
            res[i][0] = triangle[i][0] + res[i - 1][0];
            auto max_idx = triangle[i].size() - 1;
            for (int j = 1; j < max_idx; j++) {
                res[i][j] = triangle[i][j] + min(res[i - 1][j], res[i - 1][j - 1]);
            }
            res[i][max_idx] = triangle[i][max_idx] + res[i - 1][max_idx - 1];
        }
        auto min_sum = res[n - 1][0];
        for (auto i = 1; i < n; i++) {
            min_sum = min(min_sum, res[n - 1][i]);
        }
        return min_sum;
        */

        auto n = triangle.size();
        vector<int> res(n);
        res[0] = triangle[0][0];
        for (auto i = 1; i < n; i++) {
            //从后往前
            res[i] = res[i - 1] + triangle[i][i];
            for (auto j = i - 1; j > 0; --j) {
                // res[j], res[j-1]为上一行的结果的
                res[j] = min(res[j - 1], res[j]) + triangle[i][j];
            }
            res[0] += triangle[i][0];
        }

        auto min_sum = res[0];
        for (auto i = 1; i < n; i++) {
            min_sum = min(min_sum, res[i]);
        }
        return min_sum;
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<vector<int>> vec;
    vec.push_back(vector<int>{2});
    vec.push_back(vector<int>{3, 4});
    vec.push_back(vector<int>{6, 5, 7});
    vec.push_back(vector<int>{4, 1, 8, 3});

    cout << s.minimumTotal(vec) << endl;

    vec.clear();
    vec.push_back(vector<int>{-10});
    cout << s.minimumTotal(vec) << endl;
}
