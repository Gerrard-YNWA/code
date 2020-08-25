/*
 * @lc app=leetcode id=86 lang=cpp
 *
 * [86] Partition List
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
    ListNode* partition(ListNode* head, int x) {
        if(!head or !head->next)
            return head;
        ListNode *dummy1 = new ListNode(0);
        ListNode *dummy2 = new ListNode(0);
        ListNode *left = dummy1, *right = dummy2;
        while(head){
            if(head->val >= x){
                right->next = head;
                right = right->next;
            }else{
                left->next = head;
                left = left->next;
            }
            head = head->next;
        }
        right->next = nullptr;
        left->next = dummy2->next;
            
        return dummy1->next;
    }
};
// @lc code=end

int main(){
    Solution s;
    ListNode *head = makeLinkList({1,4,3,2,5,2});
    printLinkList(head);
    head = s.partition(head, 3);
    printLinkList(head);
    return 0;
}
