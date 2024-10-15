// 3217. Delete Nodes From Linked List Present in Array
// https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/description

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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        
        unordered_set<int> s;
        for (int x: nums) {
        	s.insert(x);
        }

        // if head node needs to be deleted
        while (head != NULL and s.find(head -> val) != s.end()) {

            // ListNode* temp = head;
            head = head -> next;
            // delete temp;
        }

        if (head == NULL)
            return NULL;

        ListNode* curr = head;
        while (curr -> next != NULL) {

            if (s.find(curr -> next -> val) != s.end()) {

                // ListNode* t = curr -> next;
                curr -> next = curr -> next -> next;
                // delete t;
            }
            else {
                curr = curr -> next;
            }
        }

        return head;
    }
};