// no-of-ways-in-matrix
// https://leetcode.com/discuss/interview-question/6038441/google-l4-phonescreen

/**

Initial Question: 
	You are given an n×m grid and 
	start from the bottom-left corner with the goal of reaching the bottom-right corner. 
	The allowed moves are only to the 
	right, diagonally up-right, and diagonally down-right. 

	The task is to determine the total number of unique paths 
	that can lead you from the starting point to the destination 
	while adhering to these movement rules.


Follow-Up 1: 
	A list of specific checkpoints within the grid is now introduced. 
	In this variation, 
	you are required to count only those paths that pass 
	through each of these checkpoints once before reaching the bottom-right corner.

Follow-Up 2: 
	The order of visiting these checkpoints is now specified. 
	For example, if the checkpoints are labeled 1, 2, and 3, 
	any valid path must encounter checkpoint 1 first, then checkpoint 2, and finally checkpoint 3, 
	in that exact sequence, on its way to the destination.

completed all parts of the problem within 30 minutes, including a 10 minute dry run, leaving additional time for discussing Google’s culture.
*/


#include <bits/stdc++.h>
using namespace std;


void print(vector<vector<bool>>& visit, int n, int m) {

	cout << "\n";
    for (int l = 0 ; l < n ; l++) {
        for (int x = 0 ; x < m ; x++) {
            cout << visit[l][x] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}









// 3 moves. - right, bottom right, top right
vector<pair<int, int>> moves = { { 0, 1 }, { 1, 1 }, { -1, 1 } };

int dfs(int i, int j, int n, int m, vector<vector<bool>>& visit) {
    
	if (i < 0 || j < 0 || i >= n || j >= m)
		return 0;
    
	if (i == n - 1 && j == m - 1) {
        
        cout << "reached: " << i << ", " << j;
        print(visit, n, m);
        
        return 1;
    }

	int ans = 0;
    
    for (int z = 0 ; z < moves.size() ; z++) {

		int nextX = i + moves[z].first;
		int nextY = j + moves[z].second;
	
        if (nextX >= 0 && nextY >= 0 && nextX < n && nextY < m) {
            
            if (visit[nextX][nextY] == false) {
            	visit[nextX][nextY] = true;
                ans += dfs(nextX, nextY, n, m, visit);
            	visit[nextX][nextY] = false;
            }
        }
	}

	return ans;
}

int getNumberOfWays(int n, int m) {

    // cout << n << ", " << m << " nm\n";
    vector<vector<bool>> visit(n, vector<bool>(m, false));
    visit[n - 1][0] = true;
	return dfs(n - 1, 0, n, m, visit);
}


int getNumberOfWaysDynamicProgramming(int n, int m) {

    vector<vector<int>> dp(n, vector<int>(m, 0));

    dp[n - 1][0] = 1;

    for (int j = 1 ; j < m ; j++) {
    	for (int i = 0 ; i < n ; i++) {

    		dp[i][j] += dp[i][j - 1];

    		if (i - 1 >= 0)
	    		dp[i][j] += dp[i - 1][j - 1];
    		if (i + 1 < n)
	    		dp[i][j] += dp[i + 1][j - 1];
    	}
    }

    for (int i = 0 ; i < n ; i++) {
    	for (int j = 0 ; j < m ; j++) {
    		cout << setw(3) << dp[i][j] << " ";
    	}
    	cout << "\n";
    }

    return dp[n - 1][m - 1];
}


int getNumberIndex(int i, int j, int n, int m) {

	return (i * n) + j;
}

int dfsWithCheckpoint(int i, int j, int n, int m, vector<vector<bool>>& visit, unordered_set<int>& checkpointsSet) {

	int currIndex = getNumberIndex(i, j, n, m);
	bool currCheckpoint = false;
	if (checkpointsSet.find(currIndex) != checkpointsSet.end()) {

		currCheckpoint = true;
		checkpointsSet.erase(currIndex);
	}

	if (i == n - 1 && j == m - 1) {

		print(visit, n, m);

		// reached
		if (checkpointsSet.size() == 0) {
			cout << "returning 1\n";
			return 1;
		}

		// reached but not all checkpoints used
		cout << "returning 0\n";
		return 0;
	}

	int ans = 0;
    
    for (int z = 0 ; z < moves.size() ; z++) {

		int nextX = i + moves[z].first;
		int nextY = j + moves[z].second;
	
        if (nextX >= 0 && nextY >= 0 && nextX < n && nextY < m) {
            
            if (visit[nextX][nextY] == false) {
    
            	visit[nextX][nextY] = true;
                ans += dfsWithCheckpoint(nextX, nextY, n, m, visit, checkpointsSet);
            	visit[nextX][nextY] = false;
            }
        }
	}

	if (currCheckpoint) {
		checkpointsSet.insert(currIndex);
	}

	return ans;
}

int getNumberOfWaysWithCheckpoint(int n, int m, unordered_set<int>& checkpointsSet) {

	vector<vector<bool>> visit(n, vector<bool>(m, false));

	visit[n - 1][0] = true;
	return dfsWithCheckpoint(n - 1, 0, n, m, visit, checkpointsSet);
}

int dfsWithCheckpointInOrder(int i, int j, int n, int m, vector<pair<int, int>>& checkpoints, int ci) {

	bool currentPointIsCheckpoint = false;
	if (ci < checkpoints.size()) {
		int currIndex = getNumberIndex(i, j, n, m);
		int ciIndex   = getNumberIndex(checkpoints[ci].first, checkpoints[ci].second, n, m);	
	
		if (currIndex == ciIndex)
			currentPointIsCheckpoint = true;
	}

	if (i == n - 1 && j == m - 1) {

		// reached in order
		if (ci == checkpoints.size()) {
			return 1;
		}
		// reached without all checkpoints in order
		else {
			return 0;
		}
	}

	if (currentPointIsCheckpoint) 
		ci++;


	int ans = 0;

	for (int z = 0 ; z < 3 ; z++) {

		int nextX = i + moves[z].first;
		int nextY = j + moves[z].second;

		if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < m) {

			ans += dfsWithCheckpointInOrder(nextX, nextY, n, m, checkpoints, ci);
		}
	}

	return ans;
}

int getNumberOfWaysWithCheckpointInOrder(int n, int m, vector<pair<int, int>>& checkpoints, int ci) {
	
	return dfsWithCheckpointInOrder(n - 1, 0, n, m, checkpoints, ci);	
}

int main() {
    
    // -  0  1
    // 0  .  . 
    // 1  .  . 
	// // int n = 2;
	// // int m = 2;

	//////////////////////////////////
	// total number of way
	//////////////////////////////////

	// int numOfWays = getNumberOfWays(2, 2);
	// cout << "numOfWays: " << numOfWays << "\n";
    
	// int numOfWays2 = getNumberOfWays(4, 6);
	// cout << "numOfWays: " << numOfWays2 << "\n";
    
    // int numOfWays3 = getNumberOfWays(4, 4);
	// cout << "numOfWays: " << numOfWays3 << "\n";

	// int numOfWays3 = getNumberOfWays(3, 8);
	// cout << "numOfWays: " << numOfWays3 << "\n";

	// int numOfWays21 = getNumberOfWaysDynamicProgramming(4, 6);
	// cout << "numOfWays: " << numOfWays21 << "\n";

	// int numOfWays31 = getNumberOfWaysDynamicProgramming(3, 8);
	// cout << "numOfWays: " << numOfWays31 << "\n";



	//////////////////////////////////
	// pass through checkpoints
	//////////////////////////////////


	// int n = 4;
	// int m = 4;

	// vector<pair<int, int>> checkpoints = { 
	// 	{ 2, 1 },
	// 	{ 3, 2 }
	// };

	// unordered_set<int> checkpointsSet;
	// for (pair<int, int>& c: checkpoints) {
	// 	checkpointsSet.insert(getNumberIndex(c.first, c.second, n, m));
	// }

	// // for (auto x: checkpointsSet) {
	// // 	cout << x << " ";
	// // }

	// int numOfWays4 = getNumberOfWaysWithCheckpoint(n, m, checkpointsSet);
	// cout << "numOfWays: " << numOfWays4 << "\n";




	///////////////////////////////////////
	// pass through checkpoints in order //
	///////////////////////////////////////

	// int n = 4;
	// int m = 4;

	// // 1 way
	// vector<pair<int, int>> checkpoints = { 
	// 	{ 2, 1 },
	// 	{ 3, 2 }
	// };

	// // 0 way
	// vector<pair<int, int>> checkpoints = { 
	// 	{ 3, 2 },
	// 	{ 2, 1 }
	// };

	// int numOfWays5 = getNumberOfWaysWithCheckpointInOrder(n, m, checkpoints, 0);
	// cout << "numOfWays: " << numOfWays5 << "\n";

	return 0;
}
