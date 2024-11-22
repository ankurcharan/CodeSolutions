// qlist-6-count-of-users
// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 6
////////////////////////////////////////////////////////////////////////////////////////////////////


// You are given a list of user sessions where each user session has start and end times both inclusive. 
// Now, given a value N, find the count of all users at each point in time from [0,N) 
// i.e include 0 but exclude N. Example:
// Input:
// [(0,3), (1,4) ] N=7
// Output:
// 0->1
// 1->2
// 2->2
// 3->2
// 4->1


#include<bits/stdc++.h>
using namespace std;

bool cmp (pair<int, int>& a, pair<int, int>& b) {

	if (a.second == b.second) 
		return a.first < b.first;
	return a.second < b.second;
}

void printUsers(vector<pair<int, int>>& v, int n) {

	// sort(v.begin(), v.end(), cmp);

	int users = 0;

	// changes
	unordered_map<int, int> changes;
	for (pair<int, int> f: v) {
		changes[f.first] += 1;
		changes[f.second + 1] -= 1;
	}

	for (int i = 0 ; i < n ; i++) {

		users += changes[i];
		cout << i << " = " << users << "\n";
	}
	cout << endl;
}

int main() {

	vector<pair<int, int>> v = {
		{ 0, 3 },
		{ 2, 6 },
		{ 1, 4 }
	};

	int n = 7;

	printUsers(v, n);

	return 0;
}