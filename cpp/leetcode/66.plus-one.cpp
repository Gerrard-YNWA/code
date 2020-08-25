/*
 * @lc app=leetcode id=66 lang=cpp
 *
 * [66] Plus One
 */
#include<iostream>
#include<vector>

using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        while(--n >= 0){
            if(digits[n] == 9) {
                digits[n] = 0;
            } else {
                digits[n] += 1;
                return digits;
            }
        }
        if(digits[0] == 0){
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<int> vec = {9, 9, 9};
    vec = {8, 9, 9};
    vec = s.plusOne(vec);

    for(auto x: vec) {
        cout<<" "<<x;
    }
    cout<<endl;
    return 0;
}
