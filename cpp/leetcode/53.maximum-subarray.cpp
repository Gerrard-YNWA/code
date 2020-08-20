/*
 * @lc app=leetcode id=53 lang=cpp
 *
 * [53] Maximum Subarray
 */
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        auto tmp_max = nums[0];
        auto max_sum = tmp_max;
        for(auto i = 1; i < nums.size(); i++){
            tmp_max = max(nums[i], nums[i] + tmp_max);
            max_sum = max(max_sum, tmp_max);
        }
        return max_sum;
    }
};
// @lc code=end

int main(){
    vector<int>nums{-2,1,-3,4,-1,2,1,-5,4};
    Solution s;
    cout<<s.maxSubArray(nums)<<endl;
    return 0;
}
