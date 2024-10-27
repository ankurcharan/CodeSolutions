// coast-lakes-ocean

// https://leetcode.com/discuss/interview-question/4835709/Google-Onsite-matrix-traversal-BFSDFS

// Google Onsite matrix traversal BFS/DFS

/*

Had my first onsite screening for Google (1 round for an hour) and got the question.


Given a matrix where land is marked as "X", water is marked as ".". A "." is considered an ocean 
if it's unbounded on atleast one side. A coast is any land directly connected to the ocean. 
Water grid bounded on all sides by land is considerd a lake.

Find if a given grid (co-ordinate) is a coast.


Eg:
x x x x x x
. . . x . x . .
. . . x x . x .


isCoast(1, 3) returns True


. . . . . . . .
x x x . x .
x . x x . x .
x x x . x x
x x x x x x


isCoast(3, 2) returns False

*/


#include <bits/stdc++.h>
using namespace std;


vector<pair<int, int>> moves = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

vector<vector<bool>> process(vector<vector<char>>& grid) {

	int n = grid.size();
	if (n == 0)		return { };

	int m = grid[0].size();
	if (m == 0)		return { };

	vector<vector<bool>> visit(n, vector<bool>(m, false));

	// queue for bfs
	queue<pair<int, int>> q;

	for (int i = 0 ; i < n ; i++) {
        // first column
        if (grid[i][0] == '.') {
			visit[i][0] = true;
			q.push({ i, 0 });
		}
        
        // last column
        if (grid[i][m - 1] == '.') {
			visit[i][m - 1] = true;
			q.push({ i, m - 1 });
		}
	}

	
	for (int j = 1 ; j < m - 1 ; j++) {
        // first row
		if (grid[0][j] == '.') {
			visit[0][j] = true;
			q.push({ 0, j });
		}
        
        // last row
        if (grid[n - 1][j] == '.') {
			visit[n - 1][j] = true;
			q.push({ n - 1, j });
		}
	}

	// visit all possible place and mark as ocean
	while (!q.empty()) {

		pair<int, int> f = q.front();
		q.pop();

        cout << "pop: " << f.first << ", " << f.second << endl;
        
		for (int i = 0 ; i < 4 ; i++) {

			int nextX = f.first + moves[i].first;
			int nextY = f.second + moves[i].second;

			if (nextX < 0 || nextX >= n || nextY < 0 || nextY >= m)
				continue;

			if (visit[nextX][nextY])
				continue;

			if (grid[nextX][nextY] == '.') {
			q.push({ nextX, nextY });
			visit[nextX][nextY] = true;
			}
		}
	}

	return visit;
}

void print(vector<vector<bool>> grid) {

	int n = grid.size();
	if (n == 0)		return;

	int m = grid[0].size();
	if (m == 0)		return;

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {

			cout << setw(5) << boolalpha << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void print(vector<vector<char>> grid) {

	int n = grid.size();
	if (n == 0)		return;

	int m = grid[0].size();
	if (m == 0)		return;

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {

			cout << setw(5) << boolalpha << grid[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {

	vector<vector<char>> grid = {
	    { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	    { '.', '.', '.', 'X', '.', 'X', '.', '.' },
	    { '.', '.', '.', 'X', 'X', '.', 'X', '.' }
	};

	vector<vector<bool>> ocean = process(grid);
    print(grid);
	print(ocean);


	return 0;
}