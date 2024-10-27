// qlist-16-LIS-with-diff-increasing


// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 16
////////////////////////////////////////////////////////////////////////////////////////////////////


/*

Find the length of longest increasing subsequence such that the difference between consecutive elements in 
LIS is an increasing sequence
Example :
nums -> 1 2 3 4 5 6 ans -> 3
Explanation : the best LIS can be gotten if we take 1 , 2 , 4 ( in this way )

google

*/


#include <bits/stdc++.h>
using namespace std;

int getLISwithDiffIncreasing(vector<int>& a) {

	int n = a.size();
	if (n == 0)
		return 0;

	vector<int> dp(n, 1);

	vector<int> lastDiff(n, 0);

	int longestLIS = 1;

	for (int i = 1 ; i < n ; i++) {

		for (int j = 0 ; j < i ; j++) {

			if (a[i] > a[j]) {

				int diff = a[i] - a[j];

				if (dp[j] == 1 || diff > lastDiff[j]) {

					if (dp[j] + 1 > dp[i]) {
						dp[i] = dp[j] + 1;
						lastDiff[i] = diff;
					}
				}
			}
		}

		longestLIS = max(longestLIS, dp[i]);
	}

	return longestLIS;
}

int main() {

    // // tc1
	// vector<int> a = { 1, 2, 3, 4, 5, 6 };
    
    
    // // tc2
    // vector<int> a = { 5, 1, 6, 2, 7, 3 };

    // tc2
    vector<int> a = { 5, 1, 6, 2, 3, 3 };

	int ans = getLISwithDiffIncreasing(a);
	cout << "ans: " <<  ans << "\n";

	return 0;
}