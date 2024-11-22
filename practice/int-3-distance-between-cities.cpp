// int-3-distance-between-cities
// https://leetcode.com/discuss/interview-experience/5720580/Google-or-SDE(L3)-or-BangaloreHyd-or-Aug-24/

/**


Round 1- 
	Given are N cities and M roads that travel between the given pair of cities 
	and time it takes to travel that road. 
	Also we are given a list of favourite cities L and a source city S . 

	we have to tell the favourite city which can be reached from source city the fastest (in minimum time)


Solution- 
	Classic Dijkshtra

It was followed by a discussion on runtime complexity and how it was O(V+E log(V))
This went on for a while, since we had a little argument about the complexity of the inner loop.


Then a couple of follow ups -
	1) Early Stoppage conditions
	2) a fix vertex V to be travelled in the way to favourite city
	
	for 
	1) i got a little confused and had to take a little help from the interviewer 
		but eventually i told the right solution.
	2) i made a wrapper function which calls dijkshtra to find 
		dist S-V + dijkshtra to find V- C( favourite city)

*/


#include <bits/stdc++.h>
using namespace std;

vector<int> djikstra(int n, unordered_map<int, vector<pair<int, int>>>& g, int src, unordered_set<int> favourites) {

	vector<int> dist(n, INT_MAX);


	int vertexes = 0;

	// (time, dest)
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, src });
	dist[src] = 0;

	while (!pq.empty()) {

		pair<int, int> f = pq.top();
		pq.pop();

		int u = f.second;
		int t = f.first;

		if (favourites.count(u)) {
			vertexes++;
			if (vertexes == favourites.size())
				return dist;
		}

        // cout << "pop: " << u << " in " << t << endl;
        
		for (pair<int, int>& n: g[u]) {

			int v = n.first;
			int wt = n.second;
            
            // cout << "prcoess: " << v << " " << wt << endl;

			if (dist[u] != -1 && dist[u] + wt < dist[v]) {
				dist[v] = dist[u] + wt;
				pq.push({ dist[v], v });
			}
		}
	}

	return dist;
}

int getFastestCity(int n, vector<vector<int>> edges, int src, vector<int>& favCities) {

	// src -> (dest, time)
	unordered_map<int, vector<pair<int, int>>> g;
	for (vector<int> e: edges) {

		g[e[0]].push_back({ e[1], e[2] });
		g[e[1]].push_back({ e[0], e[2] });
	}

	// set of cities
	unordered_set<int> favourites;
    for (int& x: favCities) {
        favourites.insert(x);
    }

	// djikstra
	vector<int> distances = djikstra(n, g, src, favourites);
    
    int ansMinDistance = INT_MAX;
    
    cout << "\n\ndistances: ";
	for (int i = 0 ; i < n ; i++) {
		
        int d = distances[i];
        cout << d << "";
        
        if (favourites.find(i) != favourites.end()) {
            
            cout << "t";
            ansMinDistance = min(ansMinDistance, d);
        }
        
        // cout << " ";
	}
	cout << endl;

	return ansMinDistance;
}

int getFastestCityWithFixedVertex(int n, vector<vector<int>> edges, int src, int fixedVertex, 
	unordered_set<int>& favourites) {

	// src -> (dest, time)
	unordered_map<int, vector<pair<int, int>>> g;
	for (vector<int> e: edges) {

		g[e[0]].push_back({ e[1], e[2] });
		g[e[1]].push_back({ e[0], e[2] });
	}

	// s -> v
	// djikstra
	vector<int> distances = djikstra(n, g, src, { fixedVertex });

	int srcToFixedVertex = distances[fixedVertex];

	vector<int> distancesVertexToFavs = djikstra(n, g, fixedVertex, favourites);

    int ansMinDistance = INT_MAX;

	// cout << "\n\ndistances: ";
	for (int i = 0 ; i < n ; i++) {
		
        int d = distancesVertexToFavs[i];
        // cout << d << "";
        
        if (favourites.find(i) != favourites.end()) {
            
            // cout << "t";
            ansMinDistance = min(ansMinDistance, d);
        }
        
        // cout << " ";
	}
	// cout << endl;

	return srcToFixedVertex + ansMinDistance;
}

int main() {
	
	// 4 vertices
	int n = 4;

	// [src, dest, time]
	vector<vector<int>> edges = {
		{ 0, 1, 3 },
		{ 1, 2, 4 },
		{ 0, 3, 5 },
		{ 2, 3, 1 }
	};
    // vector<int> favCities = { 1, 2 };
	int src = 0;

	// int fastestCity = getFastestCity(n, edges, src, favCities);
	// cout << "fastestCity from: " << src << " is " << fastestCity << "\n";


	// set of cities
    vector<int> favCities = { 1, 3 };
	unordered_set<int> favourites;
    for (int& x: favCities) {
        favourites.insert(x);
    }

	int fixedVertex = 2;

	int distanceWithFixedV = getFastestCityWithFixedVertex(n, edges, src, fixedVertex, favourites);
	cout << "getFastestCityWithFixedVertex: " << src << " is " << distanceWithFixedV << "\n";

	return 0;
}