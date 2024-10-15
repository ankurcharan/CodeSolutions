// 1367. Linked List in Binary Tree
// https://leetcode.com/problems/linked-list-in-binary-tree/description/

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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
	bool dfs(ListNode* curr, TreeNode* root) {

		if (!curr)				
			return true;	// all nodes in linked list matched

		if (!root)
			return false;	// not matched

		if (curr -> val != root -> val)
			return false;		// value not matched

		return dfs(curr -> next, root -> left) || dfs(curr -> next, root -> right);
	}

	bool checkDFS(ListNode* head, TreeNode* root) {
		
		if (!root)
			return false;

		if (dfs(head, root))
			return true;		// path found

		return checkDFS(head, root -> left) || checkDFS(head, root -> right);
	}

	bool dfsSoln(ListNode* head, TreeNode* root) {

		if (!root)
			return false;

		return checkDFS(head, root);
	}

	bool checkPathMatchIterative(TreeNode* root, ListNode* head) {

		if (!root)
			return false;

        if (!head)          // empty list always true
            return true;

		if (root -> val != head -> val)
			return false;		// first value is unmatched

		stack<pair<TreeNode*, ListNode*>> s;
		s.push({ root, head });

		while (!s.empty()) {

			pair<TreeNode*, ListNode*> f = s.top();
			s.pop();

            // cout << "path match stack pop: " << (f.first -> val) << " , " << (f.second -> val) << "\n";

			if (f.first -> val != f.second -> val)
				continue;

            if (f.second -> next == NULL) // finished list
				return true;

            if (f.first -> right)
				s.push({ f.first -> right, f.second -> next });
			if (f.first -> left)
				s.push({ f.first -> left , f.second -> next });
		}

		return false;		// not matched
	}

	bool dfsIterativeSoln(ListNode* head, TreeNode* root) {

		if (!root)
			return false;	// not found

		stack<TreeNode*> s;
		s.push(root);

		while (!s.empty()) {

			TreeNode* f = s.top();
			s.pop();

            // cout << "s.pop(): " << f-> val << "\n";

			if (checkPathMatchIterative(f, head))
				return true;

			if (f -> left)
				s.push(f -> left);
			if (f -> right)
				s.push(f -> right);
		}

		return false;		// no path found
	}

    bool isSubPath(ListNode* head, TreeNode* root) {
        
        // O(n * m)
        // return dfsSoln(head, root);

        return dfsIterativeSoln(head, root);
    }
};