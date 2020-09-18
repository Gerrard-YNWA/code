/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 */
#include <iostream>
#include <string>

using namespace std;
// @lc code=start
class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() <= 1) {
            return s.length();
        }
        string tmp;
        int maxLen = 0;
        int start = 0;
        // unsigned int i;
        for (unsigned int i = 0; i < s.length(); i++) {
            for (unsigned int j = 0; j < tmp.length(); j++) {
                if (s.at(i) == tmp.at(j)) {
                    if (maxLen < tmp.length()) maxLen = tmp.length();
                    tmp.clear();
                    i = start + 1;
                    break;
                }
            }
            tmp.push_back(s.at(i));
            if (tmp.length() == 1) {
                start = i;
            }
        }
        if (maxLen < tmp.length()) maxLen = tmp.length();
        return maxLen;
    }
};
// @lc code=end

int main(int argc, char** argv) {
    Solution s;
    cout << s.lengthOfLongestSubstring("abcabc") << endl;
    cout << s.lengthOfLongestSubstring("bbbbbb") << endl;
    cout << s.lengthOfLongestSubstring("pwwkew") << endl;
    cout << s.lengthOfLongestSubstring("au") << endl;
    cout << s.lengthOfLongestSubstring("dvdf") << endl;
    return 0;
}
