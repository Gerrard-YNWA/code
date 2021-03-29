/*
 * @lc app=leetcode id=103 lang=cpp
 *
 * [103] Binary Tree Zigzag Level Order Traversal
 */
#include <iostream>
#include <queue>
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root)
            return result;
        queue<TreeNode*> q;
        q.push(root);
        auto flapy = true;
        while (!q.empty()) {
            vector<int> layer;
            stack<TreeNode*> s;
            auto nodes = q.size();
            for (auto i = 0; i < nodes; i++) {
                auto node = q.front();
                q.pop();
                layer.push_back(node->val);
                if (flapy) {
                    if (node->left) {
                        s.push(node->left);
                    }
                    if (node->right) {
                        s.push(node->right);
                    }
                } else {
                    if (node->right) {
                        s.push(node->right);
                    }
                    if (node->left) {
                        s.push(node->left);
                    }
                }
            }
            result.push_back(layer);
            layer.clear();
            while (!s.empty()) {
                q.push(s.top());
                s.pop();
            }
            flapy = flapy ? false : true;
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
    print(s.zigzagLevelOrder(&root));
    print(s.zigzagLevelOrder(NULL));

    root = TreeNode(1, NULL, NULL);
    print(s.zigzagLevelOrder(&root));

    //[1,2,3,4,null,null,5]
    TreeNode layer3_1 = TreeNode(4);
    layer3_4 = TreeNode(5);
    layer2_1 = TreeNode(2, &layer3_1, nullptr);
    layer2_2 = TreeNode(3, nullptr, &layer3_4);
    root = TreeNode(1, &layer2_1, &layer2_2);
    print(s.zigzagLevelOrder(&root));
}
