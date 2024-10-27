

/**


Round 1:
Question: 
	There are n friends living in different cities across a graph. 
	Find the shortest distance between two friends (e.g., A and B).

Solution: 
	Solved using BFS (Dijkstra's algorithm).

Follow-up: 
	Given k friends, 
	find the node where the total distance for all friends to reach is minimized.

Solution: 
	Solved by applying BFS from each friend and checking nodes that all k friends visit.

Feedback: Strong hire.

*/


#include <bits/stdc++.h>
using namespace std;

class cmp {
public:
	bool operator()(pair<int, int>& a, pair<int, int>& b) {

		return a.first > b.first;
	}
};

int findShortestDistance(int n, vector<vector<int>>& edges, int s, int d) {

	// n = no of nodes
	vector<vector<pair<int, int>>> g(n + 1);
	vector<vector<pair<int, int>>> path(n + 1);

	// create graph
	for (vector<int>& e: edges) {

		g[e[0]].push_back({ e[1], e[2] });
		g[e[1]].push_back({ e[0], e[2] });
	}

	// (wt, node)
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

	pq.push({ 0, s });

	vector<int> dist(n + 1, -1);
	dist[s] = 0;
	path[s] = s;

	while (!pq.empty()) {

		pair<int, int> f = pq.top();
		pq.pop();

		cout << "pop: " << f.second << " " << f.first << "\n";

		if (f.second == d) {
			cout << "found end\n";
			return f.first;
		}

		int u = f.second;

		for (pair<int, int> n: g[u]) {

			int v = n.first;
			int wt = n.second;

			if (dist[v] == -1 || dist[v] > dist[u] + wt) {
				dist[v] = dist[u] + wt;
				pq.push({ dist[v], v });
			}
		}
	}

	return -1;		// no path
}

int main() {
	
	vector<vector<int>> edges = {
		{ 1, 2, 16 },
		{ 2, 3, 2 },
		{ 1, 4, 3 },
		{ 3, 5, 4 },
		{ 4, 5, 5 }
	};
	int n = 5;

	// find shortest distance between two friends
	int shortestDist = findShortestDistance(n, edges, 1, 2);
	cout << "shortestDist 1-2: " << shortestDist << endl;

	return 0;
}