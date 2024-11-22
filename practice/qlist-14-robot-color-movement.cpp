// qlist-14-robot-color-movement.cpp

// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 14
////////////////////////////////////////////////////////////////////////////////////////////////////


/*

There is a robot at location (0, 0) of a 10x10 grid of tiles. 
Each tile can be one of 8 different colors: (0, 1, ... 7). 
There is a star at a known location (marked with the color -1) on the grid. 
You can program the robot by giving it a lookup table of color to direction. 
The robot will sense the color of the tile it is currently on, and move in the direction (up, down, left, or right) 
specified by the lookup table you provided. 

Output a lookup table that guides the robot to the star, if such a table is possible.

Small example grid: 
[
	[(0), 1,  0, 0 ], 
	[ 3,  2, -1, 3 ], 
	[ 0,  0,  0, 2 ], 
	[ 0,  0,  0, 4 ]
]
Solution: E S N W

*/


// Usama got the same question.





#include<bits/stdc++.h>
using namespace std;




bool isValidIndex(int i, int j, int n, int m)
{
	return i >= 0 && i < n && j >= 0 && j < m;
}


bool reached(int currX, int currY, int n, int m, vector<vector<int>>& a, vector<int>& colors, const vector<pair<int, int>>& moves, vector<vector<bool>>& visit) {

	if (a[currX][currY] == -1)
		return true;
    
    visit[currX][currY] = true;

	int moveIndex = colors[a[currX][currY]];

	int nextX = currX + moves[moveIndex].first;
	int nextY = currY + moves[moveIndex].second;
	
	if (!isValidIndex(nextX, nextY, n, m))
		return false;
    
    if (visit[nextX][nextY] == true)
        return false;

	return reached(nextX, nextY, n, m, a, colors, moves, visit);
}


bool possible(vector<vector<int>>& a, vector<int> colors, vector<pair<int, int>> moves)
{
	int n = a.size();
	int m = a[0].size();
    
    vector<vector<bool>> visit(n, vector<bool>(m, false));

	if (reached(0, 0, n, m, a, colors, moves, visit))
		return true;
    
    return false;
}

int getMaxValueInMatrix(vector<vector<int>>& a) {
    
    int n = a.size();
    if (n == 0)
        return -1;
    int m = a[0].size();
    if (m == 0)
        return -1;
    
    int ans = a[0][0];
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            ans = max(ans, a[i][j]);
        }
    }
    
    return ans;
}

vector<int> getAns(vector<vector<int>> a) {

	const vector<pair<int, int>> moves = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
    
    int maxValue = getMaxValueInMatrix(a);
    if (maxValue == -1)
        return  {};      // 
    
	vector<int> colors(8, -1);
    
    int numCombinations = 0;
    int casesTested = 0;
    
    // cout << pow(4, 8) << " vs " <<  pow(4, maxValue + 1) << "\n";
    
    for (int i = 0 ; i < pow(4, maxValue + 1) ; i++)
    {
        int t = i;
        for (int j = 0 ; j < 8 ; j++)
        {
            colors[j] = t % 4;
            t = t / 4;
        }
        
        // cout << "color: ";
        // for (int x = 0 ; x < 8 ; x++)
        //     cout << colors[x];
        // cout << "\n";
        
        if (possible(a, colors, moves))
        {
            return colors;
        }
    }
    
	return { };
}

void printIntVector(vector<vector<int>> a) {

	int n = a.size();
    if (n == 0)     return;
    
	int m = a[0].size();    if (m == 0)     return;

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < n ; j++) {
			cout << setw(2) << a[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}


int main() {

	int n, m;
	// cin >> n >> m;

	vector<vector<int>> a;



	// TC1 
	// expected =  E S N W
	n = 4;
	m = 4;
	a = {
		{ 0, 1, 0, 0 },
		{ 0, 1, -1, 3 },
		{ 0, 0, 0, 2 },
		{ 0, 0, 0, 0 }
	};



	// // TC2
	// // expected = E S N E W E E E 
	// n = 10;
	// m = 10;
	// a = {
	// 	{ 0, 0, 1, 0, 0, 0,  0, 0, 0, 0 },
	// 	{ 0, 0, 1, 0, 7, 0,  1, 0, 5, 0 },
	// 	{ 0, 0, 1, 0, 0, 6,  0, 2, 0, 0 },
	// 	{ 0, 0, 1, 0, 5, 0,  4, 0, 3, 0 },
	// 	{ 0, 0, 1, 0, 0, 0,  0, 0, 0, 0 },
	// 	{ 0, 0, 1, 0, 0, 0,  0, 0, 0, 0 },
	// 	{ 0, 0, 1, 0, 0, -1, 4, 4, 4, 0 },
	// 	{ 0, 0, 1, 0, 0, 0,  0, 0, 2, 0 },
	// 	{ 0, 0, 0, 0, 0, 0,  0, 0, 2, 0 },
	// 	{ 0, 0, 0, 0, 0, 0,  0, 0, 0, 0 },
	// };
    
	// // // TC3
	// n = 0;
	// m = 0;
	// a = {};






	// for (int i = 0 ; i < n ; i++) {

	// 	vector<int> t;
	// 	int z;
	// 	for (int j = 0 ; j < m ; j++) {

	// 		cin >> z;
	// 		t.push_back(z);
	// 	}
	// 	a.push_back(t);
	// 	t.clear();
	// }
	
	printIntVector(a);

    vector<char> directions = { 'N', 'E', 'S', 'W' };
	vector<int> ans = getAns(a);
    
	cout << "ans size: " << ans.size() << endl;
    
    if (ans.size() == 0)
    {
        cout << "no path\n";
        return 0;
    }
    
	for (int i = 0 ; i < ans.size() ; i++)
	    cout << i << " - " << ans[i] << " " << directions[ans[i]] << endl;
	cout << endl;

	return 0;
}
