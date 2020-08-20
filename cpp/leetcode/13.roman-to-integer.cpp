/*
 * @lc app=leetcode id=13 lang=cpp
 *
 * [13] Roman to Integer
 */
#include<iostream>
#include<string>
using namespace std;
// @lc code=start
class Solution {
public:
    int romanToInt(string s) {
        auto len = s.length();
        if (len == 1) {
            return charToNumber(s[0]);
        }
        int sum = 0;
        int cur, next;
        for (auto i = 0; i < len - 1; i++){
            cur = charToNumber(s[i]);
            next = charToNumber(s[i+1]);
            if (cur < next) {
                sum = sum - cur;
            } else {
                sum = sum + cur;
            }
        }
        sum = sum + next;
        return sum;
    }
private:
    int charToNumber(char c) {
        switch(c) {
            case 'I': return 1;
                      break;
            case 'V': return 5;
                      break;
            case 'X': return 10;
                      break;
            case 'L': return 50;
                      break;
            case 'C': return 100;
                      break;
            case 'D': return 500;
                      break;
            case 'M': return 1000;
                      break;
            default: return 0;
        }
    }
};
// @lc code=end

int main() {
    Solution s;
    cout<<s.romanToInt("III")<<endl;
    cout<<s.romanToInt("IV")<<endl;
    cout<<s.romanToInt("IX")<<endl;
    cout<<s.romanToInt("LVIII")<<endl;
    cout<<s.romanToInt("MCMXCIV")<<endl;
    return 0;
}

