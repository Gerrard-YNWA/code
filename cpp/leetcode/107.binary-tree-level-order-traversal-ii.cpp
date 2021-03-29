/*
 * @lc app=leetcode id=107 lang=cpp
 *
 * [107] Binary Tree Level Order Traversal II
 */
#include <algorithm>
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) {
            return result;
        }
        queue<TreeNode*> q;
        q.push(root);
        stack<vector<int>> s;
        while (!q.empty()) {
            vector<int> layer;
            auto nodes = q.size();
            for (auto i = 0; i < nodes; i++) {
                auto node = q.front();
                q.pop();
                if (node) {
                    layer.push_back(node->val);
                    if (node->left) {
                        q.push(node->left);
                    }
                    if (node->right) {
                        q.push(node->right);
                    }
                }
            }
            s.push(layer);
            layer.clear();
        }
        while (!s.empty()) {
            result.push_back(s.top());
            s.pop();
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
    print(s.levelOrderBottom(&root));
    print(s.levelOrderBottom(NULL));

    root = TreeNode(1, NULL, NULL);
    print(s.levelOrderBottom(&root));
}
