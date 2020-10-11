/*
 * @lc app=leetcode id=121 lang=cpp
 *
 * [121] Best Time to Buy and Sell Stock
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0, min_price = INT_MAX;
        for (auto i = 0; i < prices.size(); i++) {
            min_price = min(min_price, prices[i]);
            max_profit = max(max_profit, prices[i] - min_price);
        }
        return max_profit;
    }
};
// @lc code=end

int main() {
    Solution s;
    // vector<int> prices = {7, 1, 5, 3, 6, 4};
    vector<int> prices = {7, 6, 4, 3, 1};
    cout << s.maxProfit(prices) << endl;
    return 0;
}
