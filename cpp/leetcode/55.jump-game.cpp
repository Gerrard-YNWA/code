/*
 * @lc app=leetcode id=55 lang=cpp
 *
 * [55] Jump Game
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    bool canJump(vector<int>& nums) {
        int len = nums.size(), farest = 0;
        for (auto i = 0; i < len; i++) {
            if (farest < i) return false;
            farest = max(i + nums[i], farest);
        }
        return true;
    }
};
// @lc code=end

int main() {
    Solution s;
    // vector<int> nums = {2, 3, 1, 1, 4};
    vector<int> nums = {3, 2, 1, 0, 4};
    cout << s.canJump(nums) << endl;
    return 0;
}
