/*
 * @lc app=leetcode id=119 lang=cpp
 *
 * [119] Pascal's Triangle II
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<int> getRow(int rowIndex) {
        vector<vector<int>> res;
        res.push_back(vector<int>{1});
        vector<int> row;
        for (auto i = 0; i < rowIndex; i++) {
            row.push_back(1);
            for (auto j = 0; j < res[i].size() - 1; j++) {
                row.push_back(res[i][j] + res[i][j + 1]);
            }
            row.push_back(1);
            res.push_back(row);
            row.clear();
        }
        return res[rowIndex];
    }
};
// @lc code=end
// print helper
void printVector(vector<int>& vec) {
    cout << "[";
    for (auto i = 0; i < vec.size() - 1; i++) {
        cout << vec[i] << ", ";
    }
    cout << vec[vec.size() - 1] << "]" << endl;
}

int main() {
    Solution s;
    vector<int> v;
    for (auto i = 0; i < 10; i++) {
        v = s.getRow(i);
        printVector(v);
    }
}
