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
	// (diameter, height)
	pair<int, int> getDiameter(TreeNode* root) {

		if (root == NULL) 
			return { 0, 0 };
        
        // if (root -> left == NULL && root -> right == NULL)
            // return { 0, 0 };

		pair<int, int> l = getDiameter(root -> left);
		pair<int, int> r = getDiameter(root -> right);

		// height
		int h = max(l.second, r.second) + 1;

		return { max(l.second + r.second + 1, max(l.first, r.first)), h };
	}

    int diameterOfBinaryTree(TreeNode* root) {

        if (root == NULL)
            return 0;
        
        return getDiameter(root).first > 0 ? getDiameter(root).first - 1 : 0;
    }
};