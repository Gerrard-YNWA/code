/*
 * @lc app=leetcode id=78 lang=cpp
 *
 * [78] Subsets
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> track;
        backtrack(ans, track, nums, 0);
        return ans;
    }

   private:
    void backtrack(vector<vector<int>>& ans, vector<int>& track, vector<int>& nums, int start) {
        ans.push_back(track);
        for (auto i = start; i < nums.size(); i++) {
            track.push_back(nums[i]);
            backtrack(ans, track, nums, i + 1);
            track.pop_back();
        }
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<int> nums = {1, 2, 3};
    auto ans = s.subsets(nums);
    for (auto it = ans.begin(); it != ans.end(); it++) {
        for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}
