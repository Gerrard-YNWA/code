/*
 * @lc app=leetcode id=47 lang=cpp
 *
 * [47] Permutations II
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> ans;
        vector<int> track;
        vector<bool> visited(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtrack(ans, track, nums, visited);
        return ans;
    }

   private:
    void backtrack(vector<vector<int>> &ans, vector<int> &track, vector<int> &nums, vector<bool> &visited) {
        if (track.size() == nums.size()) {
            ans.push_back(track);
            return;
        }
        for (auto i = 0; i < nums.size(); i++) {
            if (!visited[i]) {
                if (i > 0 && nums[i] == nums[i - 1] && visited[i - 1]) {
                    continue;
                }
                visited[i] = true;
                track.push_back(nums[i]);
                backtrack(ans, track, nums, visited);
                track.pop_back();
                visited[i] = false;
            }
        }
    }
};
// @lc code=end

int main() {
    vector<int> nums = {1, 1, 2, 3};
    Solution s;
    auto result = s.permuteUnique(nums);
    for (auto it = result.begin(); it != result.end(); it++) {
        auto vec = *it;
        for (auto it2 = vec.begin(); it2 != vec.end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}
