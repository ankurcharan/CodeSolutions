// int-3-max-path-dist-to-any-node
// https://leetcode.com/discuss/interview-experience/5720580/Google-or-SDE(L3)-or-BangaloreHyd-or-Aug-24/

/**

Part 2- 
	given a DAG , find the maximum path distance it can go upto any node
	It means from any node to any other node, what is the max distance
	
	// can graph have no nodes- NO
	had just 10 mins for it. was able to do it in O(n)time and O(n)space
	
	dist(i)= maximum dist we can travel to any other node from ith node
		= 1 + maximum(dist(c)) 				//c is any node directly reachable from ith node




int dist(int node, vector<vector<int>>&graph,vector<int> &distances)
{
	int ans = 1;
	for(auto x: graph[node])
		ans = max(ans, dist(x, graph, distance) + 1);
	
	return distances[node] = ans;
}


int func(vector<vector<int>> graph)
{
	vector<int> distances(graph.size(), -1);
	
	int ans;
	for(int i = 0 ; i < graph.size() ; i++)
	{
		if(distances[i] == -1)
			ans = max(dist(i, graph, distances) - 1, ans);
	}
	return ans;
}

in the end , interviewer was happy.


*/


#include <bits/stdc++.h>
using namespace std;

int distb(int node, vector<vector<int>>& graph, vector<int>& distances)
{
	int ans = 1;
	for(auto x: graph[node])
		ans = max(ans, distb(x, graph, distances) + 1);
	
	return distances[node] = ans;
}


int maxDistanceNode(vector<vector<int>> graph)
{
	vector<int> distances(graph.size(), -1);
	
	int ans = 0;
	for(int i = 0 ; i < graph.size() ; i++)
	{
		if(distances[i] == -1) {
            
            cout << "start: " << i << endl;
            ans = max(ans, distb(i, graph, distances) - 1);
        }
	}
	return ans;
}

int floydWarshall(vector<vector<int>>& g) {

	int n = g.size();

	vector<vector<int>> matrix(n, vector<int>(n, INT_MAX));

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < g[i].size() ; j++) {
			matrix[i][g[i][j]] = 1;
		}
	}

	// for (int i = 0 ; i < n ; i++) {
	// 	for (int j = 0 ; j < n ; j++) {
	// 		if (matrix[i][j] == INT_MAX)
	// 			cout << -1 << " ";
	// 		else
	// 			cout << setw(2) << matrix[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }
	// cout << "\n";
	// cout << "\n";

	int ans = INT_MIN;
	for (int k = 0 ; k < n ; k++) {

		for (int i = 0 ; i < n ; i++) {
			for (int j = 0 ; j < n ; j++) {

				if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX 
					&& matrix[i][j] > matrix[i][k] + matrix[k][j]) {

					matrix[i][j] = matrix[i][k] + matrix[k][j];

					ans = max(ans, matrix[i][j]);
				}
			}
		}
	}


	// cout << "sol\n\n";
	// for (int i = 0 ; i < n ; i++) {
	// 	for (int j = 0 ; j < n ; j++) {
	// 		if (matrix[i][j] == INT_MAX)
	// 			cout << setw(2) << 0 << " ";
	// 		else
	// 			cout << setw(2) << matrix[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }

	return ans;
}


int main() {
	
	vector<vector<int>> g = {

		{ 1, 7 },		// 0 
		{ 2 },			// 1
		{ 3 },			// 2
		{ 4 },			// 3
		{ 5 },			// 4
		{ 6 },			// 5
		{ },			// 6
		{ 8 },			// 7
		{ 9 },			// 8
		{ },			// 9
	};

	int ans = maxDistanceNode(g);
	cout << "ans: " <<  ans << endl;

	int ansFW = floydWarshall(g);
	cout << "ansFW: " << ansFW << endl;

	return 0;
}