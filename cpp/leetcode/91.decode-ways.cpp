/*
 * @lc app=leetcode id=91 lang=cpp
 *
 * [91] Decode Ways
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    int numDecodings(string s) {
        vector<int> dp(s.size() + 1);
        dp[0] = 1;
        if (s[0] == '0')
            dp[1] = 0;
        else
            dp[1] = 1;

        for (auto i = 2; i <= s.size(); i++) {
            int t1, t2;
            if (s[i - 1] == '0') {
                t1 = 0;
            } else {
                t1 = dp[i - 1];
            }
            auto tmp = stoi(s.substr(i - 2, 2));
            if (tmp <= 26 and tmp > 0 and s[i - 2] != '0') {
                t2 = dp[i - 2];
            } else {
                t2 = 0;
            }
            dp[i] = t1 + t2;
        }
        return dp[s.size()];
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<string> input = {"12", "226", "0", "1", "2"};
    for (auto i = 0; i < input.size(); i++) {
        cout << s.numDecodings(input[i]) << endl;
    }
    return 0;
}
