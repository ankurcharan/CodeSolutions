// 1462. Course Schedule IV
// https://leetcode.com/problems/course-schedule-iv/description/

class Solution {

	vector<bool> kahnAlgorithm(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {

		vector<vector<int>> g(numCourses);

		vector<vector<bool>> visitingPossible(numCourses, vector<bool>(numCourses, false));

		vector<int> indegree(numCourses, 0);

		for (int i = 0 ; i < prerequisites.size() ; i++) {

			g[prerequisites[i][0]].push_back(prerequisites[i][1]);
			indegree[prerequisites[i][1]]++;
		}

		// queue for topo sort
		queue<int> q;

		// push leaf nodes of graph to queue
		for (int i = 0 ; i < numCourses ; i++) {

			if (indegree[i] == 0)
				q.push(i);
		}

		while (!q.empty()) {

			int curr = q.front();
			q.pop();

			// check for neighbor
			for (int neighbor: g[curr]) {

				// mark if visiting possible
                // since edge from curr -> neighbor
				visitingPossible[curr][neighbor] = true;

				for (int i = 0 ; i < numCourses ; i++) {

                    // if edge from "i -> curr" and "curr -> neighbor" exists
                    // so transitive edge "i -> neighbor"
                    if (visitingPossible[i][curr] == true)
						visitingPossible[i][neighbor] = true;
				}

				indegree[neighbor]--;

				if (indegree[neighbor] == 0)
					q.push(neighbor);
			}
		}

		// get the queuries answered
		vector<bool> ans;
		for (vector<int> q: queries) {
			ans.push_back(visitingPossible[q[0]][q[1]]);
		}

		return ans;
	}

public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        

        return kahnAlgorithm(numCourses, prerequisites, queries);
    }
};