/*
 * @lc app=leetcode id=104 lang=cpp
 *
 * [104] Maximum Depth of Binary Tree
 */
#include <iostream>
#include <queue>

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
    /*
    int maxDepth(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
    */

    int maxDepth(TreeNode* root) {
        if (!root)
            return 0;
        queue<TreeNode*> q;
        auto depth = 0;
        q.push(root);
        while (!q.empty()) {
            depth++;
            int nodes = q.size();
            //按层遍历
            for (auto i = 0; i < nodes; i++) {
                auto node = q.front();
                q.pop();
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
        }
        return depth;
    }
};
// @lc code=end

int main() {
    //[3, 9, 20, null, null, 15, 7]
    TreeNode layer3_3 = TreeNode(15);
    TreeNode layer3_4 = TreeNode(7);
    TreeNode layer2_1 = TreeNode(9);
    TreeNode layer2_2 = TreeNode(20, &layer3_3, &layer3_4);
    TreeNode root = TreeNode(3, &layer2_1, &layer2_2);

    Solution s;
    cout << s.maxDepth(&root) << endl;

    //[1, null, 2]
    layer2_2 = TreeNode(2);
    root = TreeNode(1, NULL, &layer2_2);
    cout << s.maxDepth(&root) << endl;

    //[]
    cout << s.maxDepth(NULL) << endl;
    //[0]
    root = TreeNode(0, NULL, NULL);
    cout << s.maxDepth(&root) << endl;
    return 0;
}
