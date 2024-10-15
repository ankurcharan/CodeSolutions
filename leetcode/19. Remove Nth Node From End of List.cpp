// 19. Remove Nth Node From End of List
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {

		// no items removal needed        
        if (head == NULL || n <= 0)
        	return head;

        ListNode* fast = head;
        ListNode* slow = head;

        while (n) {
        	fast = fast -> next;
        	n--;

        	if (fast == NULL && n != 0)
        	{
        		// n > len(head)
        		return NULL;		
        	}
        }

        if (fast == NULL) {
        	return head -> next;
        }

        // if (fast)
        //     cout << "f:  " << fast -> val << ", s: " << slow -> val << "\n";
        // else
        //     cout << "f: null, s: " << slow -> val << "\n";

        while (fast && fast -> next) {
        	slow = slow -> next;
        	fast = fast -> next;
        }

        if (slow && slow -> next)
        {
        	slow -> next = slow -> next -> next;
        }

        return head;
    }
};