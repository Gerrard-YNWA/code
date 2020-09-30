/*
 * @lc app=leetcode id=90 lang=cpp
 *
 * [90] Subsets II
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> track;
        sort(nums.begin(), nums.end());
        backtrack(ans, track, nums, 0);
        return ans;
    }

   private:
    void backtrack(vector<vector<int>>& ans, vector<int>& track, vector<int>& nums, int start) {
        ans.push_back(track);
        for (auto i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i - 1]) {
                continue;
            }
            track.push_back(nums[i]);
            backtrack(ans, track, nums, i + 1);
            track.pop_back();
        }
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<int> nums = {1, 2, 2};
    auto ans = s.subsetsWithDup(nums);
    for (auto it = ans.begin(); it != ans.end(); it++) {
        for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}
