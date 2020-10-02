/*
 * @lc app=leetcode id=93 lang=cpp
 *
 * [93] Restore IP Addresses
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<string> restoreIpAddresses(string s) {
        ans.clear();
        string ip = "";
        if (s.size() >= 4 and s.size() <= 12)
            backtrack(s, ip, 0, 1);
        return ans;
    }

   private:
    vector<string> ans;
    void backtrack(string &s, string &ip, int index, int part) {
        if (part == 4) {
            if (validate(s, index, s.size() - 1)) {
                ip += s.substr(index, s.size() - index);
                ans.push_back(ip);
            }
            ip = "";
            return;
        }

        for (auto i = index; i < s.size(); i++) {
            if (!validate(s, index, i)) {
                break;
            } else {
                auto tmp = ip;
                ip += s.substr(index, i - index + 1);
                ip += '.';
                backtrack(s, ip, i + 1, part + 1);
                ip = tmp;
            }
        }
    }

    bool validate(string &s, int start, int end) {
        auto len = end - start;
        if (s.size() < len or len > 2 or len < 0 or (len != 0 and s[start] == '0'))
            return false;
        if (stoi(s.substr(start, len + 1)) > 255)
            return false;
        return true;
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<string> input = {"25525511135", "0000", "1111", "010010", "101023"};
    for (auto i = 0; i < input.size(); i++) {
        auto ans = s.restoreIpAddresses(input[i]);
        cout << "Input: s = " << input[i] << endl << "Output: [";
        for (auto it = ans.begin(); it != ans.end(); it++) {
            cout << *it << ", ";
        }
        cout << "]" << endl;
    }
    return 0;
}
