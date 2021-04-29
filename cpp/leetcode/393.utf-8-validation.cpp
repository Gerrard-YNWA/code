/*
 * @lc app=leetcode id=393 lang=cpp
 *
 * [393] UTF-8 Validation
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;
// @lc code=start
class Solution {
   public:
    bool validUtf8(vector<int>& data) {
        int len = data.size();
        int i = 0, left_size = 0;
        while (i < len) {
            if (data[i] >= 0x80) {
                if (data[i] >= 0xC0 && data[i] <= 0xDF)
                    left_size = 1;
                else if (data[i] >= 0xE0 && data[i] <= 0xEF) {
                    left_size = 2;
                } else if (data[i] >= 0xF0 && data[i] <= 0xF7) {
                    left_size = 3;
                } else {
                    return false;
                }

                if (i + left_size >= len)
                    return false;

                for (int j = 1; j <= left_size; j++)
                    if (data[i + j] < 0x80)
                        return false;

                i = i + left_size;
            }
            i++;
        }
        return true;
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<int> data = {197, 130, 1};
    // data = {235, 140, 4};
    // data = {194, 155, 231, 184, 185, 246, 176, 131, 161, 222, 174, 227, 162, 134, 241, 154, 168, 185, 218, 178, 229, 187, 139, 246, 178, 187, 139, 204, 146, 225, 148, 179, 245, 139, 172, 134, 193, 156, 233, 131, 154, 240, 166, 188, 190, 216, 150, 230, 145, 144, 240, 167, 140, 163, 221, 190, 238, 168, 139, 241, 154, 159, 164, 199, 170, 224, 173, 140, 244, 182, 143, 134, 206, 181, 227, 172, 141, 241, 146, 159, 170, 202, 134, 230, 142, 163, 244, 172, 140, 191};
    // data = {8, 21, 212, 177, 245, 187, 178, 157, 18, 196, 155, 227, 164, 170, 5, 196, 144, 229, 187, 161, 235, 164, 188, 12, 198, 163, 245, 135, 188, 189, 113, 77, 202, 177, 213, 166, 237, 129, 180, 247, 174, 169, 167, 217, 142, 228, 154, 184, 245, 163, 146, 157, 107, 225, 182, 180, 243, 149, 146, 153, 210, 158, 30, 201, 167, 227, 160, 160};
    // data = {230, 136, 145};
    cout << s.validUtf8(data) << endl;
    return 0;
}
