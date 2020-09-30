/*
 * @lc app=leetcode id=79 lang=cpp
 *
 * [79] Word Search
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    bool exist(vector<vector<char>>& board, string word) {
        max_x = board.size();
        max_y = board[0].size();
        word_len = word.size();
        for (auto i = 0; i < max_x; i++) {
            for (auto j = 0; j < max_y; j++) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }

   private:
    bool dfs(vector<vector<char>>& board, string& word, int x, int y, int idx) {
        if (x >= max_x || x < 0 || y >= max_y || y < 0 || board[x][y] != word[idx])
            return false;
        if (idx == word_len - 1)
            return true;
        auto c = board[x][y];  // save for recover
        board[x][y] = '0';
        auto ans = dfs(board, word, x + 1, y, idx + 1) || dfs(board, word, x - 1, y, idx + 1) || dfs(board, word, x, y + 1, idx + 1) || dfs(board, word, x, y - 1, idx + 1);
        board[x][y] = c;
        return ans;
    }
    int max_x, max_y, word_len;
};
// @lc code=end

int main() {
    Solution s;
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'},
    };
    vector<string> words = {"ABCCED", "SEE", "ABCB"};
    for (auto i = 0; i < words.size(); i++) {
        auto b = s.exist(board, words[i]);
        cout << "Given word = \"" << words[i] << "\", return " << boolalpha << b << "." << endl;
    }
    return 0;
}
