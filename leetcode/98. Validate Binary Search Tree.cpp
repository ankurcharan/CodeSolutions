// 98. Validate Binary Search Tree
// https://leetcode.com/problems/validate-binary-search-tree/


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
	bool validateBST(TreeNode* root, int min, int max) {

		if (root == NULL)
			return true;

		if (root -> val < min || root -> val > max) 
			return false;

        bool ans = true;

        // if current is INT_MIN or INT_MAX
        // since values can't be repeated 
        // so their left/right chils should not exists
        // there can only be one INT_MIN and INT_MAX in the tree
        if (root -> val == INT_MIN)
            ans = ans && (root -> left == NULL);
        if (root -> val == INT_MAX)
            ans = ans && (root -> right == NULL);

        // check for left and right subtree
        if (root -> left)
            ans = ans && validateBST(root -> left, min, root -> val - 1);
        if (root -> right)
            ans = ans && validateBST(root -> right, root -> val + 1, max);

		return ans;
	}

    bool isValidBST(TreeNode* root) {
        
        return validateBST(root, INT_MIN, INT_MAX);
    }
};