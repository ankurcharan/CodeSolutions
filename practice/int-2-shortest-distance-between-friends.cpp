

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
	vector<int> path(n + 1);

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

vector<int> bfs(int n, vector<vector<pair<int, int>>>& g, int s) {

	vector<int> dist(n + 1, -1);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	pq.push({ 0, s });
	dist[s] = 0;

	while (!pq.empty()) {

		pair<int, int> f = pq.top();
		pq.pop();

		for (pair<int, int>& n: g[f.second]) {

			if (dist[n.first] == -1 || dist[n.first] > dist[f.second] + n.second) {
				dist[n.first] = dist[f.second] + n.second;
				pq.push({ dist[n.first], n.first });
			}
		}
	}

	return dist;
}

int findNearestNodeToK(int n, vector<vector<int>> edges, vector<int> kfriends) {

	// create graph
	vector<vector<pair<int, int>>> g(n + 1);
	for (vector<int>& e: edges) {

		g[e[0]].push_back({ e[1], e[2] });
		g[e[1]].push_back({ e[0], e[2] });
	}

	if (kfriends.size() == 0)
		return -1;

	unordered_set<int> friendSet;
	for (int& x: kfriends)
		friendSet.insert(x);


	// first bfs
	vector<int> dist = bfs(n, g, kfriends[0]);

	for (int i = 1 ; i <= n ; i++) {

		if (friendSet.find(i) != friendSet.end()) {

			// friend isn't reachable
			if (dist[i] == -1) {
				cout << "all friends not reachable\n";
				return -1;
			}
		}
	}

	for (int i = 1 ; i < kfriends.size() ; i++) {

		int x = kfriends[i];

		vector<int> distTemp = bfs(n, g, x);
		cout << "bfs: " << setw(2) << x << " --    "; 
		for (int i = 1 ; i <= n ; i++)
			cout << setw(2) << distTemp[i] << " ";
		cout << "\n";


		// calculate sum of distance
		for (int i = 1 ; i <= n ; i++) {
			dist[i] += distTemp[i];
		}
	}

	cout << "sum dist: " << " -- "; 
	for (int i = 1 ; i <= n ; i++)
		cout << setw(2) << dist[i] << " ";
	cout << "\n";

	// return min distance
	return *min_element(dist.begin() + 1, dist.end());
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


	vector<int> kfriends = { 1, 5 };
	int nearestNode = findNearestNodeToK(n, edges, kfriends);

	cout << "nearestNode min distance: " << nearestNode << endl;

	return 0;
}