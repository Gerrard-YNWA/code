#include<iostream>
#include<linkedlist.hpp>

class Solution {
public:
    ListNode* reverse(ListNode* head) {
        ListNode *cur = head, *prev = nullptr, *next = nullptr;
        while(cur){
           next = cur->next; //保存当前节点的下一个节点
           cur->next = prev; //更新当前节点的指针域
           prev = cur; //更新当前节点上一个节点的位置
           cur = next; //更新当前节点的位置
        }
        head = prev;//更新头指针指向新链表第一个节点
        return head;
    }
};
// @lc code=end

int main(){
    Solution s;
    ListNode *head = makeLinkList({1,2,3,4,5});
    head = s.reverse(head);
    printLinkList(head);
    return 0;
}

