// 148. Sort List
// https://leetcode.com/problems/sort-list/description/

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
	void splitList(ListNode* head, ListNode** half) {

		ListNode* slow = head;
		ListNode* fast = head -> next;

		while (fast && fast -> next) {
			fast = fast -> next -> next;
			slow = slow -> next;
		}

		*half = slow -> next;		// second half of list
		slow -> next = NULL;
	}

	ListNode* sortedMerge(ListNode* a, ListNode* b) {

		if (a == NULL)	return b;
		if (b == NULL)	return a;

        // cout << "merging\n";
        // cout << "a: ";
        // printList(a);
        // cout << "b: ";
        // printList(b);

		ListNode* head = NULL;
		ListNode* ans = NULL;

		if (a -> val <= b -> val) {
			ans = head = a;
			a = a-> next;
		}
		else {
			ans = head = b;
			b = b -> next;
		}

		while (a && b) {


			if (a -> val <= b -> val) {
				head -> next = a;
				a = a -> next;
			}
			else {
				head -> next = b;
				b = b -> next;
			}

			head = head -> next;
		}

        // if (a)  cout << "mid: a: " << a -> val << "\n";
        // if (b)  cout << "mid: b: " << b -> val << "\n";

		while (a) {
			head -> next = a;
			a = a -> next;
            head = head -> next;
		}

		while (b) {
			head -> next = b;
			b = b -> next;
            head = head -> next;
		}

        // cout << "merged: ";
        // printList(ans);
		return ans;
	}

    void printList(ListNode* head) {

        while(head) {
            cout << head -> val << " ";
            head = head -> next;
        }
        cout << "\n";
    }

	ListNode* mergeSort(ListNode* head) {

		if (head == NULL || head -> next == NULL)
			return head;

		ListNode* half = NULL;
		splitList(head, &half);

        // cout << "head: ";
        // printList(head);
        // cout << "half: ";
        // printList(half);

        head = mergeSort(head);
        half = mergeSort(half);

		// half = second half of list
		// head = first  half of list

		head = sortedMerge(head, half);

		return head;
	}

	void sortedInsert(ListNode** head, ListNode** node) {

		// minmium or first node
		if ((*head) == NULL || (*head) -> val >= (*node) -> val) {
			(*node) -> next = *head;
			*head = *node;

			return;
		}

        ListNode* curr = *head;
		while (curr -> next && (curr -> next -> val < ((*node) -> val))) {
			curr = curr -> next;
		}

        // cout << "head: " << curr -> val << " herex\n";

		(*node) -> next = curr -> next;
		curr -> next = *node;

        // head = curr;
	}

	ListNode* insertionSort(ListNode* head) {

		ListNode* curr = head;
		ListNode* ans = NULL;

		while (curr != NULL) {

			ListNode* next = curr -> next;
            // cout << "insert: " << curr -> val << "\n";
			sortedInsert(&ans, &curr);
            // printList(ans);
			curr = next;
		}

		return ans;
	}


    ListNode* sortList(ListNode* head) {
        
        // return mergeSort(head);			// O(n logn)

        return insertionSort(head);     // O(n^2)
    }
};