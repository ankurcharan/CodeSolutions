// int-2-directions-to-exit
// https://leetcode.com/discuss/interview-question/5898854/L5-Google-or-Interview-Exp.-or-Rejected

/**
 * 

Round 2 (The Downhill Part):
The interviewer came late (by 5 minutes), 
didn’t ask for an introduction, and gave a vague problem. 
I took some time to fully understand it. 
The hints provided were not helpful and actually made things worse. 
The interviewer didn’t participate much, and in the end, 
just asked me to write down whatever I thought would work.


Question:
You are given a matrix of 0s, 1s, and 2s, where 0 means an empty cell, 
1 means a wall, and 2 means an exit. 
There will always be an exit. 
Generate a sequence of instructions (U, D, L, R) such that 
no matter where you start in the matrix, you always reach the exit.

Example:

1 0 1  
0 2 0  
1 0 1  

Answer: UDLR (No matter where you start, you’ll end up at 2).
Feedback: Not hire (feedback : weak in problem-solving).


 * 
 * */


#include <bits/stdc++.h>
using namespace std;

unordered_map<char, pair<int, int>> moves = {
	{ 'U', { -1,  0  } },
	{ 'D', {  1,  0  } },
	{ 'L', {  0, -1  } },
	{ 'R', {  0,  1  } }
};

bool validIndex(int i, int j, int n, int m) {

	return i >= 0 && i < n && j >= 0 && j < m;
}

string findPathToExit(vector<vector<int>>& a, int n, int m, vector<vector<bool>>& visit, int sx, int sy) {

	

	queue<pair<pair<int, int>, string>> q;

	q.push({ { sx, sy }, "" });

	while (!q.empty()) {

		pair<pair<int, int>, string> f = q.front();
		q.pop();

		int x = f.first.first;
		int y = f.first.second;

		string path = f.second;

		// cout << "pop: (" << x << ", " << y << ") => \n";

		for (auto& move: moves) {

			int nx = x + move.second.first;
			int ny = y + move.second.second;

			if (validIndex(nx, ny, n, m)) {

				// cout << "(" << nx << ", " << ny << ": " << a[nx][ny] << " == " ;

				if (a[nx][ny] == 0) {
					// cout << move.first;
					q.push({ { nx, ny }, path + move.first });
				}
				else if (a[nx][ny] == 2) {
					// cout << "ret)\n";
					return path + move.first;
				}
				else {
					// cout << "wall";
				}
				// cout << "\n";
			}
		}
	}

	return "nopath";
}

void print(vector<vector<int>>& a) {

	int n = a.size();
	if (n == 0) return;

	int m = a[0].size();
	if (m == 0) return;


	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {

			cout << setw(2) << a[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void print(vector<vector<bool>>& a) {

	int n = a.size();
	if (n == 0) return;

	int m = a[0].size();
	if (m == 0) return;


	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {

			cout << setw(5) << boolalpha << a[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void markPlace(vector<vector<int>>& a, vector<vector<bool>>& visit, int n, int m, string path, vector<pair<int, int>>& twos) {

	queue<pair<int, int>> q;

	for (int i = 0 ; i < twos.size() ; i++) {
		visit[twos[i].first][twos[i].second] = true;
		q.push({ twos[i].first, twos[i].second });
	}

	int pathSize = path.size();

	for (int i = pathSize - 1 ; i >= 0 ; i--) {

		char d = path[i];

		char x = ' ';

		if (d == 'U')
			x = 'D';
		else if (d == 'D')
			x = 'U';
		else if (d == 'L')
			x = 'R';
		else if (d == 'R')
			x = 'L'; 

		pair<int, int> move = moves[x];
	
		int qs = q.size();
		for (int j = 0 ; j < qs ; j++){

			pair<int, int> f = q.front();
			q.pop();

			visit[f.first][f.second] = true;

			int nx = f.first + move.first;
			int ny = f.second + move.second;

			if (validIndex(nx, ny, n, m) && (a[nx][ny] == 0)) {
				q.push({ nx, ny });
			}
			else {
				q.push(f);
			}
		}
	}	
}

string findTheSequence(vector<vector<int>>& a) {

	int n = a.size();
	if (n == 0)		return "";

	int m = a[0].size();
	if (m == 0)		return "";

	vector<vector<bool>> visit(n, vector<bool>(m, false));

	vector<pair<int, int>> zero;
	vector<pair<int, int>> twos;

	// print(a);

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {

			if (a[i][j] == 0)
				zero.push_back({ i, j });
			else if (a[i][j] == 2)
				twos.push_back({ i, j });
		}
	}

	// print(a);

	for (int i = 0 ; i < zero.size() ; i++) {

		if (visit[zero[i].first][zero[i].second] == false) {

			string path = findPathToExit(a, n, m, visit, zero[i].first, zero[i].second);
			
			cout << "found path: (" << zero[i].first << ", " << zero[i].second << ") path: " << path << "\n";

			markPlace(a, visit, n, m, path, twos);

			visit[zero[i].first][zero[i].second] = true;
			print(visit);
		}
	}


	return "-1";
}

int main() {
	
	// vector<vector<int>> a = {
	// 	{ 1, 0, 1 },
	// 	{ 0, 2, 0 },
	// 	{ 1, 0, 1 }
	// };

	vector<vector<int>> a = {
		{ 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 1, 1, 1, 0, 1, 1, 1, 0 },
		{ 1, 1, 1, 0, 1, 1, 1, 0 },
		{ 1, 1, 1, 0, 1, 1, 1, 0 },
		{ 1, 1, 1, 0, 1, 1, 1, 0 },
		{ 2, 0, 0, 0, 0, 0, 0, 0 },
	};

	string ans = findTheSequence(a);
	cout << "sequence: " << ans << "\n";

	return 0;
}


