#ifndef _TREE_HPP_
#define _TREE_HPP_
#include <queue>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};

void FloorPrint(TreeNode *root) {
    std::queue<TreeNode *> q;
    if (root != NULL) {
        q.push(root);
    }

    while (!q.empty()) {
        std::cout << q.front()->val << " -> ";
        if (q.front()->left != NULL) {
            q.push(q.front()->left);
        }
        if (q.front()->right != NULL) {
            q.push(q.front()->right);
        }
        q.pop();
    }
    std::cout << std::endl;
}

TreeNode *CreateTree(std::vector<int> vec, int start) {
    if (vec[start] == '#') {
        return NULL;
    }

    TreeNode *root = new TreeNode(vec[start]);

    int lnode = 2 * start + 1;
    int rnode = 2 * start + 2;
    if (lnode > vec.size() - 1) {
        root->left = NULL;
    } else {
        root->left = CreateTree(vec, lnode);
    }

    if (rnode > vec.size() - 1) {
        root->right = NULL;
    } else {
        root->right = CreateTree(vec, rnode);
    }

    return root;
}
#endif
