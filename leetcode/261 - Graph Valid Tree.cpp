// 261 - Graph Valid Tree
// https://leetcode.com/problems/graph-valid-tree/


/*

You have a graph of n nodes labeled from 0 to n - 1. 
You are given an integer n and 
a list of edges where edges[i] = [ai, bi] indicates that 
there is an undirected edge between nodes ai and bi in the graph.

Return true if the edges of the given graph make up a valid tree, 
and false otherwise.
 
 */

// you have to detect cycle in the graph 
// another way here to use Disjoin-Set Union

#include<bits/stdc++.h>
using namespace std;

int find(vector<int>& parent, int x) {

	if (parent[x] != x)
		parent[x] = find(parent, parent[x]);
	return parent[x];
}

bool isValidTree(int n, vector<vector<int>> edges, int e) {

	// sets
	vector<int> parent(n);
	for (int i = 0 ; i < n ; i++)
		parent[i] = i;

	for (int i = 0 ; i < e ; i++) {

		// belong to same set
		// mean their is a cycle 
		// i.e. they are already connected through 
		// some other node
		if (find(parent, edges[i][0]) == find(parent, edges[i][1])) {

			// cycle detected
			return false;
		}

		parent[find(parent, edges[i][0])] = find(parent, edges[i][1]);
		n--;
	}

	return n == 1; 		// only one component is left
}

int main() {

	// no of nodes
	int n;
	cin >> n;

	// no of edges
	int e;
	cin >> e;

	// graph
	vector<vector<int>> edges;
	for (int i = 0 ; i < e ; i++) {

		// undirected edge between x and y
		int x, y;
		cin >> x >> y;
		vector<int> edge = { x, y };

		edges.push_back(edge);
	}	

	cout << boolalpha << isValidTree(n, edges, e) << "\n";

	return 0;
}
