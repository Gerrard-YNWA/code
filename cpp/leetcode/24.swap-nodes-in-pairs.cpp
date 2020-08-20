/*
 * @lc app=leetcode id=24 lang=cpp
 *
 * [24] Swap Nodes in Pairs
 */
#include<iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
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
};
// @lc code=end

int main(){
    Solution s;
    ListNode* l = new ListNode(0);
    ListNode* head = l;
    for (auto i = 1; i < 10; i++) {
        ListNode* tmp = new ListNode(i);
        l->next = tmp;
        l = l->next;
    }
    head = s.swapPairs(head);
    while(head) {
        std::cout<<head->val<<"->";
        head = head->next;
    }
    std::cout<<std::endl;
}
