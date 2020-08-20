/*
 * @lc app=leetcode id=16 lang=cpp
 *
 * [16] 3Sum Closest
 */
#include<iostream>
#include<vector>
#include<algorithm>
//#include<limits>
//#include<cmath>

using namespace std;

//需要考虑负数的情况
// @lc code=start
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int j, k, tmp, ret;
        int size = nums.size();
        int diff = INT_MAX;
        sort(nums.begin(), nums.end());
        for (auto i = 0; i < size - 2; i++) {
            j = i + 1;
            k = size - 1;
            while (j < k) {
                tmp = nums[i] + nums[j] + nums[k];
                if (abs(tmp - target) < diff) {
                    ret = tmp;
                    diff = abs(tmp - target);
                }
                if (tmp == target) {
                    return tmp;
                }
                else if (tmp > target) {
                    k--;
                }
                else {
                    j++;
                }
            } 
        }
        return ret;
    }
};
// @lc code=end

int main() {
    //vector<int> nums {-1,2,1,-4,7,5,-3,1};
    //int target = 1;
    //vector<int> nums {1,1,1,0};
    //int target = -100;
    //vector<int> nums {0,2,1,-3};
    //int target = 1;
    vector<int> nums {1,1,1,1};
    int target = -100;
    Solution s;
    cout<<s.threeSumClosest(nums, target)<<endl;
}
