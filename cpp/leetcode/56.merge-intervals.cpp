/*
 * @lc app=leetcode id=56 lang=cpp
 *
 * [56] Merge Intervals
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        auto len = intervals.size();
        if (len < 2) {
            return intervals;
        }
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < len; i++) {
            int range = 0;

            int max_right = intervals[i][1];
            for (int j = i + 1; j < len; j++) {
                if (intervals[j][0] <= max_right) {
                    range++;
                    max_right = max(intervals[j][1], max_right);
                } else {
                    break;
                }
            }
            res.push_back(vector<int>{intervals[i][0], max_right});
            i = i + range;
        }
        return res;
    }
};
// @lc code=end

// print helper
void printVectorVector(vector<vector<int>>& vec) {
    cout << "[";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        auto elem = *it;
        cout << "[" << elem[0] << ", " << elem[1] << "],";
    }
    cout << "]" << endl;
}

int main() {
    Solution s;
    vector<vector<int>> vec;

    vec.push_back(vector<int>{1, 3});
    vec.push_back(vector<int>{2, 6});
    vec.push_back(vector<int>{8, 10});
    vec.push_back(vector<int>{15, 18});
    auto v = s.merge(vec);
    printVectorVector(v);

    vec.clear();
    vec.push_back(vector<int>{1, 4});
    vec.push_back(vector<int>{4, 5});
    v = s.merge(vec);
    printVectorVector(v);

    vec.clear();
    vec.push_back(vector<int>{1, 4});
    vec.push_back(vector<int>{0, 4});
    v = s.merge(vec);
    printVectorVector(v);

    vec.clear();
    vec.push_back(vector<int>{1, 4});
    vec.push_back(vector<int>{2, 3});
    v = s.merge(vec);
    printVectorVector(v);

    vec.clear();
    vec.push_back(vector<int>{2, 3});
    vec.push_back(vector<int>{4, 5});
    vec.push_back(vector<int>{6, 7});
    vec.push_back(vector<int>{8, 9});
    vec.push_back(vector<int>{1, 10});
    v = s.merge(vec);
    printVectorVector(v);

    vec.clear();
    vec.push_back(vector<int>{1, 4});
    vec.push_back(vector<int>{0, 2});
    vec.push_back(vector<int>{3, 5});
    v = s.merge(vec);
    printVectorVector(v);

    return 0;
}
