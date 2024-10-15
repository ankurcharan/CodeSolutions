// 1136. Parallel Courses
// https://leetcode.com/problems/parallel-courses

// que: https://leetcode.ca/all/1136.html
// sol: https://leetcode.ca/2019-01-09-1136-Parallel-Courses/

class Solution {
public:
	int minimumSemesters(int n, vector<vector<int>>& relations) {
    
 		// relations are given from 1 to n 
 		// so substract 1 to get node index

 		vector<int> g[n];	// graph

 		vector<int> indegree(n, 0);
 		for (vector<int> r: relations) {

 			g[r[0] - 1].push_back(r[1] - 1);
 			indegree[r[1] - 1]++;
 		}

 		// start topo
 		queue<int> q;

 		for (int i = 0 ; i < n ; i++) {
 			if (indegree[i] == 0) {
                q.push(i);
            }
 		}

 		// level order topo 
 		
 		int nodesProcessed = n;
 		int semesters = 0;
 		while (!q.empty()) {

 			int s = q.size();
            semesters++;

 			while (s--) {

 				int f = q.front();
 				q.pop();
 				nodesProcessed--;

 				for (int neighbor: g[f]) {

 					indegree[neighbor]--;
 					if (indegree[neighbor] == 0)
 						q.push(neighbor);
 				}
 			}
 		}

 		return nodesProcessed == 0 ? semesters : -1;
    }
};

int main() {

	Solution s;
	int n;
	vector<vector<int>> relations;

	// tc-1
	n = 3;
	relations = {
		{ 1, 3 },
		{ 2, 3 } 
	};

	cout << s.minimumSemesters(n, relations) << "\n";

	// tc-2
	n = 3;
	relations = {
		{ 1, 2 },
		{ 2, 3 },
		{ 3, 1 } 
	};

	cout << s.minimumSemesters(n, relations) << "\n";
    
    return 0;
}