/*
 * @lc app=leetcode id=77 lang=cpp
 *
 * [77] Combinations
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> track;
        backtrack(ans, track, n, k, 1);
        return ans;
    }

   private:
    void backtrack(vector<vector<int>>& ans, vector<int>& track, int n, int k, int start) {
        if (k == track.size()) {
            ans.push_back(track);
        } else {
            for (auto i = start; i <= n; i++) {
                track.push_back(i);
                backtrack(ans, track, n, k, i + 1);
                track.pop_back();
            }
        }
    }
};
// @lc code=end

int main() {
    Solution s;
    auto ans = s.combine(4, 2);
    for (auto it = ans.begin(); it != ans.end(); it++) {
        for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }

    return 0;
}
