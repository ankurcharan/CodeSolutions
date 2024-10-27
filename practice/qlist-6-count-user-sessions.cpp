// qlist-6-count-user-sessions


// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 6
////////////////////////////////////////////////////////////////////////////////////////////////////


/*

You are given a list of user sessions where each user session has start and end times both inclusive. 
Now, given a value N, find the count of all users at each point in time from [0,N) 

i.e include 0 but exclude N. Example:
Input:
[(0,3), (1,4) ] N=7
Output:
0->1
1->2
2->2
3->2
4->1

*/

#include <bits/stdc++.h>
using namespace std;

vector<int> getCountOfUserSessions(vector<pair<int, int>>& intervals, int n) {

	int minV = INT_MAX;
	int maxV = INT_MIN;

	int s = intervals.size();
	// for (int i = 0 ; i < s ; i++) {

	// 	minV = min(minV, intervals[i].first);
	// 	maxV = max(minV, intervals[i].second);
	// }

	vector<int> ans(n, 0);
	for (int i = 0 ; i < s ; i++) {

		if (intervals[i].first < n) {
			ans[intervals[i].first]++;
		}

		if (intervals[i].second + 1 < n) {
			ans[intervals[i].second + 1]--;
		}
	}

	vector<int> countSessions;

	int count = 0;
	for (int i = 0 ; i < n ; i++) {

		count += ans[i];

		countSessions.push_back(count);
	}

	return countSessions;
}

int main() {

	vector<pair<int, int>> intervals = {
		{ 0, 3 },
		{ 1, 4 },
		{ 1, 10 }
	};

	int n = 7;

	vector<int> ans = getCountOfUserSessions(intervals, n);
	int s = ans.size();
	
	for (int i = 0 ; i < s ; i++) {
		cout << setw(3) << i << " ";
	}
	cout << endl;

	for (int x: ans) {
		cout << setw(3) << x << " ";
	}
	cout << "\n";

	return 0;
}