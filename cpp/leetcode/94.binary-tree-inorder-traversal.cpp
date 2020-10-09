/*
 * @lc app=leetcode id=94 lang=cpp
 *
 * [94] Binary Tree Inorder Traversal
 */
#include <iostream>
#include <stack>
#include <vector>

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
    vector<int> inorderTraversal(TreeNode* root) {
        /*
        if (root) {
            inorderTraversal(root->left);
            ans.push_back(root->val);
            inorderTraversal(root->right);
        }
        return ans;
        */
        TreeNode* cur = root;
        while (cur or !s.empty()) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            s.pop();
            ans.push_back(cur->val);
            cur = cur->right;
        }
        return ans;
    }

   private:
    vector<int> ans;
    stack<TreeNode*> s;
};
// @lc code=end

void printVector(vector<int> vec) {
    for (auto i = 0; i < vec.size(); i++) {
        cout << vec[i] << " -> ";
    }
    cout << endl;
}

int main() {
    Solution s;

    TreeNode left = TreeNode(3);
    TreeNode right = TreeNode(2, &left, nullptr);
    TreeNode p1 = TreeNode(1, nullptr, &right);
    // p1 = TreeNode(1);

    // left = TreeNode(2);
    // p1 = TreeNode(1, &left, nullptr);

    // p1 = TreeNode(1, nullptr, &left);

    printVector(s.inorderTraversal(&p1));

    return 0;
}
