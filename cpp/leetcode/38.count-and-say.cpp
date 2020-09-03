/*
 * @lc app=leetcode id=38 lang=cpp
 *
 * [38] Count and Say
 */
#include <iostream>
#include <string>
#include <vector>

/*
 * 1 = 1
 * 2 = 11
 * 3 = 21
 * 4 = 1211
 * 5 = 111221
 * 6 = 312211
 */
using namespace std;
// @lc code=start
vector<string> dp(31, "");
class Solution {
   public:
    string countAndSay(int n) {
        if (n == 1) {
            return "1";
        } else if (n == 2) {
            return "11";
        }
        if (dp[n - 1] != "") {
            return dp[n - 1];
        }
        string res = countAndSay(n - 1);
        string newstr = "";
        int count = 1;
        for (auto i = 0; i < res.size(); i++) {
            if (res[i] == res[i + 1]) {
                count++;
            } else {
                newstr += (48 + count);
                newstr += (res[i]);
                count = 1;
            }
        }
        dp[n - 1] = newstr;
        return newstr;
    }
};
// @lc code=end

int main() {
    Solution s;
    cout << s.countAndSay(1) << endl;
    cout << s.countAndSay(2) << endl;
    cout << s.countAndSay(3) << endl;
    cout << s.countAndSay(4) << endl;
    cout << s.countAndSay(5) << endl;
    cout << s.countAndSay(6) << endl;
    cout << s.countAndSay(7) << endl;
    cout << s.countAndSay(8) << endl;
    cout << s.countAndSay(9) << endl;
    cout << s.countAndSay(10) << endl;
    cout << s.countAndSay(20) << endl;
    return 0;
}
