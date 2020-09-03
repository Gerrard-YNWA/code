/*
 * @lc app=leetcode id=58 lang=cpp
 *
 * [58] Length of Last Word
 */
#include <iostream>

using namespace std;
// @lc code=start
class Solution {
   public:
    int lengthOfLastWord(string s) {
        int start = s.length() - 1;
        if (start == -1) {
            return 0;
        }
        int i = 0;
        for (i = start; i >= 0; i--) {
            if (s[i] != 32) break;
        }
        start = i;
        for (; i >= 0; i--) {
            if (s[i] == 32) {
                return start - i;
            }
        }
        return start + 1;
    }
};
// @lc code=end

int main() {
    Solution s;
    cout << s.lengthOfLastWord("Hello World") << endl;
    cout << s.lengthOfLastWord("HelloWorld") << endl;
    cout << s.lengthOfLastWord("  a") << endl;
    cout << s.lengthOfLastWord("a  ") << endl;
    cout << s.lengthOfLastWord("  ba ") << endl;
    return 0;
}
