/*
 * @lc app=leetcode id=61 lang=cpp
 *
 Given a linked list, rotate the list to the right by k places, where k is non-negative.

 Example 1:

 Input: 1->2->3->4->5->NULL, k = 2
 Output: 4->5->1->2->3->NULL
 Explanation:
 rotate 1 steps to the right: 5->1->2->3->4->NULL
 rotate 2 steps to the right: 4->5->1->2->3->NULL
 Example 2:

 Input: 0->1->2->NULL, k = 4
 Output: 2->0->1->NULL
 Explanation:
 rotate 1 steps to the right: 2->0->1->NULL
 rotate 2 steps to the right: 1->2->0->NULL
 rotate 3 steps to the right: 0->1->2->NULL
 rotate 4 steps to the right: 2->0->1->NULL

 * [61] Rotate List
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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head)
            return head;
        ListNode* l1 = head;
        auto len = 1;
        while(l1->next) {
            l1 = l1->next;
            len++;
        }
        l1->next = head;
        auto step = k % len;
        for(auto i = 0; i < len - step; i++){
            l1 = l1->next;
        }
        head = l1->next;
        l1->next = nullptr;
        return head;
    }
};
// @lc code=end
//

int main() {
    Solution s;
    ListNode* l = new ListNode(1);
    ListNode *head = l;
    for(auto i = 2; i < 6; i++) {
        ListNode* tmp = new ListNode(i);
        l->next = tmp;
        l = l->next;
    }

    head = s.rotateRight(head, 100);
    while(head) {
        std::cout<<head->val<<"->";
        head = head->next;
    }
    std::cout<<std::endl;

    ListNode* l2 = new ListNode(0);
    head = l2;
    for(auto i = 1; i < 3; i++) {
        ListNode* tmp = new ListNode(i);
        l2->next = tmp;
        l2 = l2->next;
    }

    head = s.rotateRight(head, 4);
    while(head) {
        std::cout<<head->val<<"->";
        head = head->next;
    }
    std::cout<<std::endl;
    return 0;
}
