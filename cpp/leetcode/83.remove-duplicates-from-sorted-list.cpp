/*
 * @lc app=leetcode id=83 lang=cpp
 *
 * [83] Remove Duplicates from Sorted List
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head or !head->next)
            return head;
        ListNode *l = head;
        while(l) {
            while(l->next and l->val == l->next->val){
                l->next = l->next->next;
            }
            l = l->next;
        }
        return head;   
    }
};
// @lc code=end
int main(){
    Solution s;
    ListNode* l = new ListNode(1);
    ListNode* head = l;
    l->next = new ListNode(1);
    l->next->next = new ListNode(1);
    l->next->next->next = new ListNode(1);
    //l->next->next = new ListNode(2);
    //l->next->next->next = new ListNode(3);
    //l->next->next->next->next = new ListNode(3);
    head = s.deleteDuplicates(head);
    while(head) {
        std::cout<<head->val<<"->";
        head = head->next;
    }
    std::cout<<std::endl;
    return 0;
}
