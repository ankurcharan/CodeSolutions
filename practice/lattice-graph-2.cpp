#include<bits/stdc++.h>
using namespace std;


void printIntVector(vector<vector<int>> a)
{
	int n = a.size();
	int m = a[0].size();

	for (int i = 0 ; i < n ; i++)
	{
		for (int j = 0 ; j < m ; j++)
			cout << setw(3) << a[i][j] << " ";
		cout << endl;
	}
}

void printIntVector(vector<int> a)
{
	int n = a.size();

	for (int i = 0 ; i < n ; i++)
	{
		cout << setw(3) << a[i] << " ";
	}
	cout << endl;
}




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

vector<int> getAns(vector<vector<int>> a) {

	const vector<pair<int, int>> moves = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
	vector<int> colors(8, -1);
    
    int numCombinations = 0;
    int casesTested = 0;
    
    for (int i = 0 ; i < pow(4, 8) ; i++)
    {
        int t = i;
        for (int j = 0 ; j < 8 ; j++)
        {
            colors[j] = t % 4;
            t = t / 4;
        }
        
        if (possible(a, colors, moves))
        {
            return colors;
        }
    }
    
	return { };
}



int main() {

	int n, m;
	cin >> n >> m;

	vector<vector<int>> a;

	for (int i = 0 ; i < n ; i++) {

		vector<int> t;
		int z;
		for (int j = 0 ; j < m ; j++) {

			cin >> z;
			t.push_back(z);
		}
		a.push_back(t);
		t.clear();
	}
	
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