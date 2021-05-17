/*
 * @lc app=leetcode id=118 lang=cpp
 *
 * [118] Pascal's Triangle
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        if (numRows < 1) {
            return res;
        }

        res.push_back(vector<int>{1});
        if (numRows == 1) {
            return res;
        }

        vector<int> row;
        for (auto i = 0; i < numRows - 1; i++) {
            row.push_back(1);
            for (auto j = 0; j < res[i].size() - 1; j++) {
                row.push_back(res[i][j] + res[i][j + 1]);
            }
            row.push_back(1);
            res.push_back(row);
            row.clear();
        }
        return res;
    }
};
// @lc code=end
// print helper
void printVectorVector(vector<int>& vec) {
    for (auto it = vec.begin(); it != vec.end(); it++) {
        auto elem = *it;
        cout << "[";
        for (auto i = 0; i < elem.size() - 1; i++) {
            cout << elem[i] << ", ";
        }
        cout << elem[elem.size() - 1] << "]";
    }
}

int main() {
    Solution s;
    vector<vector<int>> v;
    for (auto i = 0; i < 10; i++) {
        v = s.generate(i);
        printVectorVector(v);
    }
}
