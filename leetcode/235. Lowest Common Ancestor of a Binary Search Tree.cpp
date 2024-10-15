// 235. Lowest Common Ancestor of a Binary Search Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
	bool checkIfExists(TreeNode *root, TreeNode* x) {

		if (root == NULL)
			return false;

		if (root == x)
			return true;

		return checkIfExists(root -> left, x) || checkIfExists(root -> right, x);
    }

	TreeNode* getLCA(TreeNode* root, TreeNode* p, TreeNode* q, bool& pExist, bool& qExist) {

		if (root == NULL)
        	return NULL;

        if (root == p || root == q) {

        	if (root == p)	pExist = true;
        	if (root == q)	qExist = true;
        	return root;
        }

        TreeNode* l = getLCA(root -> left,  p, q, pExist, qExist);
        TreeNode* r = getLCA(root -> right, p, q, pExist, qExist);

        return (l && r) ? root : (l) ? l : r;
	}

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        bool pExist = false;
        bool qExist = false;
        TreeNode* lca = getLCA(root, p, q, pExist, qExist);

        if (lca == NULL)
        	return NULL;

        if (pExist && qExist)
        	return lca;

        if (pExist)
        	return checkIfExists(root, q) ? lca : NULL;
        else
        	return checkIfExists(root, p) ? lca : NULL;
    }
};