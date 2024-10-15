// 2050. Parallel Courses III
// https://leetcode.com/problems/parallel-courses-iii/description/

class Solution {
public:    
    int dfs(int u, vector<int>& distance, vector<vector<int>>& g, vector<int>& time) {

    	if (distance[u] != 0)
    		return distance[u];

    	int maxDist = 0;
    	for (int v: g[u])
    		maxDist = max(maxDist, dfs(v, distance, g, time));
    	
    	return distance[u] = maxDist + time[u];
    }

    int topoDFS(int n, vector<vector<int>>& relations, vector<int>& time) {

    	vector<vector<int>> g(n);
    	vector<int> distance(n, 0);

    	for (vector<int> e: relations) {
    		g[e[0] - 1].push_back(e[1] - 1);
    	}

    	for (int i = 0 ; i < n ; i++) {
    		dfs(i, distance, g, time);
    	}

    	return *max_element(distance.begin(), distance.end());
    }
    

      int topoBFS(int n, vector<vector<int>>& relations, vector<int>& time) {

    	vector<vector<int>> g(n);
    	vector<int> indegree(n, 0);
    	vector<int> distance(n, 0);

    	for (vector<int>& e: relations) {

    		g[e[0] - 1].push_back(e[1] - 1);
    		indegree[e[1] - 1]++;
    	}

    	queue<int> q;

    	for (int i = 0 ; i < n ; i++) {
    		if (indegree[i] == 0) {
    			distance[i] = time[i];
    			q.push(i);
    		}
    	}

    	while (q.empty() == false) {

    		int f = q.front();
    		q.pop();

    		for (int neighbor: g[f]) {

    			distance[neighbor] = max(distance[neighbor], distance[f] + time[neighbor]);
    			indegree[neighbor]--;

    			if (indegree[neighbor] == 0) {
    				q.push(neighbor);
    			}
    		}
    	}

    	return *max_element(distance.begin(), distance.end());
    }


    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        
        // return topoBFS(n, relations, time);
    
    	return topoDFS(n, relations, time);
    }
};