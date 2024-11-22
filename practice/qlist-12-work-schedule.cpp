// qlist-12-work-schedule


// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 12
////////////////////////////////////////////////////////////////////////////////////////////////////

/*

You work as a consultant and have clients in cityA and cityB. On a given day,
say i, you can either
work in cityA and make Ai dollars or you can work in cityB and make Bi dollars. You can also spend
the day traveling between cityA and cityB in which case your earnings that day are 0.
Given Al,A2, ....An and B1, B2,....., Bn, return a schedule S of N days which maximizes your earnings,
where S is a string of length N, and Si = A/B/T where A means work in cityA, B means work in cityB
T means travel on day i. You can start either in cityA or cityB. 
Example1: 
	A = [23, 4,5 ,101] B = [21,1,10, 100] The optimal schedule S here would be ->"ATBB"
Example 2:
	A[25,10,15,10,70] B = [5,5,50,5,30] The optimal schedule S here would be-> "ATBTA"

*/

#include<bits/stdc++.h>
using namespace std;

vector<char> getSchedule(vector<int>& a, vector<int>& b) {

	int n = a.size();

	vector<char> ans;

	vector<int> dpA(n + 1);		// // ending at city A
	vector<int> dpB(n + 1);		// // ending at city B
	dpA[0] = 0;
	dpB[0] = 0;
	dpA[1] = a[0];
	dpB[1] = b[0];
	dpA[2] = max(dpB[1], dpA[1] + a[1]);
	dpB[2] = max(dpA[1], dpB[1] + b[1]);

	for (int i = 2 ; i <= n ; i++) {

		dpA[i] = max(dpA[i - 1], dpB[i - 2]) + a[i - 1];
		dpB[i] = max(dpB[i - 1], dpA[i - 2]) + b[i - 1];
	}

	int maxProfit = max(dpA[n], dpB[n]);

	cout << "maxProfit: " << maxProfit << "\n";

	return ans;

}


void recurseMax(vector<int>& a, vector<int>& b, int currIdx, int n, string path, int sum, int& maxSum) {

	if (currIdx == n) {
        
        if (sum >= maxSum) {
            
            cout << "sum: " << setw(4) << sum << ", path: " << path << "\n";
            maxSum = sum;
        }
        
		return;
	}

	if (path.back() == 'A') {
        
		recurseMax(a, b, currIdx + 1, n, path + "A", sum + a[currIdx], maxSum);
		if (currIdx + 2 <= n) 
            recurseMax(a, b, currIdx + 2, n, path + "TB", sum + b[currIdx + 1], maxSum);
	
    } else {
	
        recurseMax(a, b, currIdx + 1, n, path + "B", sum + b[currIdx], maxSum);
		if (currIdx + 2 <= n) 
            recurseMax(a, b, currIdx + 2, n, path + "TA", sum + a[currIdx + 1], maxSum);
	}
}

vector<char> getScheduleRecursive(vector<int>& a, vector<int>& b) {

	int n = a.size();

    int maxSum = 0;
    
	recurseMax(a, b, 1, n, "A", a[0], maxSum);
	recurseMax(a, b, 1, n, "B", b[0], maxSum);

	vector<char> ans;
	return ans;
}

int main() {

    // // ATBB
	// vector<int> a = { 23, 4, 5, 101 };
	// vector<int> b = { 21, 1, 10, 100 };

	// vector<char> s = getSchedule(a, b); 
	// cout << "schedule: ";
	// for (char x: s)
	// 	cout << x << " ";
	// cout << "\n";






    // // ATBTA
	vector<int> a = { 25 , 10 , 15 , 10 , 70 };
	vector<int> b = { 5 ,  5 ,  50 , 5 , 30 };

	vector<char> s = getSchedule(a, b); 
	cout << "schedule: ";
	for (char x: s)
		cout << x << " ";
	cout << "\n";


	vector<char> schedule = getScheduleRecursive(a, b);

	return 0;
}