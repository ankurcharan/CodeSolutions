// 105. Construct Binary Tree from Preorder and Inorder Traversal
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/

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
	int search(vector<int> &inorder, int target, int start, int end) {

		for (int i = start ; i <= end ; i++)
		{
			if (inorder[i] == target)
				return i;
		}

		return -1;
	}

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder, int start, int end, int &preIndex) {

    	if (start > end)
    		return NULL;

        // cout << "start: " << start << ", end: " << end << "\n";
    	TreeNode* node = new TreeNode(preorder[preIndex++]);

    	if (start == end)
    		return node;

    	int inorderIndex = search(inorder, node -> val, start, end);
        // cout << "node: " << node -> val << " , inorderIndex: " << inorderIndex << "\n";
    	
        node -> left = buildTree(preorder, inorder, start, inorderIndex - 1, preIndex);
    	node -> right = buildTree(preorder, inorder, inorderIndex + 1, end, preIndex);
    
    	return node;
    }


    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        
        int preIndex = 0;
        return buildTree(preorder, inorder, 0, preorder.size() - 1, preIndex);
    }
};