// 2326. Spiral Matrix IV
// https://leetcode.com/problems/spiral-matrix-iv/description

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
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
       
		vector<vector<int>> v(m, vector<int> (n, -1));

		int top = 0;
		int right = n - 1; 
		int bottom = m - 1;
		int left = 0;

       	while  (top <= bottom && left <= right) {

            // cout << "L-to-R: ";
       		for (int i = left ; i <= right ; i++) {

       			if (head == NULL)
       				break;
                // cout << "(" << top << ", " << i << ") -- ";
       			v[top][i] = head -> val;
       			head = head -> next;
       		}
            // cout << "\n";

       		top++;

            // cout << "T-to-B: ";
       		for (int i = top ; i <= bottom ; i++) {

       			if (head == NULL)
       				break;
                // cout << "(" << i << ", " << right << ") -- ";
       			v[i][right] = head -> val;
       			head = head -> next;
       		}
            // cout << "\n";
       		right--;

       		if (top <= bottom) {

                // cout << "R-to-L: ";
       			for (int i = right ; i >= left ; i--) {

       				if (head == NULL)
       					break;

                    // cout << "(" << bottom << ", " << i << ") -- ";
       				v[bottom][i] = head -> val;
       				head = head -> next;
       			}
                // cout << "\n";
       			bottom--;
       		}

       		if (left <= right) {

                // cout << "B-to-T: ";
       			for (int i = bottom ; i >= top ; i--) {

       				if (head == NULL)
       					break;
                    // cout << "(" << i << ", " << left << ") -- ";
       				v[i][left] = head -> val;
       				head = head -> next;
       			}
                // cout << "\n";
       			left++;
       		}
        }

        return v;
    }
};