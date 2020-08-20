/*
 * @lc app=leetcode id=19 lang=cpp
 *
 * [19] Remove Nth Node From End of List
 */
#include<iostream>

using namespace std;

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode* createLinkList(ListNode* head, int value) {
    ListNode *p = (ListNode*) malloc(sizeof(ListNode));
    p->val = value;
    p->next = NULL;
    if (head == NULL) {
        head = p;
    } else {
        p->next = head;
        head = p;
    }
    return head;
}

void printLinkList(ListNode* head) {
    ListNode* cur = head;
    while (cur) {
        cout<<cur->val<<"->";
        cur = cur->next;
    }
    cout<<endl;
}
// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto slow = head, fast = head;
        for (auto i = 0; i < n; i++)
            fast = fast->next;
        if (!fast)
            return head->next;
        while(fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return head;
    }
};
// @lc code=end

int main() {
    ListNode* head = NULL;
    for (auto i = 1; i < 10; i++){
        head = createLinkList(head, i);
    }
    printLinkList(head);
    auto s = new Solution();
    printLinkList(s->removeNthFromEnd(head, 5));
    return 0;
}
