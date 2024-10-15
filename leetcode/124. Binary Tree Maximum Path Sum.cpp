// 124. Binary Tree Maximum Path Sum
// https://leetcode.com/problems/binary-tree-maximum-path-sum/description/

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
	// (sum = max(left/right) + node, sum = left + node + right)
	pair<int, int> recursiveDFS(TreeNode* root, int &ans) {

		if (root == NULL)
			return { 0, 0 };

		pair<int, int> left  = recursiveDFS(root -> left, ans);
		pair<int, int> right = recursiveDFS(root -> right, ans);

		int thisNode = max(max(left.first, right.first) + root -> val, root -> val);

		int maxToFromThisNode = max(thisNode, left.first + right.first + root -> val);
	
        // cout << (root -> val) << " -> " << thisNode << ", " << maxToFromThisNode << "\n";

        ans = max(ans, maxToFromThisNode);

		return { thisNode, maxToFromThisNode };
	}

	int iterativeBFS(TreeNode* root, int &ans) {

		ans = INT_MIN;

		stack<pair<TreeNode*, int>> s;
		s.push({ root, 0 });

		while (!s.empty()) {

			pair<TreeNode* , int> f = s.top();
			s.pop();

			if (f.first == NULL)
				continue;

			// first visit
			if (f.second == 0) {
				s.push({ f.first, 1 });
				s.push({ f.first -> left, 0 });
			}
			// second visit
			else if (f.second == 1) {
				s.push({ f.first, 2 });
				s.push({ f.first -> right, 0 });
			}
			// this visit
			else {

                // cout << "visit: " << setw(3) << f.first -> val << " - " << f.second << "\n";

				int left = (f.first -> left) ? f.first -> left -> val : 0;
				int right = (f.first -> right) ? f.first -> right -> val : 0;

                ans = max(ans, left + f.first -> val + right);

                int maxChildSum = max(left, right);
				f.first -> val += max(0, maxChildSum);

                ans = max(ans, f.first -> val);

				// ans = max(ans, max(0, left) + f.first -> val + max(0, right));
                // cout << setw(3) << f.first -> val << " , ans: " << setw(3) << ans << "  , modified: ";
				
                // cout << setw(3) << f.first -> val << "\n";
			}
		}

		return ans;
	}

    int maxPathSum(TreeNode* root) {
        
        int ans = INT_MIN;
        // recursiveDFS(root, ans);

        iterativeBFS(root, ans);

        return ans;
    }
};