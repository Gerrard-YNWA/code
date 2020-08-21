/*
 * @lc app=leetcode id=82 lang=cpp
 *
 * [82] Remove Duplicates from Sorted List II
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
        if(!head or !head->next){
            return head;
        }
        //remove repeated from head
        auto *cur= head;
        while(true) {
            cur = skipRepeated(cur);
            if(!cur or !cur->next)
                return cur;
            if(cur->val != cur->next->val)
                break;
        }
        head = cur;
        ListNode *prev = cur, *tmp;
        cur = cur->next;
        while(cur) {
            tmp = cur;
            cur = skipRepeated(cur);
            if(!cur){
                prev->next = nullptr;
                break;
            }
            if(cur == tmp) {
                prev->next = cur;
                prev = cur;
                cur = cur->next;
            }
        }
        return head;       
    }
private:
    ListNode* skipRepeated(ListNode *cur) {
        auto repeated = 0; 
        while(cur and cur->next and cur->val == cur->next->val){
            cur->next = cur->next->next;
            repeated = 1;
        }
        return repeated ? cur->next : cur;
    }
};
// @lc code=end

int main(){
    Solution s;
    ListNode* l = new ListNode(1);
    ListNode* head = l;
    /*
    l->next = new ListNode(1);
    l->next->next = new ListNode(2);
    l->next->next->next = new ListNode(3);
    l->next->next->next->next = new ListNode(4);
    l->next->next->next->next->next = new ListNode(5);
    l->next->next->next->next->next->next = new ListNode(5);
    l->next->next->next->next->next->next->next = new ListNode(6);
    l->next->next->next->next->next->next->next->next = new ListNode(7);
    l->next->next->next->next->next->next->next->next->next = new ListNode(7);
    l->next->next->next->next->next->next->next->next->next->next = new ListNode(8);
    */
    l->next = new ListNode(2);
    l->next->next = new ListNode(3);
    l->next->next->next = new ListNode(3);
    l->next->next->next->next = new ListNode(4);
    l->next->next->next->next->next = new ListNode(4);
    l->next->next->next->next->next->next = new ListNode(5);
    printLinkList(head);
    head = s.deleteDuplicates(head);
    printLinkList(head);
    

    return 0;
}
