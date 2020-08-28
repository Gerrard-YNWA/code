/*
 * @lc app=leetcode id=69 lang=cpp
 *
 * [69] Sqrt(x)
 */
#include <iostream>

using namespace std;
// @lc code=start
class Solution {
   public:
    int mySqrt(int x) {
        if (x <= 1) return x;
        int left = 1, right = x / 2, mid, tmp;
        while (left <= right) {
            mid = left + (right - left) / 2;
            tmp = x / mid;  //乘法会溢出, 改用除法
            if (mid == tmp)
                return mid;
            else if (mid > tmp)
                right = mid - 1;
            else
                left = mid + 1;
        }
        cout << "left: " << left << ", right: " << right << endl;
        return right;
    }
};
// @lc code=end
int main() {
    Solution s;
    cout << s.mySqrt(36) << endl;
    return 0;
}
