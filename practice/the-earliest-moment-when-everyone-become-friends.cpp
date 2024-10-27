// https://leetcode.com/discuss/interview-question/4845526/Google-Interview-Question
// the-earliest-moment-when-everyone-become-friends


/*

Initial Question:
https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/description/


Follow-up:
Two types of logs


Add Friend - A and B become friends
Remove Friend - If A and B are friends, unfriend them
Two people can be connected and disconnected multiple times.


Given this, find the earliest timestamp when all of them become friends

*/


/*
Leetcode CA

In a social group, there are N people, with unique integer ids from 0 to N-1.

We have a list of logs, where each logs[i] = [timestamp, id_A, id_B] contains a 
non-negative integer timestamp, and the ids of two different people.

Each log represents the time in which two different people became friends.  
Friendship is symmetric: if A is friends with B, then B is friends with A.

Let's say that person A is acquainted with person B if A is friends with B, 
or A is a friend of someone acquainted with B.

Return the earliest time for which every person became acquainted 
with every other person. 

Return -1 if there is no such earliest time.






test case:

Input: logs = [
	[20190101,0,1], [20190104,3,4], [20190107,2,3], [20190211,1,5], [20190224,2,4],
	[20190301,0,3], [20190312,1,2], [20190322,4,5]
],
N = 6

Output: 20190301



*/

#include <bits/stdc++.h>
using namespace std;

int find(vector<int>& parent, int u) {

	if (parent[u] == u)
		return u;

	return parent[u] = find(parent, parent[u]);
}

void unite(vector<int>& parent, vector<int>& rank, int u, int v) {

	int up = find(parent, u);
	int vp = find(parent, v);

	if (up == vp)
		return;

	if (rank[up] < rank[vp]) {
		parent[up] = vp;
		rank[vp] += rank[up];
	}
	else {
		parent[vp] = up;
		rank[up] += rank[vp];
	}
}

int earliestTimestampWhenEveryoneIsFriends(int n, vector<vector<int>>& logs) {

	vector<int> parent(n);
	vector<int> rank(n, 1);

	for (int i = 0 ; i < n ; i++)
		parent[i] = i;

	int ls = logs.size();

	int vertexCount = 1;
	for (int i = 0 ; i < ls ; i++) {

		int u = logs[i][1];
		int v = logs[i][2];

		if (find(parent, u) != find(parent, v)) {

			unite(parent, rank, u, v);
			vertexCount++;

			if (vertexCount == n) {
				return logs[i][0];
			}
		}
	}

	return -1;
}

// normal = 0    -- ad given
// normal = 1 	 -- undo op
void processEdge(vector<int> edge, unordered_map<int, vector<int>>& g, int normal) {

	int u = edge[1];
	int v = edge[2];

	// add
	if ((edge[3] == 0 && normal == 0) || (edge[3] == 1 && normal == 1)) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	else {

		// delete existing edge
		vector<int>::iterator it = find(g[u].begin(), g[u].end(), v);
		if (it != g[u].end()) {
			g[u].erase(it);
			g[v].erase(find(g[v].begin(), g[v].end(), u));
		}
	}
}

int dfs(unordered_map<int, vector<int>>& g, int n, vector<bool>& visited) {

	visited[n] = true;

	int nodes = 1;

	for (int v: g[n]) {
		if (visited[v] == false) {
			nodes += dfs(g, v, visited);
		}
	}

	return nodes;
}

int earliestTimestampWhenEveryoneIsFriendsBreakingEdges(int n, vector<vector<int>>& logs) {

	int ls = logs.size();

	if (n <= 1)		return 0;
	if (ls == 0)	return -1;


	int l = 0;
	int r = ls - 1;

	int mid = (l + r) / 2;

	cout << "init mid: " << mid << endl;

	unordered_map<int, vector<int>> g;
	for (int i = 0 ; i <= mid ; i++) {
		processEdge(logs[i], g, 0);
	}

	int earliestTimestanpAns = -1;
	while (l <= r) {

		int mid = (l + r) / 2;

		vector<bool> visited(n, false);

		int nodesVisited = dfs(g, 0, visited);

		visited.clear();

		if (nodesVisited == n) {

			earliestTimestanpAns = logs[mid][0];

			cout << "nodes visited\n";
			// remove edges and move to left
			r = mid - 1;
			for (int e = r ; e >= mid ; e--) {
				processEdge(logs[e], g, 1);
			}
		}
		else {
			cout << "nodes not visited\n";
		
			l = mid + 1;
			int newMid = (l + r) / 2;

			cout << "new l: " <<  l << ", r: " << r << ", mid: " << newMid << endl;

			cout << "process: ";
			for (int e = l ; e <= r ; e++) {
				cout << e << " ";
				processEdge(logs[e], g, 0);
			}
			cout << endl;
		}

	}

	return earliestTimestanpAns;
}

int main() {

	// int n = 6;
	// vector<vector<int>> logs = { 
	// 	{ 20190101, 0, 1 }, { 20190104, 3, 4 }, { 20190107, 2, 3 }, { 20190211, 1, 5 }, 
	// 	{ 20190224, 2, 4 }, { 20190301, 0, 3 }, { 20190312, 1, 2 }, { 20190322, 4, 5 }
	// };

	// int ans = earliestTimestampWhenEveryoneIsFriends(n, logs);
	// cout << "earliestTimestampWhenEveryoneIsFriends: " << ans << endl;

	// // follow up, when relationships can break
	int n = 4;

	// (time, u, v, add/remove)
	// add = 0
	// remove = 1
	vector<vector<int>> logs = { 
		{ 0, 0, 1, 0 }, { 1, 2, 3, 0 }, { 2, 1, 2, 0 } 
		// { 20190312, 1, 2 }, { 20190322, 4, 5 }
	};

	int ans = earliestTimestampWhenEveryoneIsFriendsBreakingEdges(n, logs);
	cout << "earliestTimestampWhenEveryoneIsFriendsBreakingEdges: " << ans << endl;

	return 0;
}

