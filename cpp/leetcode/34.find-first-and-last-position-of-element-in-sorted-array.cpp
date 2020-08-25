/*
 * @lc app=leetcode id=34 lang=cpp
 *
 * [34] Find First and Last Position of Element in Sorted Array
 */
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    /*
    vector<int> searchRange(vector<int>& nums, int target) {
        auto lower = lower_bound(nums.begin(), nums.end(), target);
        if (lower != nums.end() and *lower == target){
            auto upper = upper_bound(nums.begin(), nums.end(), target);
            auto start = distance(nums.begin(), lower);
            auto dis = distance(lower, upper);
            return {static_cast<int>(start), static_cast<int>(start+dis-1)};
        }else{
            return {-1, -1};
        }
        return nums;
    }
    */
    vector<int> searchRange(vector<int>& nums, int target) {
        auto start = lower_bound(nums, target);
        auto end = lower_bound(nums, target+1)-1;
        if (start <= end)
            return {start, end};
        return {-1, -1};
    }
private:
    int lower_bound(vector<int>&nums, int target){
        int l = 0, r = nums.size() - 1;
        while(l <= r) {
            auto mid = l + (r - l) / 2;
            if (nums[mid] < target){
                l = mid + 1;
            }else {
                r = mid - 1;
            }
        }
        return l;
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<int> nums = {5,7,7,8,8,8,10};
    auto vec = s.searchRange(nums, 8);
    for(auto it = vec.begin(); it != vec.end(); it++) {
        std::cout<<*it<<",";
    }
    std::cout<<std::endl;
    return 0;
}
