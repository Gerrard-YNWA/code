/*
 * @lc app=leetcode id=113 lang=cpp
 *
 * [113] Path Sum II
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
    /*
   private:
    vector<vector<int>> res;
    void dfs(TreeNode* root, vector<int>& tmp, int sum) {
        if (!root)
            return;
        tmp.push_back(root->val);
        if (root->val == sum && !root->left && !root->right) {
            res.push_back(tmp);
        }
        dfs(root->left, tmp, sum - root->val);
        dfs(root->right, tmp, sum - root->val);
        tmp.pop_back();
    }
    */

   public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        /*
        res.clear();
        dfs(root, tmp, targetSum);
        return res;
        */
        vector<vector<int>> res;
        stack<TreeNode*> s;
        vector<int> tmp;
        TreeNode *cur = root, *pre = nullptr;
        auto cur_sum = 0;

        while (!s.empty() || cur) {
            if (cur) {
                s.push(cur);
                tmp.push_back(cur->val);
                cur_sum += cur->val;
                if (!cur->left && !cur->right && cur_sum == targetSum) {
                    res.push_back(tmp);
                }
                cur = cur->left;
            } else {
                auto top = s.top();
                if (!top->right || top->right == pre) {
                    s.pop();
                    tmp.pop_back();
                    cur_sum -= top->val;
                    pre = top;
                } else {
                    cur = top->right;
                }
            }
        }
        return res;
    }
};
// @lc code=end

void printVectorVector(vector<vector<int>>& vec) {
    cout << "[";
    for (auto i = 0; i < vec.size(); i++) {
        cout << "[";
        for (auto j = 0; j < vec[i].size() - 1; j++) {
            cout << vec[i][j] << ",";
        }
        if (i < vec.size() - 1) {
            cout << vec[i][vec[i].size() - 1] << "], ";
        } else {
            cout << vec[i][vec[i].size() - 1] << "]";
        }
    }
    cout << "]" << endl;
}

int main() {
    //[5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
    //          5
    //        /   \
    //      4       8
    //     /       / \
    //    11      13  4
    //   /  \        / \
    //  7    2      5   1
    TreeNode layer_3_0 = TreeNode(7);
    TreeNode layer_3_1 = TreeNode(2);
    TreeNode layer_3_2 = TreeNode(5);
    TreeNode layer_3_3 = TreeNode(1);
    TreeNode layer_2_0 = TreeNode(11, &layer_3_0, &layer_3_1);
    TreeNode layer_2_1 = TreeNode(13);
    TreeNode layer_2_2 = TreeNode(4, &layer_3_2, &layer_3_3);
    TreeNode layer_1_0 = TreeNode(4, &layer_2_0, nullptr);
    TreeNode layer_1_1 = TreeNode(8, &layer_2_1, &layer_2_2);
    TreeNode root = TreeNode(5, &layer_1_0, &layer_1_1);
    Solution s;
    auto vv = s.pathSum(&root, 22);
    printVectorVector(vv);

    root = TreeNode(1, new TreeNode(2), new TreeNode(3));
    vv = s.pathSum(&root, 5);
    printVectorVector(vv);

    root = TreeNode(1, new TreeNode(2), nullptr);
    vv = s.pathSum(&root, 0);
    printVectorVector(vv);

    // 1,0,1,1,2,0,-1,0,1,-1,0,-1,0,1,0
    //            1
    //        /       \
    //      0          1
    //     /  \       /  \
    //   1     2     0    -1
    //  / \   / \   / \   / \
    // 0   1 -1  0 -1  0 1   0

    TreeNode a = TreeNode(1, new TreeNode(0), new TreeNode(1));
    TreeNode b = TreeNode(2, new TreeNode(-1), new TreeNode(0));
    TreeNode c = TreeNode(0, new TreeNode(-1), new TreeNode(0));
    TreeNode d = TreeNode(-1, new TreeNode(1), new TreeNode(0));
    TreeNode e = TreeNode(0, &a, &b);
    TreeNode f = TreeNode(1, &c, &d);
    root = TreeNode(1, &e, &f);
    vv = s.pathSum(&root, 2);
    printVectorVector(vv);
    return 0;
}
