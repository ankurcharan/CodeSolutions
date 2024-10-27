// min-max-dist-from-cat

/*

You can give a matrix marked with 'S' as source, and 'D' as destination. 
You can move in four direction. 

There are cats in matrix marked with 'X'
you have to find the min distance from S to D which should be at max distance from cat. 



marking 'S' as -2
marking 'D' as -3

marking 'X' as -1

everything else is zero

*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> moves = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

void getDistanceFromCats(vector<vector<int>>& a) {

	int n = a.size();
	if (n == 0)	return;
	int m = a[0].size();
	if (m == 0)	return;

	// (x, y), distance
	queue<pair<pair<int, int>, int>> q;
	vector<vector<bool>> visit(n, vector<bool>(m, false));

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {
			if (a[i][j] == -1) {
                visit[i][j] = true;
				q.push({ { i, j }, 0 });
			}
		}
	}


	while (!q.empty()) {

		pair<pair<int, int>, int> f = q.front();
		q.pop();

		a[f.first.first][f.first.second] = f.second;

		for (int i = 0 ; i < 4 ; i++) {

			int x = f.first.first + moves[i][0];
			int y = f.first.second + moves[i][1];

			if (x >= 0 && x < n && y >= 0 && y < m && visit[x][y] == false) {
				q.push({ { x, y }, f.second + 1 });
                visit[x][y] = true;
			}
		}
	}
}

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
        else {
            cout << "new value: ";
        }
        
        cout << "pop: " << currSteps << ", " << dist << ", " << currX << ", " << currY << "  \n";
        
        step[currX][currY] = currSteps;
        distance[currX][currY] = dist;
        
        if (f.second.first == dest[0] && f.second.second == dest[1]) {
            
            cout << "\n\ntotaldist: " << f.first.second << endl << endl;
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
            
            if (x == 0 && y == 5)
                d = true;
            else
                d = false;
            
            
            if (x >= 0 && x < n && y >= 0 && y < m && a[x][y] != 0) {
                
                if (d)
                    cout << "axy: " << a[x][y] << ", " << f.first.second + a[x][y] << "\n";
                pq.push({ { f.first.first + 1, f.first.second + a[x][y] }, { x, y } });
            }
        }
    }
    
    
    cout << "\n\nsteps\n";
    print(step);
    
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

	vector<vector<int>> srcAndDest = getSourceAndDest(a);

	// print(a);

	vector<int> src  = srcAndDest[0];
	vector<int> dest = srcAndDest[1];
    
    cout << "src : " << src[0] << ", " << src[1] << "\n";
    cout << "dest: " << dest[0] << ", " << dest[1] << "\n\n";

	getDistanceFromCats(a);
	print(a);

    int ans = getMinDistanceMaxFromCat(a, src, dest);
    cout << "minSteps: " << ans << "\n";
    
	return 0;
}