// 21. Merge Two Sorted Lists
// https://leetcode.com/problems/merge-two-sorted-lists/description/

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
	ListNode* mergedList(ListNode* a, ListNode* b) {

		ListNode* head = NULL;
		ListNode* curr = NULL;

		if (a -> val <= b -> val) {
			head = curr = a;
			a = a -> next;
		} 
		else {
			head = curr = b;
			b = b -> next;
		}

		while (a && b) {

			if (a -> val <= b -> val) {
				curr -> next = a;
				a = a -> next;
			}
			else {
				curr -> next = b;
				b = b -> next;
			}

			curr = curr -> next;
		}

		while (a) {
			curr -> next = a;
			a = a -> next;
            curr = curr -> next;
        }

		while (b) {
			curr -> next = b;
			b = b -> next;
            curr = curr -> next;
		}

		return head;
	}

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
  
    	if (list1 == NULL)	return list2;
    	if (list2 == NULL)	return list1;

    	return mergedList(list1, list2);
    }
};