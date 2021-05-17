/*
 * @lc app=leetcode id=434 lang=cpp
 *
 * [434] Number of Segments in a String
 */
#include <iostream>

using namespace std;
// @lc code=start
class Solution {
   public:
    int countSegments(string s) {
        int len = s.length();
        if (len == 0)
            return 0;
        int part = 1, i = 0, stop = 0, start = 0;
        //"!@#$%^&*()_+-=',.:"
        while (i < len) {
            if (s[i] != 32) {
                stop = 0;
                start = 1;
            } else {
                if (!stop && start) {
                    part++;
                }
                stop++;
            }
            i++;
        }
        if (stop > 0) {
            part--;
        }
        return part;
    }
};
// @lc code=end

int main() {
    Solution s;
    cout << s.countSegments("Hello, my name is John") << endl;      // 5
    cout << s.countSegments("Hello") << endl;                       // 1
    cout << s.countSegments("love live! mu'sic forever") << endl;   // 4
    cout << s.countSegments("") << endl;                            // 0
    cout << s.countSegments(" love live! mu'sic forever") << endl;  // 4
    cout << s.countSegments("love live! mu'sic forever ") << endl;  // 4
    cout << s.countSegments("           ") << endl;                 // 0
    return 0;
}
