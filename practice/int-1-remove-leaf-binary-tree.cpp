// https://leetcode.com/discuss/interview-question/2006734/google-onsite-l4-rejected



////////////////////////////////
// First Question
////////////////////////////////



// Given a binary tree, remove leafs and print sequence. 
// After I solved that recursively, interviewer asked about changing the order that the 
// leaves print (basically depth first with recursion/stack vs breadth first with a queue).

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
	int data;
	Node* left;
	Node* right;

	Node(int x) {
		data = x;
		left = right = NULL;
	}
};

Node* dfs(Node* root) {

	if (root == NULL)
		return NULL;

	if (root -> left == NULL && root -> right == NULL) {
		cout << root -> data << " ";
		return NULL;
	} 
    
	root -> left = dfs(root -> left);
	root -> right = dfs(root -> right);

	return root;
}


Node* printLeavesRecursivelyDFS(Node *root) {

	while (root) {
		root = dfs(root);
        cout << "\n";
	}
    return root;
}


void printLeavesBFS(Node* root) {
    
    if (root == NULL)
        return;
    
    int cn = 0;
    while (root) {
        
        if (root -> left == NULL && root -> right == NULL) {
            cout << root -> data << " ";
            root = NULL;
            break;
        }
            
        
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {

            Node* f = q.front();
            q.pop();

            if (f -> left) {
                
                if (f -> left -> left == NULL && f -> left -> right == NULL) {
                    cout << f-> left -> data << " ";
                    f -> left = NULL;
                }
                else 
                    q.push(f -> left);
            }
            
            if (f -> right) {
                
                if (f -> right -> left == NULL && f-> right -> right== NULL) {
                    cout << f -> right -> data << " ";
                    f -> right = NULL;
                } 
                else 
                    q.push(f -> right);
            }
        }
        
        cout << "\n";
    }
}


int fillMapDFS(Node* root, unordered_map<int, vector<Node*>>& nodesAtDepth) {

	if (root == NULL) 
		return 0;

	int l = fillMapDFS(root -> left, nodesAtDepth);
	int r = fillMapDFS(root -> right, nodesAtDepth);

	int depth = max(l, r) + 1;
	nodesAtDepth[depth].push_back(root);
	return depth;
}

void printLeavesOptimized(Node* root) {

	if (root == NULL)
		return;

	unordered_map<int, vector<Node*>> nodesAtDepth;

	int maxDepth = fillMapDFS(root, nodesAtDepth);

	for (int i = 1 ; i <= maxDepth ; i++) {

		for (auto x: nodesAtDepth[i]) {
			cout << x -> data << " ";
		}
		cout << "\n";
	}
}

int main() {

	Node *root = new Node(1);
    root -> left = new Node(2);
    root -> right = new Node(3);
    root -> left  -> left = new Node(4);
    root -> right -> left = new Node(5);
    root -> right -> right = new Node(8);
    root -> right -> left  -> left = new Node(6);
    root -> right -> left  -> right = new Node(7);
    root -> right -> right -> left = new Node(9);
    root -> right -> right -> right = new Node(10);

    // cout << "DFS\n";
    // root = printLeavesRecursivelyDFS(root);
    
    // cout << "BFS\n";
    printLeavesBFS(root);

    // cout << "optimized O(n)\n";
    // printLeavesOptimized(root);

	return 0;
}