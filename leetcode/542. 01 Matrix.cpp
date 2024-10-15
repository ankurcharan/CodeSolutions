// 542. 01 Matrix
// https://leetcode.com/problems/01-matrix/description/

class Solution {
public:
	int dx[8] = { 1, -1, 0, 0 };
	int dy[8] = { 0, 0, -1, 1 };

	void print(vector<vector<int>>& a) {

		int n = a.size();
    	int m = a[0].size();

    	for (int i = 0 ; i < n ; i++) {

    		for (int j = 0 ; j < m ; j++) {

    			cout << setw(2) << a[i][j] << " ";
    		}
    		cout << endl;
    	}
    	cout << endl;
	}

    vector<vector<int>> updateMatrix(vector<vector<int>>& a) {

    	int n = a.size();
    	int m = a[0].size();

    	queue<pair<int, int>> q;

    	print(a);

    	for (int i = 0 ; i < n ; i++) {

    		for (int j = 0 ; j < m ; j++) {

    			if (a[i][j] == 0) {
    				q.push({ i, j });
    				continue;
    			}

    			a[i][j] = -1;
    		}
    	}

    	print(a);

    	while (!q.empty()) {

    		pair<int, int> f = q.front();
    		q.pop();

    		for (int i = 0 ; i < 8 ; i++) {

    			int adjX = f.first  + dx[i];
    			int adjY = f.second + dy[i];
    		
    			if (adjX >= 0 && adjX < n && adjY >= 0 && adjY < m && a[adjX][adjY] == -1) {
    				a[adjX][adjY] = a[f.first][f.second] + 1;
    				q.push({ adjX, adjY });
    			}
    		}
    	}

    	print(a);

    	return a;
    }
};