// 24. Swap Nodes in Pairs
// https://leetcode.com/problems/swap-nodes-in-pairs/description/

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
	ListNode* swappingNodeDataIterative(ListNode* head) {

		ListNode* curr = head;

        while (curr && curr -> next) {
        	// swap node data
        	swap(curr -> val, curr -> next -> val);
        	curr = curr -> next -> next;
        }

        return head;
	}

	ListNode* swappingNodeDataRecursive(ListNode* head) {

		if (head && head -> next) {
			swap (head -> val, head -> next -> val);
			swappingNodeDataRecursive(head -> next -> next);
		}

		return head;
	}

	ListNode* swappingLinksIterative(ListNode* head) {

		if (head == NULL || head -> next == NULL)
			return head;

		ListNode* prev = head;
		ListNode* curr = head -> next;

		head = curr;	// new head will be 2nd node

		while (true) {

			ListNode* next = curr -> next;
			curr -> next = prev;

			// next is NULL or last node
			if (next == NULL || next -> next == NULL) {

				// either NULL or last node
				prev -> next = next;
				break;		// end of list
			}

			prev -> next = next -> next;
			prev = next;
			curr = prev -> next;
		}

		return head;
	}


	ListNode* swappingLinksRecursive(ListNode* head) {

		if (head == NULL || head -> next == NULL)
			return head;

		ListNode* remaining = head -> next -> next;

		ListNode* newHead = head -> next;
		newHead -> next = head;
		head -> next = swappingLinksRecursive(remaining);

		return newHead;
	}


    ListNode* swapPairs(ListNode* head) {
        
        // return swappingNodeDataIterative(head);

        // return swappingNodeDataRecursive(head);

        // return swappingLinksIterative(head);

        return swappingLinksRecursive(head);
    }
};