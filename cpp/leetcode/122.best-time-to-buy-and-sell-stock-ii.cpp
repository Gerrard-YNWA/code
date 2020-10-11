/*
 * @lc app=leetcode id=122 lang=cpp
 *
 * [122] Best Time to Buy and Sell Stock II
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        for (auto i = 1; i < prices.size(); i++) {
            max_profit += max(prices[i] - prices[i - 1], 0);
        }
        return max_profit;
    }
};
// @lc code=end

int main() {
    Solution s;
    // vector<int> prices = {7, 1, 5, 3, 6, 4};
    // vector<int> prices = {1, 2, 3, 4, 5};
    vector<int> prices = {7, 6, 4, 3, 1};
    cout << s.maxProfit(prices) << endl;
    return 0;
}
