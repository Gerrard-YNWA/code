/*
 * @lc app=leetcode id=45 lang=cpp
 *
 * [45] Jump Game II
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    int jump(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) return 0;
        int farest = nums[0], steps = 0, pos = 0;
        int last_pos = len - 1;
        for (auto i = 0; i < len; i++) {
            farest = max(i + nums[i], farest);
            if (i == pos) {
                pos = farest;
                steps++;
            }
            if (farest >= last_pos) {
                if (pos < last_pos) steps++;
                break;
            }
        }
        return steps;
    }
};
// @lc code=end
//
int main() {
    Solution s;
    vector<int> nums = {1, 2, 1};
    // vector<int> nums = {3, 0, 0, 2, 1};
    // vector<int> nums = {1, 2, 0, 3, 100, 1, 1, 4};
    // vector<int> nums = {2, 3, 1, 1, 4};
    cout << s.jump(nums) << endl;
    return 0;
}
