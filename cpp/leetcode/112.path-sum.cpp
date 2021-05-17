/*
 * @lc app=leetcode id=112 lang=cpp
 *
 * [112] Path Sum
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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root)
            return false;
        stack<TreeNode*> s;
        s.push(root);
        TreeNode* node;
        while (!s.empty()) {
            node = s.top();
            s.pop();
            if (node->left) {
                node->left->val += node->val;
                s.push(node->left);
            }
            if (node->right) {
                node->right->val += node->val;
                s.push(node->right);
            }
            if (!node->left && !node->right) {  // leaf
                if (node->val == targetSum) {
                    return true;
                }
            }
        }
        return false;
    }
};
// @lc code=end

int main() {
    // 5,4,8,11,null,13,4,7,2,null,null,null,1
    TreeNode layer4_0 = TreeNode(7);
    TreeNode layer4_1 = TreeNode(2);
    TreeNode layer4_5 = TreeNode(1);
    TreeNode layer3_0 = TreeNode(11, &layer4_0, &layer4_1);
    TreeNode layer3_2 = TreeNode(13);
    TreeNode layer3_3 = TreeNode(4, nullptr, &layer4_5);
    TreeNode layer2_0 = TreeNode(4, &layer3_0, nullptr);
    TreeNode layer2_1 = TreeNode(8, &layer3_2, &layer3_3);
    TreeNode root = TreeNode(5, &layer2_0, &layer2_1);

    Solution s;
    cout << s.hasPathSum(&root, 18) << endl;

    root = TreeNode(1, new TreeNode(2), new TreeNode(3));
    cout << s.hasPathSum(&root, 5) << endl;

    // 1,-2,-3,1,3,-2,null,-1
    root = TreeNode(1, new TreeNode(-2, new TreeNode(1, new TreeNode(-1, nullptr, nullptr), nullptr), new TreeNode(3, nullptr, nullptr)), new TreeNode(-3, new TreeNode(-2), nullptr));
    cout << s.hasPathSum(&root, -1) << endl;

    return 0;
}
