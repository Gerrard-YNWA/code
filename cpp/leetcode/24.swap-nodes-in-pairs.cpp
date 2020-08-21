/*
 * @lc app=leetcode id=24 lang=cpp
 *
 * [24] Swap Nodes in Pairs
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
    /* 递归
    ListNode* swapPairs(ListNode* head) {
        if (!head)
            return nullptr;
        if (!head->next)
            return head;
        ListNode* p1 = head;
        ListNode* p2 = head->next;
        p1->next = swapPairs(p2->next);
        p2->next = p1;
        return p2;   
    }
    */
    //非递归
    ListNode* swapPairs(ListNode* head) {
        if(!head or !head->next) {
            return head;
        }
        //辅助节点，保存起始位置
        ListNode* l0 = new ListNode();
        l0->next = head->next;
        ListNode *l1 = head, *l2, *l3;
        while(l1->next) {
            l2 = l1->next;
            l3 = l1->next->next;
            l2->next = l1;
            if(!l3){
                l1->next = nullptr;
                break;
            }
            if(!l3->next){
                l1->next = l3;
                l1 = l2;
                break;
            }
            l1->next = l3->next;
            l1 = l3;
        }
        return l0->next;
    }
};
// @lc code=end

int main(){
    Solution s;
    ListNode* l = new ListNode(0);
    ListNode* head = l;
    for (auto i = 1; i < 8; i++) {
        ListNode* tmp = new ListNode(i);
        l->next = tmp;
        l = l->next;
    }
    head = s.swapPairs(head);
    printLinkList(head);
}
