// 236. Lowest Common Ancestor of a Binary Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/


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
    TreeNode* findLCA(TreeNode* root, TreeNode *p, TreeNode* q, bool &np, bool &nq) {

        if (root == NULL)
            return NULL;

        if (root == p) {
            np = true;
            return root;
        }
        else if (root == q) {
            nq = true;
            return root;
        }

        TreeNode* left   = findLCA(root -> left, p, q, np, nq);
        TreeNode* right  = findLCA(root -> right, p, q, np, nq);
    
        if (left && right)
            return root;

        return left ? left : right;
    }

    bool findNode(TreeNode* root, TreeNode* n) {

        if (root == NULL)
            return false;

        if (root == n)
            return true;

        return findNode(root -> left, n) || findNode(root -> right, n);
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        bool np = false;
        bool nq = false;

        TreeNode* lca = findLCA(root, p, q, np, nq);
    
        if ((np && nq) || (np && findNode(root, q)) || (nq && findNode(root, p)))
            return lca;

        return NULL;
    }
};