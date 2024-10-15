// 102. Binary Tree Level Order Traversal
// https://leetcode.com/problems/binary-tree-level-order-traversal/description/

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
    vector<vector<int>> levelOrder(TreeNode* root) {
  		
  		vector<vector<int>> levels;

        if (root == NULL)
            return levels;

  		queue<TreeNode*> q;
  		q.push(root);

  		while (!q.empty()) {

  			int size = q.size();
  			vector<int> currLevel;

  			for (int i = 0 ; i < size ; i++) {

  				TreeNode* f = q.front();
  				q.pop();

  				currLevel.push_back(f -> val);

  				if (f -> left)
  					q.push(f -> left);
  				if (f -> right)
  					q.push(f -> right);
  			}

            levels.push_back(currLevel);
  		}

  		return levels;    
    }
};