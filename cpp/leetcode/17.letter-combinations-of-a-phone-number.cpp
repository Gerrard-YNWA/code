/*
 * @lc app=leetcode id=17 lang=cpp
 *
 * [17] Letter Combinations of a Phone Number
 */
#include<iostream>
#include<vector>
#include<unordered_map>
#include<utility>

using namespace std;
// @lc code=start
/*
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> vec;
        if (digits.size() > 0){
            auto tmp = letterCombinations(digits.substr(1, digits.size()-1));
            if (tmp.size() == 0) {
                tmp.push_back("");
            }
            auto p = letters.find(digits[0]);
            for(auto i = 0; i < p->second.second; i++) {
                for (auto j = 0; j < tmp.size(); j++) {
                    vec.push_back((p->second.first)[i] + tmp[j]);
                }
            }
        }
        return vec;
    }
private:
    unordered_map<char, pair<string, int>> letters = {
        {'2', make_pair("abc", 3)},
        {'3', make_pair("def", 3)},
        {'4', make_pair("ghi", 3)},
        {'5', make_pair("jkl", 3)},
        {'6', make_pair("mno", 3)},
        {'7', make_pair("pqrs", 4)},
        {'8', make_pair("tuv", 3)},
        {'9', make_pair("wxyz", 4)}
    };
};
*/
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        std::vector<string> vecStringResult;
        if(digits.size()==0) {
            return vecStringResult;
        }
        std::unordered_map<char,string> digitMaps;
        digitMaps.insert(std::pair<char, string>('0'," "));
        digitMaps.insert(std::pair<char, string>('2',"abc"));
        digitMaps.insert(std::pair<char, string>('3',"def"));
        digitMaps.insert(std::pair<char, string>('4',"ghi"));
        digitMaps.insert(std::pair<char, string>('5',"jkl"));
        digitMaps.insert(std::pair<char, string>('6',"mno"));
        digitMaps.insert(std::pair<char, string>('7',"pqrs"));
        digitMaps.insert(std::pair<char, string>('8',"tuv"));
        digitMaps.insert(std::pair<char, string>('9',"wxyz"));
        std::vector<string> vecStringsToCombine;
        //Append to all corresponding strings to vecStringsToCombine
        for(int i=0; i<digits.size();i++){
            string tempStr=digitMaps[digits[i]];
            vecStringsToCombine.push_back(tempStr);
            // cout<<vecStringsToCombine[i]<<" ";
        }
        string currentString;
        combineWithBacktrack(vecStringResult, vecStringsToCombine,currentString, 0);
        return vecStringResult;
    }
    void combineWithBacktrack(std::vector<string> &vecStringResult, std::vector<string> &vecStringsToCombine,string &currentString, int currentIndx){
        if(currentString.length()==vecStringsToCombine.size()){
            vecStringResult.push_back(currentString);
            return;
        }
        for(int i=currentIndx; i<vecStringsToCombine.size(); i++){
            for(int charIndx=0; charIndx<vecStringsToCombine[i].length(); charIndx++){
                
                currentString.append(1,vecStringsToCombine[currentIndx][charIndx]);
                combineWithBacktrack(vecStringResult,vecStringsToCombine, currentString, i+1);
                currentString.pop_back();
            }
        }
    }   
};
// @lc code=end

int main(){
    string digits = "234";
    auto s = new Solution();
    auto v = s->letterCombinations(digits);
    for (auto it = v.begin(); it != v.end(); it++)
        cout<<*it<<endl;
    return 0;
}
