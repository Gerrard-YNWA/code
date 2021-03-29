/*
 * @lc app=leetcode id=67 lang=cpp
 *
 * [67] Add Binary
 */
#include <iostream>

using namespace std;
// @lc code=start
class Solution {
   public:
    string addBinary(string a, string b) {
        string s = "";
        int len_a = a.length(), len_b = b.length();
        int i = len_a - 1, j = len_b - 1;
        int flag = 0;
        while (true) {
            //cout << i << ", " << j << endl;
            if (i >= 0 && j >= 0) {
                if (a[i] == b[j]) {
                    s = flag ? "1" + s : "0" + s;
                    flag = a[i] == '1' ? 1 : 0;
                } else {
                    char cur = flag ? '0' : '1';
                    s = cur + s;
                    flag = cur == '0' ? 1 : 0;
                }
                i--;
                j--;
            } else if (i >= 0) {
                if (flag) {
                    if (a[i] == '1') {
                        s = "0" + s;
                        flag = 1;
                    } else {
                        s = "1" + s;
                        flag = 0;
                    }
                } else {
                    s = a[i] + s;
                }
                i--;
            } else if (j >= 0) {
                if (flag) {
                    if (b[j] == '1') {
                        s = "0" + s;
                        flag = 1;
                    } else {
                        s = "1" + s;
                        flag = 0;
                    }
                } else {
                    s = b[j] + s;
                }
                j--;
            } else {
                s = flag ? "1" + s : s;
                break;
            }
        }
        return s;
    }
};
// @lc code=end

int main() {
    Solution s;
    cout << s.addBinary("11", "1") << endl;
    cout << s.addBinary("1010", "1011") << endl;

    return 0;
}
