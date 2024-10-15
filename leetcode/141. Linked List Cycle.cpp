// 141. Linked List Cycle
// https://leetcode.com/problems/linked-list-cycle/description/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	bool hashset(ListNode* head) {

		unordered_set<ListNode*> s;

		while (head) {

			if (s.find(head) != s.end())
				return true;

			s.insert(head);
			head = head -> next;
		}

		return false;
	}

	bool floydAlgo(ListNode* head) {

		if (head == NULL)
			return false;

		ListNode* slow = head;
		ListNode* fast = head;

		while (fast && fast -> next) {
			slow = slow -> next;
			fast = fast -> next -> next;

			if (slow == fast)
				return true;
		}

		return false;
	}

    bool hasCycle(ListNode *head) {
        
        // return hashset(head);

        return floydAlgo(head);		// slow/fast pointer
    }
};