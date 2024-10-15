// 994. Rotting Oranges
// https://leetcode.com/problems/rotting-oranges/

#define F first
#define S second

class Solution {

    int dx[4] = { 1, -1, 0,  0 };
    int dy[4] = { 0,  0, 1, -1 };
public:

    int orangesRotting(vector<vector<int>>& grid) {
        
        int m = grid.size();
        if (m == 0) return 0;
        int n = grid[0].size();

        vector<vector<bool> > visit(m, vector<bool>(n, false));

        // bfs
        // (x, y), dist
        queue<pair<pair<int, int>, int> > q; 

        for (int i = 0 ; i < m ; i++) {
            for (int j = 0 ; j < n ; j++) {
                if (grid[i][j] == 2) {

                    visit[i][j] = true;
                    q.push({ { i, j }, 0 });
                }
            }
        }

        int ans = 0;
        while(!q.empty()) {

            pair<pair<int, int>, int> f = q.front();
            q.pop();

            ans = max(ans, f.S);

            for(int i = 0 ; i < 4 ; i++) {

                int tx = f.F.F + dx[i];
                int ty = f.F.S + dy[i];

                if (tx < 0 || tx >= m || ty < 0 || ty >= n) continue;

                if(grid[tx][ty] == 1 && visit[tx][ty] == false) {

                    visit[tx][ty] = true;
                    q.push({ {tx, ty}, f.S + 1 });
                }
            }
        }

        for (int i = 0 ; i < m ; i++) {
            for (int j  = 0 ; j < n ; j++) {

                if (grid[i][j] == 1 && visit[i][j] == false)
                    return -1;
            }
        }

        return ans;
    }
};