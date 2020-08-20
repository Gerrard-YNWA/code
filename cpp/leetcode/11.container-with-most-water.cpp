/*
 * @lc app=leetcode id=11 lang=cpp
 *
 * [11] Container With Most Water
 */
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int area =0, left = 0, right = height.size() - 1;
        while(left < right){
            area = max(area, min(height[left], height[right]) * (right - left));
            if (height[left] > height[right]) {
                right--;
            } else {
                left++;
            }
        }
        return area;
    }
};
// @lc code=end

int main(){
    Solution s;
    vector<int> height;
    height = {1,8,6,2,5,4,8,3,7};
    cout<<s.maxArea(height)<<endl;
    return 0;
}
