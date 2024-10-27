// https://leetcode.com/discuss/interview-question/2126784/google-phone-interview-collection-of-circles

// qlist-12-work-schedule


// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 1
////////////////////////////////////////////////////////////////////////////////////////////////////



/*
Google | Phone Interview | Collection of Circles

https://leetcode.com/discuss/interview-question/2126784/google-phone-interview-collection-of-circles



Problem: A circle is define by x-axis position, y-axis position, and a radius. 
A circle group is a collection of circles that overlap. 

Given a list of circles, figure out if they belong to a single circle group. 
Formula for calculating distance between two points: sqrt((x2-x1)^2 + (y2-y1)^2)

*/


/*

A circle is define by x-axis position, y-axis position, and a
radius. A circle group is a collection of circles that overlap. Given a
list of circles, figure out if they belong to a single circle group

*/

#include <bits/stdc++.h>
using namespace std;

bool inRange(vector<vector<int>>& circles, int i, int j) {

	int x = pow((circles[i][0] - circles[j][0]), 2);
	int y = pow((circles[i][1] - circles[j][1]), 2);

	int dist = sqrt(x + y);

	return (dist - circles[i][2] - circles[j][2]) <= 0;
}

int dfs(vector<int> g[], int s, vector<bool>& visit) {

	visit[s] = true;

	int nodes = 1;
	for (int v: g[s]) {

		if (visit[v] == false)
			nodes += dfs(g, v, visit);
	}

	return nodes;
}

bool belongToSameGroupDFS(vector<vector<int>>& circles) {

	// edges between circles
	vector<pair<int, int>> edges;

	int n = circles.size();
	if (n <= 1)	return true;

	vector<int> g[n];

	for (int i = 0 ; i < n ; i++) {
		for (int j = i + 1 ; j < n ; j++) {

			if (inRange(circles, i, j)) {

				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}

	vector<bool> visit(n, false);
	int visitedNodes = dfs(g, 0, visit);

	cout << "vistedNodes: " << visitedNodes << "\n";

	return visitedNodes == n;
}

int find(vector<int>& parent, int x) {
	if (parent[x] == x)
		return x;
	return parent[x] = find(parent, parent[parent[x]]);
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

bool belongToSameGroupDSU(vector<vector<int>>& circles) {

	int n = circles.size();
	if (n <= 1)	return true;

	vector<pair<int, int>> edges;

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < n ; j++) {

			if (inRange(circles, i, j)) {

				edges.push_back({ i, j });
			}
		}
	}

	vector<int> parent(n);
	vector<int> rank(n, 1);

	for (int i = 0 ; i < n ; i++)
		parent[i] = i;

	int vertex = 1;
	for (pair<int, int>& e: edges) {

		int u = e.first;
		int v = e.second;

		if (find(parent, u) != find(parent, v)) {

			unite(parent, rank, u, v);
			vertex++;
		}
	}

	return vertex == n;
}

int main() {

	// TC -1 
	vector<vector<int>> circles = {
		{ 0, 0, 1 },
		{ 0, 0, 2 },
		{ 24, 24, 1 },
		{ 25, 25, 2 },
		{ -36, 36, 2 }
	};

	// // TC-2
	// vector<vector<int>> circles = {
	// 	{ 0, 0, 1 },
	// 	{ 0, 1, 2 },
	// 	{ 0, 2, 1 },
	// 	{ 0, 3, 2 },
	// 	{ 0, 4, 2 }
	// };



	// bool ans = belongToSameGroupDFS(circles);
	// cout << "belong to same group: " << boolalpha << ans << endl;

	bool ans = belongToSameGroupDSU(circles);
	cout << "belong to same group: " << boolalpha << ans << endl;

	return 0;
}