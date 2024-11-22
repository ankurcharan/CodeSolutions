// min-max-dist-from-cat





// mouse-move-with-cat
// https://leetcode.com/discuss/interview-question/5967704/Google-India-or-L3-or-Phone-Screen




/*

///////////////////////////////////////////
as told by manasa's friend
///////////////////////////////////////////




You can give a matrix marked with 'S' as source, and 'D' as destination. 
You can move in four direction. 

There are cats in matrix marked with 'X'
you have to find the min distance from S to D which should be at max distance from cat. 



marking 'S' as -2
marking 'D' as -3

marking 'X' as -1

everything else is zero

*/





/**



Hi folks,


I'm currently in the interview process with Google and 
thought I'd share my screening round question for those who may find it helpful.


Experience: 	1.5 years
Position : 		Google (Level wasn't disclosed, assuming L3 for my YOE)
Location: 		Bangalore / Hyderabad, India
Date: 			October 2024
Phone Screen : 	45 minutes


The interviewer started with a straight-forward grid question :

	You are given a grid with locations for a mouse and a target cheese block. 
	The mouse wants to reach the cheese, some cells are filled with water which cannot be crossed.  
	Can the mouse reach the cheese? 
	The mouse can move along the horizontal and vertical directions.
	Just the approach was discussed for this. Standard bfs solution.

Follow up 1:

	The grid also has a cat at some given location. 
	You have to find the maximum distance which you can always maintain from the cat.  
	I assumed the distance as Manhattan distance. Used a priority queue while traversing the grid.
		Time complexity : O(n^2 log N)
		Space complexity : O(n^2)


Follow up 2:

	What if we want to find the shortest path for this maximum distance?
	We can track the steps required to reach the destination in the above approach.


The interviewer was helpful throughout the interview, 
and was satisfied with the approach. We wrapped up 5 minutes early.

The recruiter came back with positive feedback and I have my onsites scheduled. I will add those questions too in a few days.


Thoughts on other approaches?


*/












#include <bits/stdc++.h>
using namespace std;

//////////////////////////////////////////
////////// unrelated functions ///////////
//////////////////////////////////////////

vector<vector<int>> getSourceAndDest(vector<vector<int>>& a) {

	vector<int> src;
	vector<int> dest;

	int n = a.size();
	if (n == 0)	return { src, dest };
	int m = a[0].size();
	if (m == 0)	return { src, dest };

	for (int i = 0 ; i < n ; i++) {

		for (int j = 0 ; j < m ; j++) {

			// src
			if (a[i][j] == -2) {
				src.push_back(i);
				src.push_back(j);
			}

			// dest
			if (a[i][j] == -3) {
				dest.push_back(i);
				dest.push_back(j);
			}

			if (src.size() && dest.size())
				return { src, dest };
		}
	}

	return { src, dest };
}

void print(vector<vector<int>>& a) {

	int n = a.size();
	if (n == 0)	return;
	int m = a[0].size();
	if (m == 0)	return;

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
	if (n == 0)	return;
	int m = a[0].size();
	if (m == 0)	return;

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {
			cout << setw(2) << a[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}












vector<vector<int>> moves = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

void getDistanceFromCats(vector<vector<int>>& a) {

	int n = a.size();
	if (n == 0)	return;
	int m = a[0].size();
	if (m == 0)	return;

	// (x, y), distance
	queue<pair<pair<int, int>, int>> q;
	vector<vector<bool>> visit(n, vector<bool>(m, false));

	// push cat positions
	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {
			if (a[i][j] == -1) {
                visit[i][j] = true;
				q.push({ { i, j }, 0 });
			}
		}
	}


	while (!q.empty()) {

		// get the front position
		pair<pair<int, int>, int> f = q.front();
		q.pop();

		// update distance
		a[f.first.first][f.first.second] = f.second;

		for (int i = 0 ; i < 4 ; i++) {

			int x = f.first.first + moves[i][0];
			int y = f.first.second + moves[i][1];

			// if the next positions is valid and unvisited, push to queue
			if (x >= 0 && x < n && y >= 0 && y < m && visit[x][y] == false) {
				
				q.push({ { x, y }, f.second + 1 });
                visit[x][y] = true;
			}
		}
	}
}


int minDistanceFromSrcToDest(vector<vector<int>> a, vector<int>& src, vector<int>& dest) {

	int n = a.size();
	if (n == 0)	return 0;
	int m = a[0].size();
	if (m == 0)	return 0;


	// (x-coord, y-coord), distance
	queue<pair<pair<int, int>, int>> q;
	q.push({ { src[0], src[1] }, 0 });

	vector<vector<int>> dist(n, vector<int>(m, -1));
	dist[src[0]][src[1]] = 0;

	while (!q.empty()) {

		auto f = q.front();
		q.pop();
        
        // cout << "pop: " << f.first.first << ", " << f.first.second << "\n";

		// if reached dest coordinate
		if (f.first.first == dest[0] && f.first.second == dest[1])
			return f.second;		// return distance

		for (int i = 0 ; i < 4 ; i++) {

			int newX = f.first.first  + moves[i][0];
			int newY = f.first.second + moves[i][1];
		
            if (newX < 0 || newX >= n || newY < 0 || newY >= m || a[newX][newY] == -1)
                continue;
            
			if (dist[newX][newY] == -1) {

				dist[newX][newY] = f.second + 1;
				q.push({ {newX, newY }, dist[newX][newY] });
			}
		}
	}

	return -1;
}



int getMaxDistanceFromCatMaintained(vector<vector<int>> a, vector<int>& src, vector<int>& dest) {
    
    int n = a.size();
    if (n == 0)	return 0;
    int m = a[0].size();
    if (m == 0)	return 0;
    
    if (src[0] == dest[0] && src[1] == dest[1])
        return 0;

    vector<vector<bool>> visit(n, vector<bool>(m, false));
    
    // max heap should output the coordinate with max distance from cat
    // (distance from cat), (x-coord, y-coord)
    priority_queue<pair<int, pair<int, int>>> pq;
    // pq.push({ 0, { src[0], src[1] }});
    
    visit[src[0]][src[1]] = true;
    
    // push the neighbour elements
    for (int i = 0 ; i < 4 ; i++) {
            
        int newX = src[0] + moves[i][0];
        int newY = src[1] + moves[i][1];

        if (newX < 0 || newX >= n || newY < 0 || newY >= m)
            continue;

        if (a[newX][newY] == 0 || visit[newX][newY] == true)
            continue;

        // cout << "push: " << newX << ", " << newY << " = " << a[newX][newY] << "\n";
        
        pq.push({ a[newX][newY], { newX, newY } });
    }
    
    
    

    int maxDistanceFromCat = a[src[0]][src[1]];
    while (!pq.empty()) {
        
        pair<int, pair<int, int>> f = pq.top();
        pq.pop();
        
        visit[f.second.first][f.second.second] = true;
        
        // cout << "pop: " << f.second.first << ", " << f.second.second << " = " << f.first << "\n";
        
        maxDistanceFromCat = min(maxDistanceFromCat, f.first);
        
        if (f.second.first == dest[0] && f.second.second == dest[1])
            return maxDistanceFromCat;
        
        for (int i = 0 ; i < 4 ; i++) {
            
            int newX = f.second.first  + moves[i][0];
			int newY = f.second.second + moves[i][1];
		
            if (newX < 0 || newX >= n || newY < 0 || newY >= m)
                continue;
            
            if (a[newX][newY] == 0 || visit[newX][newY] == true)
                continue;
            
            // cout << "push: " << newX << ", " << newY << " = " << a[newX][newY] << "\n";
            
            pq.push({ a[newX][newY], { newX, newY } });
        }
    }
    
    // no way to destination
    return -1;
}

void dfs(vector<vector<int>>& a, int i, int j, int dx, int dy, int&n, int& m, vector<vector<int>>& visit, int step, int dist, int& minSteps, int& minDistance) {
    
    cout << "at: " << i << ", " << j << endl;
    
    if (i == dx && j == dy) {
        
        cout << "at destination: " << i << ", " << j << endl;
        cout << "steps: " << step << ", dist: " << dist << "\n";
        
        if ((step < minSteps) || (step == minSteps && dist > minDistance)) {
            
            minSteps = step;
            minDistance = dist;
            
            cout << "update steps: " << step << ", dist: " << dist << "\n";
            print(visit);
            
            return;
        }
    }
    
    for (int z = 0 ; z < 4 ; z++) {
        
        int newX = i + moves[z][0];
        int newY = j + moves[z][1];
        
        // cout << "(" << i << ", " << j <<  ") to (" << newX << ", " << newY << ")\n";
        
        if (newX < 0 || newX >= n || newY < 0 || newY >= m || a[newX][newY] == 0 || visit[newX][newY] != -1)
            continue;
        
        visit[newX][newY] = step;
        dfs(a, newX, newY, dx, dy, n, m, visit, step + 1, dist + a[newX][newY], minSteps, minDistance);
        visit[newX][newY] = -1;
    }
}

void getPath(vector<vector<int>> a, vector<int>& src, vector<int>& dest) {
    
    int n = a.size();
	if (n == 0)	return;
	int m = a[0].size();
	if (m == 0)	return;
    
    vector<vector<int>> visit(n, vector<int> (m, -1));
    int minSteps = INT_MAX;
    int minDistance = INT_MAX;
    
    visit[src[0]][src[1]] = 1;
    dfs(a, src[0], src[1], dest[0], dest[1], n, m, visit, 2, 0, minSteps, minDistance);
}


class cmp {
public:
    bool operator()(pair<pair<int, int>, pair<int, int>>& a, pair<pair<int, int>, pair<int, int>>& b) {
        
        if (a.first.first == b.first.first) {
            return a.first.second < b.first.second;
        }
        
        return a.first.first > b.first.first;
    }    
};

int getMinDistanceMaxFromCat(vector<vector<int>> a, vector<int>& src, vector<int>& dest) {
    
    int n = a.size();
	if (n == 0)	return 0;
	int m = a[0].size();
	if (m == 0)	return 0;
    
    // (steps, sumOfDistance), (x, y)
    // pair<pair<int, int>, pair<int, int>>;
    priority_queue<pair<pair<int, int>, pair<int, int>>, vector<pair<pair<int, int>, pair<int, int>>>, cmp> pq;

    vector<vector<int>> step(n, vector<int>(m, -1));
    vector<vector<int>> distance(n, vector<int>(m, -1));
    
//     cout << "\n\nsteps init\n";
//     print(step);
    
    
    pq.push({ { 0, 0 }, { src[0], src[1] } });
    
    while(!pq.empty()) {
        
        pair<pair<int, int>, pair<int, int>> f = pq.top();
        pq.pop();
        
        int currX = f.second.first;
        int currY = f.second.second;
        
        int currSteps = f.first.first;
        int dist = f.first.second;
        
        if (step[currX][currY] != -1) {
            // cout << "old value\n";
            continue;
        }
        // else {
        //     cout << "new value: ";
        // }
        
        cout << "pop: " << currSteps << ", " << dist << ", " << currX << ", " << currY << "  \n";
        
        step[currX][currY] = currSteps;
        distance[currX][currY] = dist;
        
        if (f.second.first == dest[0] && f.second.second == dest[1]) {
            
            // cout << "\n\ntotaldist: " << f.first.second << endl << endl;
            cout << "steps: \n";
            print(step);
            cout << "distance: \n";
            print(distance);
            
            return f.first.first;
        }
            
        bool d = false;
        
        
        for (int i = 0 ; i < 4 ; i++) {
            
            int x = f.second.first + moves[i][0];
            int y = f.second.second + moves[i][1];
            
            // if (x == 0 && y == 5)
            //     d = true;
            // else
            //     d = false;
            
            
            if (x >= 0 && x < n && y >= 0 && y < m && a[x][y] != 0) {
                
                // if (d)
                //     cout << "axy: " << a[x][y] << ", " << f.first.second + a[x][y] << "\n";
                pq.push({ { f.first.first + 1, f.first.second + a[x][y] }, { x, y } });
            }
        }
    }
    
    
    // cout << "\n\nsteps\n";
    // print(step);
    // cout << "distance: \n";
    // print(distance);
    
    return step[dest[0]][dest[1]];
}

    
    
int main() {

//     // testcase1
// 	vector<vector<int>> a = {

// 		{ 0,-2, 0, 0, 0, 0 }, 
// 		{ 0, 0, 0, 0, 0, 0 }, 
// 		{ 0, 0, 0, 0, 0, 0 }, 
// 		{ 0, 0,-1, 0, 0, 0 }, 
// 		{ 0, 0, 0, 0, 0, 0 }, 
// 		{-1, 0, 0, 0, 0,-3 }, 
// 	};
    
    
    
    // testcase2
	vector<vector<int>> a = {

		{  0, -2,  0,  0,  0,  0 }, 
		{ -1, -1, -1, -1, -1,  0 }, 
		{  0,  0,  0,  0,  0,  0 }, 
		{  0, -1, -1, -1, -1, -1 }, 
		{  0,  0,  0,  0,  0,  0 }, 
		{ -1,  0,  0,  0,  0, -3 }, 
	};
    
    
    
//     // testcase3
// 	vector<vector<int>> a = {

// 		{ -2,  0,  0,  0,  0, -1 }, 
// 		{  0,  0,  0,  0,  0,  0 }, 
// 		{  0,  0,  0,  0,  0,  0 }, 
// 		{  0,  0,  0,  0,  0,  0 }, 
// 		{  0,  0,  0,  0,  0,  0 }, 
// 		{  0,  0,  0,  0,  0, -3 }, 
// 	};
    
    
    cout << "matrix:\n";
    print(a);
    

	// -2 is source
	// -3 is destination
	// -1 is cat
	vector<vector<int>> srcAndDest = getSourceAndDest(a);

	// print(a);

	// coordinates -2
	vector<int> src  = srcAndDest[0];
	// coordinates -3
	vector<int> dest = srcAndDest[1];
    
    cout << "src : " << src[0] << ", " << src[1] << "\n";
    cout << "dest: " << dest[0] << ", " << dest[1] << "\n\n";

    //////////////////////////////////////
    // // main question 1
    // // min distance from source to dest
    //////////////////////////////////////
    int minDistanceFromSrcToDestAns = minDistanceFromSrcToDest(a, src, dest);
    cout << "minDistanceFromSrcToDestAns: " << minDistanceFromSrcToDestAns << "\n\n";

    
    //////////////////////////////////////
    // // Follow up 1:

	// // The grid also has a cat at some given location. 
	// // You have to find the maximum distance which you can always maintain from the cat.  
	// // I assumed the distance as Manhattan distance. Used a priority queue while traversing the grid.
		// // Time complexity : O(n^2 log N)
		// // Space complexity : O(n^2)
    //////////////////////////////////////
            
	getDistanceFromCats(a);
    
    cout << "distance from cat updated in matrix:\n";
	print(a);
    
    int maxDistanceFromCatMaintained = getMaxDistanceFromCatMaintained(a, src, dest);
    cout << "maxDistanceFromCatMaintained: " << maxDistanceFromCatMaintained << "\n\n";
    
    
    //////////////////////////////////////
    // // Follow up 2:
	// // What if we want to find the shortest path for this maximum distance?
    //////////////////////////////////////

    // int ans = getMinDistanceMaxFromCat(a, src, dest);
    // cout << "minSteps: " << ans << "\n";
    
    // getPath(a, src, dest);
    
	return 0;
}



// // emaar
// 1.92 - 2bhk 							14500
// 3 - 1.5 cr (ready to move)			
// 37d ready to move in 				