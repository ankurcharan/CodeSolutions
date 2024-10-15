// 876. Middle of the Linked List
// https://leetcode.com/problems/middle-of-the-linked-list/description/


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
    ListNode* middleNode(ListNode* head) {
  		
  		if (head == NULL)
  			return NULL;

  		ListNode* slow = head;
  		ListNode* fast = head;		// for two nodes and later to choose
  									// if you do (head -> next) then first one is chosen 
    
  		while (fast && fast -> next) {

  			slow = slow -> next;
  			fast = fast -> next -> next;
  		}

  		return slow;
    }
};