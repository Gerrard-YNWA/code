/*
 * @lc app=leetcode id=25 lang=cpp
 *
 * [25] Reverse Nodes in k-Group
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head or !head->next or k == 1)
            return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *cur = head, *prev, *next;
        auto num = 0;
        while(cur) {
            num++;
            cur = cur->next;
        }
        prev = dummy;
        while(num >= k) {
            cur = prev->next;
            next = cur->next;
            for(auto i = 1; i < k; i++){
                cur->next = next->next;
                next->next = prev->next;
                prev->next = next;
                next = cur->next;
            }
            prev = cur;
            num -= k;
        }
        return dummy->next;
    }
};
// @lc code=end

int main(){
    ListNode *head = makeLinkList({1,2,3,4,5,6,7,8,9});
    printLinkList(head);
    Solution s;
    head = s.reverseKGroup(head, 4);
    printLinkList(head);
    return 0;
}

