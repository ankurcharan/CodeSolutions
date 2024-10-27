// shortest-path-with-restricted-nodes

// https://leetcode.com/discuss/interview-question/5920301/Google-New-Grad-2025-or-Interview-or-Tech-%2B-Googleyness

// questions 2


/**
 * 
 * 
Round 2: Tech(45min) + Googleyness(15min)
Similar to first round It started with the introduction and the we moved to the problem.


You are given a undirected unweighted graph, a start node and an end node. 
You need to find the shortest path from start to end node but there are some nodes which are 
restricted (L), that can not be part of your path.
example: edges =[{1,2}, {2,3}, {1,4}, {4,5}, {3,5}}, start = 1, end = 3, L ={2}


I asked some claryfying questions - does the path always exist?
This was very standard problem- used BFS and while visiting the adjNodes 
I checked if the adjNode is present in the restricted array.
He asked to optimize it a bit, so i said we'll store the restricted node in a vector. 
he told me to update the code accordigly.
Then I was asked Time and space complexities.


Follow Up
There is a special kind of pass to cross the restricted node, which is very costly. 
Assume there is no possible path from start to end which does not contain restricted nodes. 
Then find the minimum number of passes you will need to reach the end. there is no need to minimize the path length here.


I gave a dijkestra solution with no of restricted nodes as the first argument in the priority queue.
wrote the code and then discussed the time complexity.
He seem satisfied with both the codes.

*/

#include <bits/stdc++.h>
using namespace std;

int findShorttestPathWithoutRestricted(int n, vector<vector<int>>& edges, vector<int>& restricted, int start, int end) {

	// no path
	if (n == 0)	return -1;

	unordered_set<int> L;		// resricted
	for (int& x: restricted)
		L.insert(x);

	vector<vector<int>> g(n + 1);

	for (vector<int>& e: edges) {

		// add edge
		g[e[0]].push_back(e[1]);
		g[e[1]].push_back(e[0]);
	}

	vector<bool> visit(n + 1, false);

	// (node, dist)
	queue<pair<int, int>> q;

	visit[start] = true;
	q.push({ start, 0 });

	// bfs
	while (!q.empty()) {

		pair<int, int> f = q.front();
		q.pop();

		// found end node
		if (f.first == end)
			return f.second;

		for (int neigh: g[f.first]) {

			if (visit[neigh] == false && L.count(neigh) == 0) {

				visit[neigh] = true;
				q.push({ neigh, f.second + 1 });
			}
		}
	}

	return -1;		// no path
}


int minPassesFromRestrictedNodes01BFS(int n, vector<vector<int>>& edges, vector<int>& restricted, int start, int end) {

	// create graph and restricted nodes

	unordered_set<int> L;		// resricted
	for (int& x: restricted)
		L.insert(x);

	vector<vector<int>> g(n + 1);

	for (vector<int>& e: edges) {
		g[e[0]].push_back(e[1]);
		g[e[1]].push_back(e[0]);
	}

	// bfs 
	// (node, passes, moves)
    vector<bool> visit(n + 1, false);
	deque<pair<pair<int, int>, int>> q;
	q.push_back({ { start, 0 }, 0 });
    // visit[start] = true;

	while (!q.empty()) {

		pair<pair<int, int>, int> f = q.front();
		q.pop_front();

		// printing min passes
		cout << "pop: " << f.first.first << ", " << f.first.second << " :: " << f.second << endl;

		visit[f.first.first] = true;

		// return min number of passes from here
		if (f.first.first == end)
			return f.first.second;

		for (int neigh: g[f.first.first]) {
            
            if (visit[neigh])
                continue;

			if (L.find(neigh) != L.end()) {
				q.push_back({ { neigh, f.first.second + 1 }, f.second + 1 });
			}
			else
				q.push_front({ { neigh, f.first.second }, f.second + 1 });
		}
	}

	return -1;		// no path
}


class cmp {
public:
	bool operator()(pair<int, int>& a, pair<int, int>& b) {
		return a.first > b.first;
	}
};

int minPassesFromRestrictedNodesDjikstra(int n, vector<vector<int>>& edges, vector<int>& restricted, int start, int end) {

	unordered_set<int> L;		// resricted
	for (int& x: restricted)
		L.insert(x);

	vector<vector<int>> g(n + 1);

	for (vector<int>& e: edges) {
		g[e[0]].push_back(e[1]);
		g[e[1]].push_back(e[0]);
	}

	// djikstra starts

	vector<int> passes(n + 1, -1);

	// (noOfRestrictedNodes, node)
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

	pq.push({ 0, start });
	// passes[start] = 0;

	while (!pq.empty()) {

		pair<int, int> f = pq.top();
		pq.pop();

		cout << "pop: " << f.second << " = " << f.first << endl;

		passes[f.second] = f.first;

		if (f.second == end) {

			cout << "end found. minPasses ans: " << f.first << endl;
			// return f.first;
		}

		for (int neigh: g[f.second]) {

			if (passes[neigh] == -1) {

				passes[neigh] = passes[f.second];
				if (L.find(neigh) != L.end())
					passes[neigh]++;

				pq.push({ passes[neigh], neigh });
			}
		}
	}

	// just to print min passes to all the nodes
	for (int i = 1 ; i <= n ; i++)
		cout << setw(2) << i << " ";
	cout << endl;
	for (int i = 1 ; i <= n ; i++)
		cout << setw(2) << passes[i] << " ";
	cout << endl;

	return passes[end];		// no path
}


int main() {

	// int n = 5;		// no of nodes

	// vector<vector<int>> edges = {
	// 	{ 1, 2 },
	// 	{ 2, 3 },
	// 	{ 1, 4 },
	// 	{ 4, 5 },
	// 	{ 3, 5 }
	// };

	// vector<int> restricted = { 2 };

	// int start = 1;
	// int end = 3;

	// int shorttestPathWithoutRestricted = findShorttestPathWithoutRestricted(n, edges, restricted, start, end);
	// cout << "shorttestPathWithoutRestricted: " <<  shorttestPathWithoutRestricted << endl;






	// Follow Up
	// There is a special kind of pass to cross the restricted node, which is very costly. 
	// Assume there is no possible path from start to end which does not contain restricted nodes. 
	// Then find the minimum number of passes you will need to reach the end. there is no need to minimize the path length here.


	int n = 5;		// no of nodes

	vector<vector<int>> edges = {
		{ 1, 2 },
		{ 2, 3 },
		{ 1, 4 },
		// { 4, 5 },			// removing this make no path from 1-3
		{ 3, 5 }
	};

	vector<int> restricted = { 2 };

	int start = 1;
	int end = 3;

	int shorttestPathWithoutRestricted = findShorttestPathWithoutRestricted(n, edges, restricted, start, end);
	cout << "shorttestPathWithoutRestricted: " <<  shorttestPathWithoutRestricted << endl;

	// int minPasses = minPassesFromRestrictedNodesDjikstra(n, edges, restricted, start, end);
	// cout << "minPasses: " << minPasses << endl;

	int minPassesBFS = minPassesFromRestrictedNodes01BFS(n, edges, restricted, start, end);
	cout << "minPasses: " << minPassesBFS << endl;

	return 0;
}