/*
 * @lc app=leetcode id=88 lang=cpp
 *
 * [88] Merge Sorted Array
 */
#include<iostream>
#include<vector>

using namespace std;
// @lc code=start
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        auto i = m-1, j = n-1;
        while(i>=0 && j>=0){
            if(nums1[i] >= nums2[j]){
                nums1[i+j+1] = nums1[i];
                i--;
            }else{
                nums1[i+j+1] = nums2[j];
                j--;
            }
        }
        while(j>=0){
            nums1[j] = nums2[j];
            j--;
        }
    }
};
// @lc code=end

int main() {
        Solution s;
        vector<int> nums1 = {1,2,3,0,0,0};
        vector<int> nums2 = {2,5,6};
        s.merge(nums1, 3, nums2, 3);
        for(auto x : nums1){
            cout<<x<<" ";
        }
        cout<<endl;
        return 0;
}
