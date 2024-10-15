// 662. Maximum Width of Binary Tree
// https://leetcode.com/problems/maximum-width-of-binary-tree/description/

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
    int widthOfBinaryTree(TreeNode* root) {
        
        if (root == NULL)
        	return 0;

        queue<pair<TreeNode*, unsigned long long int>> q;
        q.push({ root, 0 });

        int ans = 0;

        while (!q.empty()) {

        	int s = q.size();

        	int start = -1;
        	int end = -1;
        	for (int i = 0 ; i < s ; i++) {

        		pair<TreeNode*, unsigned long long int> f = q.front();
        		q.pop();

        		if (i == 0)		start = f.second;
        		if (i == s - 1)	end = f.second;

        		if (f.first -> left)
        			q.push({ f.first -> left, 2 * f.second + 1 });
        		if (f.first -> right)
        			q.push({ f.first -> right, 2 * f.second + 2 });
        	}

        	ans = max(ans, end - start + 1);
        }

        return ans;
    }
};