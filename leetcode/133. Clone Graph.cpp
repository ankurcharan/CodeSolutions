// 133. Clone Graph
// https://leetcode.com/problems/clone-graph/description/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {

    	if (!node)
    		return NULL;
        
        unordered_map<Node*, Node*> newNodes;

        stack<Node*> s;
        s.push(node);
        newNodes[node] = new Node(node -> val);

        while (!s.empty()) {

        	Node* f = s.top();
        	s.pop();

        	for (Node* neighbor: f -> neighbors) {

                if (newNodes.find(neighbor) == newNodes.end()) {

                    newNodes[neighbor] = new Node(neighbor -> val);   
                    s.push(neighbor);
                }

                newNodes[f] -> neighbors.push_back(newNodes[neighbor]);
        	}
        }

        // for (auto it: newNodes) {
        //     cout << it.first << " " << it.second << "\n";
        //     cout << it.first->val << " " << it.second->val << "\n";
        // }

        return newNodes[node];
    }
};