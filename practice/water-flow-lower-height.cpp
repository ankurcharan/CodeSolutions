// water-flow-lower-height

// https://leetcode.com/discuss/interview-question/4817033/Google-or-Phone-Screen-or-2024


/*

I got the following question in the phone screen at Google:


Given is a 2D array that describes the height of a landscape and the location of 2 cities within this 2D array. I am now looking for the highest position to place a water tower there so that both cities can be supplied with water.


Rules:


The pipes of the tower are not allowed to run diagonally
The pipes must always slope downwards (i.e. be lower than the previous cell) or be at the same height, otherwise the water would run upwards
Inputs:


heights = [
[4, 9, 7, 6, 5],
[2, 6, 5, 4, 3],
[6, 5, 1, 2, 8],
[3, 4, 7, 2, 5]
]

town1 = [1, 4]
town2 = [3, 1]
Output:


[0, 1]
Explanation:


From [0, 1], which is 9, for example, a line runs via 9 -> 7 -> 6 -> 5 -> 3 (Town 1)
A pipeline runs to Town 2 via 9 -> 6 -> 5 -> 4 (Town 2)
Other Example:


heights = [
[9, 0, 1, 0],
[0, 0, 1, 0],
[1, 1, 1, 0]
]

town1 = [1, 3]
town2 = [2, 3]
Although 9 is the highest here, the water would run upwards to reach the cities, which is not possible
In this example, a water tower could be placed at all locations where there is a 1



*/


/*

same as

https://leetcode.com/problems/pacific-atlantic-water-flow/description/
*/

#include <bits/stdc++.h>
using namespace std;

bool validIndex(int i, int j, int n, int m) {
	return i >= 0 && i < n && j >= 0 && j < m;
}

vector<pair<int, int>> moves = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }; 

vector<int> getTowerPosition(vector<vector<int>>& a, pair<int, int>& townA, pair<int, int>& townB) {

	int n = a.size();
	if (n == 0)	return { -1, -1 };

	int m = a[0].size();
	if (m == 0)	return { -1, -1 };

	if (!validIndex(townA.first, townA.second, n, m) || !validIndex(townB.first, townB.second, n, m))
		return { -1, -1 };

	vector<vector<bool>> visitA(n, vector<bool>(m, false));
	vector<vector<bool>> visitB(n, vector<bool>(m, false));

	// ( 0/1, (x, y))
	// 0 = townA
	// 1 = townB
	queue<pair<int, pair<int, int>>> q;
	q.push({ 0, { townA.first, townA.second } });
	q.push({ 1, { townB.first, townB.second } });

	visitA[townA.first][townA.second] = true;
	visitB[townB.first][townB.second] = true;

	// if no path possible
	vector<int> ans = { -1, -1 };		// solution index
	int ansHeight = -1;

	while (!q.empty()) {

		pair<int, pair<int, int>> f = q.front();
		q.pop();

		for (int i = 0 ; i < 4 ; i++) {

			int nextX = f.second.first + moves[i].first;
			int nextY = f.second.second + moves[i].second;
		
			if (!validIndex(nextX, nextY, n, m))
				continue;

			if (a[nextX][nextY] < a[f.second.first][f.second.second])
					continue;

			if (f.first == 0) {

				if (visitA[nextX][nextY])
					continue;

				if (visitB[nextX][nextY]) {
					// cout << "curr: " << f.second.first << ", " << f.second.second << ", nextX: " << nextX << ", nextY: " << nextY << endl;
					// return { nextX, nextY };
					if (ansHeight < a[nextX][nextY])
					{
						ansHeight = a[nextX][nextY];
						ans = { nextX, nextY };
					}
				}

				cout << "curr: " << f.second.first << ", " << f.second.second << " val: " << a[f.second.first][f.second.second] << ", nextX: " << nextX << ", nextY: " << nextY << ", val: " << a[nextX][nextY] << endl;
				visitA[nextX][nextY] = true;
				q.push({ 0, { nextX, nextY }});

			}
			else if (f.first == 1) {

				if (visitB[nextX][nextY])
					continue;

				// if (a[nextX][nextY] < a[f.second.first][f.second.second])
				// 	continue;

				if (visitA[nextX][nextY]) {

					if (ansHeight < a[nextX][nextY])
					{
						ansHeight = a[nextX][nextY];
						ans = { nextX, nextY };
					}

					// return { nextX, nextY };
				}

				visitB[nextX][nextY] = true;
				q.push({ 1, { nextX, nextY }});
			}
		}
	}

	return ans;
}

int main() {

	// // tc 1
	// vector<vector<int>> a = { 
	// 	{ 4, 9, 7, 6, 5 },
	// 	{ 2, 6, 5, 4, 3 },
	// 	{ 6, 5, 1, 2, 8 },
	// 	{ 3, 4, 7, 2, 5 }
	// };
	// pair<int, int> townA = { 1, 4 };
	// pair<int, int> townB = { 3, 1 };

	// // ans = [0, 1]


	// tc 2 
	vector<vector<int>> a = {
		{ 9, 0, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 }
	};
	pair<int, int> townA = { 1, 3 };
	pair<int, int> townB = { 2, 3 };

	// ans = [any location with 1 height]

	vector<int> ans = getTowerPosition(a, townA, townB);

	cout << ans[0] << ", " << ans[1] << endl;

	return 0;
}