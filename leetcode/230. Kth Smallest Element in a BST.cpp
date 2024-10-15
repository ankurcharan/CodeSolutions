// 230. Kth Smallest Element in a BST
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/

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
	TreeNode* getKthSmallest(TreeNode* root, int k, int& count) {

		if (root == NULL)
			return NULL;

        // cout << (root -> val) << " \n";

		TreeNode* l = getKthSmallest(root -> left, k, count);
		if (l != NULL)
			return l;

		count++;
		if (count == k)
			return root;

		return getKthSmallest(root -> right, k, count);
	}

    int kthSmallest(TreeNode* root, int k) {
  		
  		int count = 0;
  		TreeNode* ans = getKthSmallest(root, k, count);
        return ans == NULL ? -1 : ans -> val;      
    }
};