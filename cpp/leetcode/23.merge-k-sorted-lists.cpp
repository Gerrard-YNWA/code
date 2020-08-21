/*
 * @lc app=leetcode id=23 lang=cpp
 *
 * [23] Merge k Sorted Lists
 */
#include<iostream>
#include<linkedlist.hpp>
#include<vector>
using namespace std;
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) 
            return nullptr;
        auto len = lists.size();
        while(len > 1) {
            //分治
            for(auto i = 0; i< len / 2; i++){
                lists[i] = mergeTwoLists(lists[i], lists[len - 1 - i]);
            }
            len = (len + 1)/2;
        }
        return lists.front();
    }
private:
    ListNode* mergeTwoLists(ListNode *l1, ListNode *l2){
        ListNode* head;
        if(l1 && l2){
            if(l1->val < l2->val){
                head = new ListNode(l1->val);
                l1 = l1->next;
            }else{
                head = new ListNode(l2->val);
                l2 = l2->next;
            }
        }else if(!l2){
            return l1;
        }else{
            return l2;
        }
        ListNode* tail = head;
        while(l1 != NULL && l2 != NULL){
            if(l1->val < l2->val){
                tail->next = l1;
                l1 = l1->next;
            }else{
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if(l1 == NULL){
            tail->next = l2;
        }
        if (l2 == NULL){
            tail->next = l1;
        }
        return head;
    }
};
// @lc code=end
//
int main(){
    vector<ListNode*>vec;
    auto head = makeLinkList({1,4,5});
    vec.push_back(head);
    head = makeLinkList({1,3,4});
    vec.push_back(head);
    head = makeLinkList({2,6});
    vec.push_back(head);
    Solution s;
    head = s.mergeKLists(vec);
    printLinkList(head);
    return 0;
}
