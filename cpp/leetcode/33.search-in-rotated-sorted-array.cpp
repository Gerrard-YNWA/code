/*
 * @lc app=leetcode id=33 lang=cpp
 *
 * [33] Search in Rotated Sorted Array
 */
#include<iostream>
#include<vector>

using namespace std;
// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1, mid = 0;
        if(nums[0] == target)
            return 0;
        else if(nums[right] == target)
            return right;

        //find the pivot
        while(left + 1 < right) {
            mid = left + (right - left) / 2;
            if (nums[mid] > nums[left]) {
                left = mid;
            }else{
                right = mid;
            }
        }
        
        if (nums[0] > target) {
            right = nums.size() - 1;
        }else{
            left = 0;
        }

        while(left + 1 < right) {
            mid = left + (right - left) / 2;
            if(nums[mid] > target) {
                right = mid;
            }else if(nums[mid] < target){
                left = mid;
            }else{
                return mid;
            }
        }
        return -1;
    }
};
// @lc code=end

int main() {
    vector<int> nums = {4,5,6,7,0,1,2};
    Solution s;
    auto idx = s.search(nums, 0);
    cout<<idx<<endl;
    return 0;
}
