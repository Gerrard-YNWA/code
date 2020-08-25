/*
 * @lc app=leetcode id=92 lang=cpp
 *
 * [92] Reverse Linked List II
 */
#include<iostream>
#include<linkedlist.hpp>
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *prev = dummy;
        for(auto i = 0; i < m - 1; i++){//find start
            prev = prev->next;
        }
        ListNode *cur = prev->next, *next;
        for(auto i = m; i < n; i++){
            next = cur->next;
            cur->next = next->next;
            next->next = prev->next;
            prev->next = next;
        }
        return dummy->next;
    }
};
// @lc code=end

int main(){
    Solution s;
    ListNode *head = makeLinkList({1,2,3,4,5});
    head = s.reverseBetween(head, 2, 4);
    printLinkList(head);
    return 0;
}

