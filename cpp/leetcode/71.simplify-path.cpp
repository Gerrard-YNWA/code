/*
 * @lc app=leetcode id=71 lang=cpp
 *
 * [71] Simplify Path
 */
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
   public:
    string simplifyPath(string path) {
        stack<string> slash_stack;
        string tmp = "";
        int len = path.size();
        for (auto i = 0; i < len; i++) {
            if (path[i] == '/') {
                if (tmp == ".") {
                } else if (tmp == "..") {
                    if (!slash_stack.empty()) {
                        slash_stack.pop();
                    }
                } else if (tmp != "") {
                    slash_stack.push("/" + tmp);
                }
                tmp = "";
            } else {
                tmp = tmp + path[i];
            }
        }

        if (tmp == ".") {
            tmp = "";
        } else if (tmp == "..") {
            if (!slash_stack.empty()) {
                slash_stack.pop();
            }
            tmp = "";
        }
        if (tmp != "") tmp = "/" + tmp;
        if (slash_stack.empty() and tmp == "") tmp = "/";

        while (!slash_stack.empty()) {
            tmp = slash_stack.top() + tmp;
            slash_stack.pop();
        }
        return tmp;
    }
};
// @lc code=end

int main() {
    Solution s;
    vector<string> input = {"/home/", "/../", "/home//foo/", "/a/./b/../../c/", "/a/../../b/../c//.//", "/a//b////c/d//././/..", "/home", "abc", "/...", "/a//b////c/d//././/..", "/abc/...", "/../"};
    for (auto it = input.begin(); it != input.end(); it++) {
        cout << s.simplifyPath(*it) << endl;
    }
    return 0;
}
