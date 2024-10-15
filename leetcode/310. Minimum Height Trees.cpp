// 310. Minimum Height Trees
// https://leetcode.com/problems/minimum-height-trees/description/

class Solution {
public:
	void createGraphAndIndegree(int n, vector<vector<int>>& edges, vector<int>& inDegree, vector<int> g[]) {

		for (vector<int> edge: edges) {

			g[edge[0]].push_back(edge[1]);
			g[edge[1]].push_back(edge[0]);

			inDegree[edge[0]]++;
			inDegree[edge[1]]++;
		}
	}

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        
        if (edges.size() == 0)
            return { 0 };

        vector<int> g[n];
        vector<int> inDegree(n, 0);
        createGraphAndIndegree(n, edges, inDegree, g);
    
    	// use leaf nodes and come back in middle 
    	// to find the mid nodes
        queue<int> q;

        for (int i = 0 ; i < n ; i++) {

        	// leaf node
        	if (inDegree[i] == 1)
        		q.push(i);
        }

        int numberOfNodes = n;	// nodes in graph

        while (numberOfNodes > 2) {

        	int currSize = q.size();
        	numberOfNodes -= currSize;	// curr nodes in queue will be removed

        	for (int i = 0 ; i < currSize ; i++) {

        		int f = q.front();
        		q.pop();

        		for (int neighbor: g[f]) {

        			inDegree[neighbor]--;

        			if (inDegree[neighbor] == 1)
        				q.push(neighbor);
        		}
        	}
        }

        // the mid nodes will be either 1 or 2
        vector<int> ans;
        while (q.empty() == false) {
        	ans.push_back(q.front());
        	q.pop();
        }

        return ans;
    }
};