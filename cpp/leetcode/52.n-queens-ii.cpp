/*
 * @lc app=leetcode id=52 lang=cpp
 *
 * [52] N-Queens II
 */
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    int totalNQueens(int n) {
        initBoard(n);
        backtrack(n, 0);
        return ans.size();
    }

   private:
    void backtrack(int n, int x) {
        if (x == n) {
            genBoard();
            return;
        }
        for (int y = 0; y < n; y++) {
            if (validate(x, y)) {
                queen.push_back(y);
                s1.insert(y);
                s2.insert(x - y);
                s3.insert(x + y);
                backtrack(n, x + 1);
                queen.pop_back();
                s1.erase(y);
                s2.erase(x - y);
                s3.erase(x + y);
            }
        }
    }

    bool validate(int x, int y) {
        if (s1.find(y) == s1.end() and s2.find(x - y) == s2.end() and s3.find(x + y) == s3.end()) {
            return true;
        }
        return false;
    }

    void initBoard(int n) {
        string line(n, '.');
        for (auto i = 0; i < n; i++) {
            board.push_back(line);
        }
    }

    void genBoard() {
        for (auto i = 0; i < queen.size(); i++) {
            board[i][queen[i]] = 'Q';
        }
        ans.push_back(board);
        for (auto i = 0; i < queen.size(); i++) {
            board[i][queen[i]] = '.';
        }
    }
    vector<int> queen;
    vector<string> board;
    vector<vector<string>> ans;
    set<int> s1, s2, s3;
};
// @lc code=end

int main() {
    Solution s;
    vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for (auto i = 0; i < input.size(); i++) {
        cout << s.totalNQueens(input[i]) << endl;
    }
    return 0;
}
