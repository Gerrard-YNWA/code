/*
 * @lc app=leetcode id=509 lang=cpp
 *
 * [509] Fibonacci Number
 */
#include<iostream>
#include<vector>

using namespace std;
// @lc code=start
vector<int> t(31, 0);

class Solution {
public:
    int fib(int N) {
        if(N == 0) return 0;
        if(N == 1) return 1;
        if(t[N] == 0)
            t[N] = fib(N-1) + fib(N-2);
        return t[N];
    }
};
// @lc code=end

int main() {
    Solution s;
    cout<<s.fib(30)<<endl;
    return 0;
}
