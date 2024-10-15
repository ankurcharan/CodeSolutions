// 417. Pacific Atlantic Water Flow
// https://leetcode.com/problems/pacific-atlantic-water-flow/description/

class Solution {

	int dx[4] = { 1, -1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };

	bool safeIndex(int i, int j, int n, int m) {
		return i >= 0 && i < n && j >= 0 && j < m;
	}
public:
    void bfs(queue<pair<int, int>>& q, int n, int m, vector<vector<bool>>& visited, vector<vector<int>>& heights) {

    	while (!q.empty()) {

    		pair<int, int> f = q.front();
    		q.pop();

    		visited[f.first][f.second] = true;

    		for (int i = 0 ; i < 4 ; i++) {

    			int nextX = f.first + dx[i];
    			int nextY = f.second + dy[i];

    			if (safeIndex(nextX, nextY, n, m) && visited[nextX][nextY] == false
    				&& heights[nextX][nextY] >= heights[f.first][f.second])
    			{
    				q.push({ nextX, nextY });
    			}
    		}
    	}
    }

    void printMatrix(vector<vector<bool>>& a, int n, int m) {

    	for (int i = 0 ; i < n ; i++) {
    		for (int j = 0 ; j < m ; j++) {
    			cout << setw(5) << boolalpha << a[i][j] << " ";
    		}
    		cout << endl;
    	}
    	cout << endl;
    }


    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        
        int n = heights.size();
        if (n == 0)	return { {} };

        int m = heights[0].size();
        if (m == 0)	return { {} };

        vector<vector<bool>> visitedP(n, vector<bool> (m, false));
        vector<vector<bool>> visitedA(n, vector<bool> (m, false));

        // pacific and atlantic bfs queues
        queue<pair<int, int>> p, a;

        for (int i = 0 ; i < n ; i++) {
        	p.push({ i, 0 });
        	a.push({ i, m - 1 });
        }

        for (int i = 0 ; i < m ; i++) {
        	p.push({ 0, i });
        	a.push({ n - 1, i });
        }

        bfs(p, n, m, visitedP, heights);
        bfs(a, n, m, visitedA, heights);

        vector<vector<int>> ans;
        for (int i = 0 ; i < n ; i++) {
        	for (int j = 0 ; j < m ; j++) {

        		if (visitedA[i][j] && visitedP[i][j])
        			ans.push_back({ i, j });
        	}
        }

        return ans;
    }
};