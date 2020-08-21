#ifndef _LINKED_LIST_HPP_
#define _LINKED_LIST_HPP_
//Definition for singly-linked list.
#include<vector>
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

void printLinkList(ListNode *head) {
    while(head) {
        std::cout<<head->val<<"->";
        head = head->next;
    }
    std::cout<<std::endl;
}

ListNode* makeLinkList(std::vector<int> v){
    if(v.size() == 0)
        return nullptr; 
    ListNode *head = new ListNode(v[0]);
    ListNode *p = head;
    for(auto i = 1; i < v.size(); i++){
        ListNode *node = new ListNode(v[i]);
        p->next = node;
        p = node;
    }
    return head;
}


#endif
