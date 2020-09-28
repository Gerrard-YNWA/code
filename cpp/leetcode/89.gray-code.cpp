/*
 * @lc app=leetcode id=89 lang=cpp
 *
 * [89] Gray Code
 */
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   private:
    void backtrack(bitset<32> &bits, vector<int> &ans, int k) {
        if (k == 0) {
            ans.push_back(bits.to_ulong());
        } else {
            backtrack(bits, ans, k - 1);
            bits.flip(k - 1);
            backtrack(bits, ans, k - 1);
        }
    }

   public:
    vector<int> grayCode(int n) {
        bitset<32> bits;
        vector<int> ans;
        backtrack(bits, ans, n);
        return ans;
    }
};
// @lc code=end

int main() {
    Solution s;
    auto vec = s.grayCode(2);
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}
