/*
 * @lc app=leetcode id=62 lang=cpp
 *
 * [62] Unique Paths
 */
#include<iostream>
#include<vector>

using namespace std;
// @lc code=start

vector<int>row(101,0);
vector<vector<int>>dp(101, row);
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m <=0 or n <= 0)
            return 0;
        if(m==1 or n == 1)
            return 1;
        if(dp[m][n] == 0){
            dp[m][n] = uniquePaths(m-1, n) + uniquePaths(m, n-1);
        }
        return dp[m][n];
    }
};
// @lc code=end


int main () {
    Solution s;
    cout<<s.uniquePaths(7, 3)<<endl;
    return 0;
}

