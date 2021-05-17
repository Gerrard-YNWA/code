/*
 * @lc app=leetcode id=57 lang=cpp
 *
 * [57] Insert Interval
 */
#include <iostream>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        auto len = intervals.size();
        auto start = 0;
        //前k个
        for (int i = 0; i < len; i++) {
            if (intervals[i][1] < newInterval[0]) {
                start++;
                res.push_back(intervals[i]);
            } else {
                break;
            }
        }

        // 合并
        for (int i = start; i < len; i++) {
            if (intervals[i][0] <= newInterval[1]) {
                newInterval[0] = min(newInterval[0], intervals[i][0]);
                newInterval[1] = max(newInterval[1], intervals[i][1]);
                start++;
            } else {
                break;
            }
        }
        res.push_back(newInterval);
        //后m个
        for (int i = start; i < len; i++) {
            res.push_back(intervals[i]);
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
    vector<vector<int>> intervals;
    vector<int> newInterval;

    intervals.push_back(vector<int>{1, 3});
    intervals.push_back(vector<int>{6, 9});
    newInterval.push_back(2);
    newInterval.push_back(5);
    auto v = s.insert(intervals, newInterval);
    printVectorVector(v);

    intervals.clear();
    newInterval.clear();
    intervals.push_back(vector<int>{1, 2});
    intervals.push_back(vector<int>{3, 5});
    intervals.push_back(vector<int>{6, 7});
    intervals.push_back(vector<int>{8, 10});
    intervals.push_back(vector<int>{12, 16});
    newInterval.push_back(4);
    newInterval.push_back(8);
    v = s.insert(intervals, newInterval);
    printVectorVector(v);

    intervals.clear();
    newInterval.clear();
    newInterval.push_back(5);
    newInterval.push_back(7);
    v = s.insert(intervals, newInterval);
    printVectorVector(v);

    intervals.clear();
    newInterval.clear();
    intervals.push_back(vector<int>{1, 5});
    newInterval.push_back(2);
    newInterval.push_back(3);
    v = s.insert(intervals, newInterval);
    printVectorVector(v);

    intervals.clear();
    newInterval.clear();
    intervals.push_back(vector<int>{1, 5});
    newInterval.push_back(6);
    newInterval.push_back(8);
    v = s.insert(intervals, newInterval);
    printVectorVector(v);

    intervals.clear();
    newInterval.clear();
    intervals.push_back(vector<int>{1, 5});
    newInterval.push_back(0);
    newInterval.push_back(3);
    v = s.insert(intervals, newInterval);
    printVectorVector(v);

    intervals.clear();
    newInterval.clear();
    intervals.push_back(vector<int>{1, 5});
    newInterval.push_back(0);
    newInterval.push_back(0);
    v = s.insert(intervals, newInterval);
    printVectorVector(v);

    return 0;
}
