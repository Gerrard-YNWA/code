/*
 * @lc app=leetcode id=155 lang=cpp
 *
 * [155] Min Stack
 */
#include <climits>
#include <iostream>
#include <stack>

using namespace std;
// @lc code=start
class MinStack {
   public:
    /** initialize your data structure here. */
    MinStack() {
        _min = INT_MAX;
    }

    void push(int val) {
        if (_min >= val) {
            _stack.push(_min);
            _min = val;
        }
        _stack.push(val);
    }

    void pop() {
        int top = _stack.top();
        if (top == _min) {
            _stack.pop();
            _min = _stack.top();
        }
        _stack.pop();
    }

    int top() {
        return _stack.top();
    }

    int getMin() {
        return _min;
    }

   private:
    int _min;
    stack<int> _stack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

int main() {
    MinStack *minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    cout << minStack->getMin() << endl;
    minStack->pop();
    cout << minStack->top() << endl;
    cout << minStack->getMin() << endl;

    return 0;
}
