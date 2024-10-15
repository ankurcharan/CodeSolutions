// 200. Number of Islands
// https://leetcode.com/problems/number-of-islands/description/

class Solution {

	bool safeIndex(int i, int j, int n, int m) {

		return i >= 0 && i < n && j >= 0 && j < m;
	}
public:
	int dx[4] = { 1, -1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };

	void dfs(vector<vector<char>>& g, int i, int j, int n, int m, vector<vector<bool>>& visited) {

        // cout << "i: " << i << ", j: " << j << endl;

		visited[i][j] = true;

		for (int z = 0 ; z < 4 ; z++) {

			if (safeIndex(i + dx[z], j + dy[z], n, m) && g[i + dx[z]][j + dy[z]] == '1' && visited[i + dx[z]][j + dy[z]] == false)
				dfs(g, i + dx[z], j + dy[z], n, m, visited);
		}
	}

    int numIslands(vector<vector<char>>& g) {

    	int n = g.size();
    	if (n == 0) return 0;

    	int m = g[0].size();
    	if (m == 0)	return 0;

    	int numOfComponents = 0;

    	vector<vector<bool>> visited(n, vector<bool> (m, false));
    
    	for (int i = 0 ; i < n ; i++) {

    		for (int j = 0 ; j < m ; j++) {

    			if (g[i][j] == '1' && visited[i][j] == false)
    			{
    				dfs(g, i, j, n, m, visited);
    				numOfComponents++;
    			}
    		}
    	}

    	return numOfComponents++;
    }
};