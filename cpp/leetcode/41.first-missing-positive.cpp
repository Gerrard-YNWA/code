/*
 * @lc app=leetcode id=41 lang=cpp
 *
 * [41] First Missing Positive
 */
#include<iostream>
#include<vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        auto n = nums.size();
        auto i = 0;
        while (i < n) {
            if (nums[i] > 0 and nums[i] <= n and nums[i] != i + 1 and nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            } else {
                i++;
            } 
        }

        for(auto i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i+1;
            }
        }
        return n+1;
    }
};
// @lc code=end

int main() {
    Solution s;
    //vector<int> nums = {1,2,0};
    //vector<int> nums = {3,4,-1,1};
    vector<int> nums = {7,8,9,11,12};
    //vector<int> nums = {11,3,4,5,12,0,-1,-2,-3};
    std::cout<<s.firstMissingPositive(nums)<<std::endl;
    return 0;
}
