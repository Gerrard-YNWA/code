/*
 * @lc app=leetcode id=101 lang=cpp
 *
 * [101] Symmetric Tree
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
    bool isSymmetric(TreeNode* root) {
        std::queue<TreeNode*> q;
        if (!root) {
            return true;
        }
        q.push(root->left);
        q.push(root->right);
        while (!q.empty()) {
            auto left = q.front();
            q.pop();
            auto right = q.front();
            q.pop();
            if (!left && !right) {
                continue;
            } else if (!left || !right) {
                return false;
            } else {
                if (left->val != right->val) {
                    return false;
                }
                q.push(left->left);
                q.push(right->right);
                q.push(left->right);
                q.push(right->left);
            }
        }
        return true;
    }
    */
    bool isSymmetric(TreeNode *root) {
        if (!root)
            return true;
        return compare(root->left, root->right) && compare(root->right, root->left);
    }

   private:
    bool compare(TreeNode *left, TreeNode *right) {
        if (!left && !right) {
            return true;
        } else if (!left || !right) {
            return false;
        } else {
            if (left->val != right->val) {
                return false;
            } else {
                return compare(left->left, right->right) && compare(left->right, right->left);
            }
        }
    }
};
// @lc code=end

int main() {
    TreeNode layer3_1 = TreeNode(3);
    TreeNode layer3_2 = TreeNode(4);
    TreeNode layer3_3 = TreeNode(4);
    TreeNode layer3_4 = TreeNode(3);
    TreeNode layer2_1 = TreeNode(2, &layer3_1, &layer3_2);
    TreeNode layer2_2 = TreeNode(2, &layer3_3, &layer3_4);
    TreeNode root = TreeNode(1, &layer2_1, &layer2_2);

    Solution s;
    FloorPrint(&root);
    cout << s.isSymmetric(&root) << endl;

    layer3_2 = TreeNode(3);
    layer3_4 = TreeNode(3);
    layer2_1 = TreeNode(2, NULL, &layer3_2);
    layer2_2 = TreeNode(2, NULL, &layer3_4);
    root = TreeNode(1, &layer2_1, &layer2_2);
    FloorPrint(&root);
    cout << s.isSymmetric(&root) << endl;
    return 0;
}
