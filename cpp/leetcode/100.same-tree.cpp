/*
 * @lc app=leetcode id=100 lang=cpp
 *
 * [100] Same Tree
 */
#include <iostream>

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p or !q) {
            return p == q;
        }
        return p->val == q->val and isSameTree(p->left, q->left) and isSameTree(p->right, q->right);
    }
};
// @lc code=end

int main() {
    Solution s;
    TreeNode left = TreeNode(2);
    TreeNode right = TreeNode(1);
    TreeNode p1 = TreeNode(1, &left, &right);
    TreeNode p2 = TreeNode(1, &right, &left);
    cout << s.isSameTree(&p1, &p2) << endl;

    right = TreeNode(3);
    p1 = TreeNode(1, &left, &right);
    p2 = TreeNode(1, &left, &right);
    cout << s.isSameTree(&p1, &p2) << endl;

    p1 = TreeNode(1, &left, nullptr);
    p1 = TreeNode(1, nullptr, &left);
    cout << s.isSameTree(&p1, &p2) << endl;

    return 0;
}
