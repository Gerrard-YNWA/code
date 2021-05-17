/*
 * @lc app=leetcode id=437 lang=cpp
 *
 * [437] Path Sum III
 */
#include <iostream>
#include <stack>

#include "tree.hpp"

using namespace std;
// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    int counter = 0;
    void dfs(TreeNode* root, int target_sum, int cur_sum) {
        if (root) {
            cur_sum += root->val;
            if (cur_sum == target_sum)
                counter++;

            if (root->left)
                dfs(root->left, target_sum, cur_sum);

            if (root->right)
                dfs(root->right, target_sum, cur_sum);
        }
    }
    int pathSum(TreeNode* root, int targetSum) {
        if (!root)
            return 0;
        dfs(root, targetSum, 0);
        pathSum(root->left, targetSum);
        pathSum(root->right, targetSum);
        return counter;
    }
};
// @lc code=end

int main() {
    // 10,5,-3,3,2,null,11,3,-2,null,1
    // target 8
    // output 3
    vector<int> vec = {10, 5, -3, 3, 2, '#', 11, 3, -2, '#', 1};
    TreeNode* root = CreateTree(vec, 0);
    FloorPrint(root);
    Solution s;
    cout << s.pathSum(root, 8) << endl;

    // 5,4,8,11,null,13,4,7,2,null,null,5,1
    // target 22
    // output 3
    //
    vec = {5, 4, 8, 11, '#', 13, 4, 7, 2, '#', '#', 5, 1};
    root = CreateTree(vec, 0);
    FloorPrint(root);
    s.counter = 0;
    cout << s.pathSum(root, 22) << endl;

    // 1,null,2,null,3,null,4,null,5
    // target 3
    // output 2
    //
    vec = {1, '#', 2, '#', '#', '#', 3, '#', '#', '#', '#', '#', '#', '#', 4, '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 5};
    root = CreateTree(vec, 0);
    FloorPrint(root);
    s.counter = 0;
    cout << s.pathSum(root, 3) << endl;

    // 1,-2,-3,1,3,-2,null,-1
    // target 3
    // output 1
    //
    vec = {1, -2, -3, 1, 3, 2, '#', -1};
    root = CreateTree(vec, 0);
    FloorPrint(root);
    s.counter = 0;
    cout << s.pathSum(root, 3) << endl;
}
