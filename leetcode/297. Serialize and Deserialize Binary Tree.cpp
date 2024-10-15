// 297. Serialize and Deserialize Binary Tree
// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {

	vector<string> getValues(TreeNode* root) {

		vector<string> values;

		queue<TreeNode*> q;
		q.push(root);

		while (!q.empty()) {

			TreeNode* f = q.front();
			q.pop();

			if (f == NULL) {
				values.push_back("null");
				continue;
			}

			values.push_back(to_string(f -> val));

			q.push(f -> left);
			q.push(f -> right);
		}

		return values;
	}

    TreeNode* createTree(vector<string> &values) {
        
        int n = values.size();

        if (n == 0 || (n == 1 && values[0].compare("null") == 0))
        	return NULL;

        int i = 0;
        TreeNode* root = new TreeNode(stoi(values[i++]));

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {

        	TreeNode* f = q.front();
        	q.pop();

            // cout << "pop:  " <<  f-> val << "\n";

        	// if (i < n && values[i].compare("null") != 0) {
        	// 	f -> left = new TreeNode(stoi(values[i++]));
        	// 	q.push(f -> left);
        	// }
        	// else 
        	// 	i++;

        	// if (i < n && values[i].compare("null") != 0) {
        	// 	f -> right = new TreeNode(stoi(values[i++]));
            //     q.push(f -> right);
        	// }
        	// else
        	// 	i++;

            for (int j = 0 ; j < 2 && i < n ; i++, j++) {

                if (values[i] != "null") {

                    TreeNode* child = new TreeNode(stoi(values[i]));

                    if (j == 0)
                        f -> left = child;
                    else
                        f -> right = child;
                    
                    q.push(child);
                }
            }
        }

        return root;
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        
        vector<string> values = getValues(root);

        string ans = "";
        for (int i = 0 ; i < values.size() ; i++) {

        	ans += values[i];
        	ans += (i == values.size() - 1) ? "" : ",";
        }

        // cout << "serialized: " << ans << "\n";
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {

        vector<string> values;
        string token;

        stringstream ss(data);

        while (getline(ss, token, ',')) {
            values.push_back(token);
            // cout << "t:" << token << ":\n";
        }

        TreeNode* root = createTree(values);

        return root;
        // return NULL;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));