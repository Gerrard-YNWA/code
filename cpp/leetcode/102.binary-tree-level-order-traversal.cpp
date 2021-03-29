/*
 * @lc app=leetcode id=102 lang=cpp
 *
 * [102] Binary Tree Level Order Traversal
 */
#include <iostream>
#include <queue>
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root)
            return result;

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            auto nodes = q.size();
            vector<int> layer;
            for (auto i = 0; i < nodes; i++) {
                auto node = q.front();
                q.pop();
                layer.push_back(node->val);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            result.push_back(layer);
            layer.clear();
        }
        return result;
    }
};
// @lc code=end

void printVec(vector<int> arr) {
    if (arr.size() > 0) {
        cout << "[";
        for (auto i = 0; i < arr.size(); i++) {
            cout << arr[i] << ",";
        }
        cout << "]";
    }
}

void print(vector<vector<int>> arr) {
    cout << "[";
    for (auto i = 0; i < arr.size(); i++) {
        printVec(arr[i]);
    }
    cout << "]" << endl;
}

int main() {
    TreeNode layer3_3 = TreeNode(15);
    TreeNode layer3_4 = TreeNode(7);
    TreeNode layer2_1 = TreeNode(9);
    TreeNode layer2_2 = TreeNode(20, &layer3_3, &layer3_4);
    TreeNode root = TreeNode(3, &layer2_1, &layer2_2);

    Solution s;
    print(s.levelOrder(&root));
    print(s.levelOrder(NULL));

    root = TreeNode(1, NULL, NULL);
    print(s.levelOrder(&root));
}
