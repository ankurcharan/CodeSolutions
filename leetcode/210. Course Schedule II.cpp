// 210. Course Schedule II
// https://leetcode.com/problems/course-schedule-ii/description/

class Solution {
public:
	bool dfs(vector<int> g[], int curr, int n, vector<bool>& visited, vector<int>& topoOrder, vector<bool>& onPath) {

		visited[curr] = true;
        onPath[curr] = true;

		for (int neighbor: g[curr]) {

            if (onPath[neighbor] == true)
                return false;

			if (visited[neighbor] == false)
				if (dfs(g, neighbor, n, visited, topoOrder, onPath) == false)
                    return false;
		}

		topoOrder.push_back(curr);
        onPath[curr] = false;
        return true;
	}

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
        vector<int> g[numCourses];

        for (vector<int> edge: prerequisites) {
        	g[edge[0]].push_back(edge[1]);
        }

        vector<bool> visited(numCourses, false);
        vector<bool> onPath(numCourses, false);

        vector<int> topoOrder;
        for (int i = 0 ; i < numCourses ; i++) {
        	if (visited[i] == false) {
                if (dfs(g, i, numCourses, visited, topoOrder, onPath) == false)
                    return {};
            }
		        
        }
    
        return topoOrder;
    }
};