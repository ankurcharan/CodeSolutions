// 2101. Detonate the Maximum Bombs
// https://leetcode.com/problems/detonate-the-maximum-bombs/description/

class Solution {

	bool inRange(vector<int>& a, vector<int>& b) {

        // dist = sqrt ( (x2-x1)^2 + (y2-y1)^2 )
        // dist^2 = (x2-x1)^2 + (y2-y1)^2
		long long int dist = pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2);
        long long int radius = a[2];
        bool ans = dist <= (radius * radius);
        return ans;
	}

public:
	int dfs(vector<int> g[], int i, vector<bool>& visited) {

		visited[i] = true;

		int nodes = 1;

		for (int n: g[i]) {

			if (visited[n] == false) {
				nodes += dfs(g, n, visited);
			}
		}

		return nodes;
	}

	int getMaxComponentSizeDFS(vector<int> g[], int n) {

		int maxComponentSize = 0;

		for (int i = 0 ; i < n ; i++) {

            vector<bool> visited(n, false);
            maxComponentSize = max(maxComponentSize, dfs(g, i, visited));
		}

		return maxComponentSize;
	}

	int find(vector<int>& parent, int u) {
		
		if (parent[u] != u)
			parent[u] = find(parent, parent[parent[u]]);

		return parent[u]; 
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

	int getMaxComponentSizeDSU(vector<int> g[], int n) {

		vector<int> parent(n);
		vector<int> rank(n, 1);

		for (int i = 0 ; i < n ; i++)
			parent[i] = i;

		for (int i = 0 ; i < n ; i++) {
			int u = i;
			for (int v: g[u]) {

				if (find(parent, u) != find(parent, v)) {

					unite(parent, rank, u, v);
				}
			}
		}

		cout << "parent: ";
		for (int i = 0 ; i < n ; i++)
			cout << parent[i] << " ";
		cout << "\n";

		cout << "rank  : ";
		for (int i = 0 ; i < n ; i++)
			cout << rank[i] << " ";
		cout << "\n";

        // max compoent size would be the max element of rank 
		return *max_element(rank.begin(), rank.end());
	}

    int maximumDetonation(vector<vector<int>>& bombs) {
        
        int n = bombs.size();

        vector<int> g[n];

        for (int i = 0 ; i < n ; i++) {
        	for (int j = 0 ; j < n ; j++) {

                if (i == j)
                    continue;

        		if (inRange(bombs[i], bombs[j])) {
        			g[i].push_back(j);
        			// g[j].push_back(i);
        		}
        	}
        }

        // if (n >= 12) {
        //     cout << 7 << " - " << bombs[7][0] << ", " << bombs[7][1] << " = " << bombs[7][2] << "\n";
        //     cout << 12 << " - " << bombs[12][0] << ", " << bombs[12][1] << " = " << bombs[12][2] << "\n";
        // }

        // // print graph
        for (int i = 0 ; i < n ; i++) {

        	cout << i << " -- ";
        	for (int x: g[i]) {
        		cout << x << " ";
        	}
        	cout << "\n";
        }

        // count number of components
        int maxComponentSize = getMaxComponentSizeDFS(g, n);
        // cout << "maxComponentSize DFS: " << maxComponentSize << "\n";

        // // DSU won't work, because directed edge
        // int maxComponentSize = getMaxComponentSizeDSU(g, n);
        // cout << "maxComponentSize DSU: " << maxComponentSize << "\n";


        return maxComponentSize;
    }
};
