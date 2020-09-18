/*
 * @lc app=leetcode id=4 lang=cpp
 *
 * [4] Median of Two Sorted Arrays
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        /*
        vector<int>::iterator it;
        it = nums1.end();
        nums1.insert(it, nums2.begin(), nums2.end());

        for(it = nums1.begin(); it != nums1.end(); it++){
            cout<<*it<<endl;
        }
        */
        vector<int> merged_vec;
        while (nums1.size() > 0 && nums2.size() > 0) {
            if (*(nums1.begin()) < *(nums2.begin())) {
                merged_vec.insert(merged_vec.end(), *(nums1.begin()));
                nums1.erase(nums1.begin());
            } else {
                merged_vec.insert(merged_vec.end(), *(nums2.begin()));
                nums2.erase(nums2.begin());
            }
        }
        if (nums1.size() > 0) {
            merged_vec.insert(merged_vec.end(), nums1.begin(), nums1.end());
        } else if (nums2.size() > 0) {
            merged_vec.insert(merged_vec.end(), nums2.begin(), nums2.end());
        }
        // for(vector<int>::iterator it = merged_vec.begin(); it != merged_vec.end(); it++){
        // cout<<*it<<endl;
        //}
        if (merged_vec.size() % 2 == 0) {
            return (merged_vec[merged_vec.size() / 2] + merged_vec[merged_vec.size() / 2 - 1]) / 2.0;
        } else {
            return merged_vec[merged_vec.size() / 2] / 1.0;
        }
    }
};
// @lc code=end

int main(int argc, char** argv) {
    Solution s;
    int m[] = {2};
    int n[] = {};
    vector<int> nums1(m, m + sizeof(m) / sizeof(int));
    vector<int> nums2(n, n + sizeof(n) / sizeof(int));
    cout << s.findMedianSortedArrays(nums1, nums2) << endl;
    return 0;
}
