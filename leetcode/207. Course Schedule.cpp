// 207. Course Schedule
// https://leetcode.com/problems/course-schedule/description/

class Solution {
public:
	bool dfsCycle(vector<int> g[], int curr, vector<bool>& onPath, vector<bool>& visited) {

        // cout << "curr: " << curr << "\n";

		if (visited[curr])		// already visited
			return false;		// cycle not detected - visited nodes can be ignored

		// mark as visited and on path
		visited[curr] = true;
		onPath[curr] = true;

		for (int neighbour: g[curr]) {

            // cout << "curr: " <<  curr << " -> neighbour: " << neighbour << "\n";
            // cout << "onPath: " << boolalpha << onPath[neighbour] << " , visited: " << visited[neighbour] << "\n";

			// if curr node is on path
			// or cycle detected 
			if (onPath[neighbour] || dfsCycle(g, neighbour, onPath, visited)) {

                // cout << curr << "returning true\n";
                return true;
            }
				
		}

		// mark as not on path and cycle not detected
        // cout << curr << "returning false\n";
		onPath[curr] = false;
        return false;
	}

	bool detectCycleDFS(vector<int> g[], int n) {

		vector<bool> onPath(n, false);
		vector<bool> visited(n, false);

		for (int i = 0 ; i < n ; i++) {

			if (!visited[i] && dfsCycle(g, i, onPath, visited)) {
                
                // cout << "loop i: " << i << " true\n";
                return true;
            }
            // else {
            //     cout << "loop i: " << i << " false\n";
            // }
		}

		return false;
	}

	bool topoSortPossibility(vector<int> g[], int n) {

		vector<int> inDegree(n, 0);

		// get indegree
		for (int i = 0 ; i < n ; i++) {
			for(int neighbour: g[i]) {
				inDegree[neighbour]++;
			}
		}

		// push zero indegree as starting node in queue
		queue<int> q;
		for (int i = 0 ; i < n ; i++) {
			if (inDegree[i] == 0)
				q.push(i);
		}

		// do topo sort
		while (!q.empty()) {

			int node = q.front();
			q.pop();

			for (int neighbour: g[node]) {
				inDegree[neighbour]--;

				if (inDegree[neighbour] == 0)
					q.push(neighbour);
			}
		}

		// all nodes must be visited
		// i.e. their indegree should be zero 
		for (int i = 0 ; i < n ; i++) {
			if (inDegree[i] != 0)
				return false;		// cannot be topo sorted
		}

		return true;		// can be topo sorted
	}

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        vector<int> g[numCourses];

        // create graph
        int prerequisitesSize = prerequisites.size();
        for (int i = 0 ; i < prerequisitesSize ; i++) {
        	g[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        // // detect cycle using DFS
        // return detectCycleDFS(g, numCourses) == false;
    
        // // detect cycle using topoSort
        return topoSortPossibility(g, numCourses);
    }
};