// 725. Split Linked List in Parts
// https://leetcode.com/problems/split-linked-list-in-parts/description/

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
	int getLength(ListNode* head) {

		int ans = 0;
		while (head) {
			ans++;
			head = head -> next;
		}

		return ans;
	}

    vector<ListNode*> splitListToParts(ListNode* head, int k) {
  
  		int l = getLength(head);      

  		if (l == 0)
  			return {};

  		// get sizes
  		int left = l % k;
        int sizeEach = l / k;

        // list nodes
  		vector<ListNode*> ans(k, NULL);

  		ListNode* curr = head;
  		int currCount = 0;		// curr node count
  		int split = 0;			// split number
        ans[split++] = curr;

  		while (curr) {

  			currCount++;

  			if (currCount == sizeEach + (left > 0)) {

  				left--;

  				ListNode* next = curr -> next;
  				curr -> next = NULL;
  				curr = next;

                currCount = 0;

                if (split < k)
                    ans[split++] = curr;
  			}
  			else {
	  			curr = curr -> next;
  			}

  		}

  		return ans;
    }
};