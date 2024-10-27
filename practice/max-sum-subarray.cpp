// https://leetcode.com/discuss/interview-question/4929501/Google-onsite-Interview

/*

Given an array of integers, find a subarray with maximum sum?


Solved using Kadane's Algorithm


Follow up:
Given an array of integers nums, find indexes [i, j] 
such that the subarray sum nums[i] + nums[i+1] ... nums[j-1] + nums[j] is maximum and nums[i] is equal to nums[j]


Example:


nums = [1, 3, 5, 6, 3, -6, 3]


Answer: [1, 4]

*/

#include<bits/stdc++.h>
using namespace std;

int maxSumSubarray(vector<int>& a) {

	int n = a.size();

    int sum = a[0];
    int maxSum = a[0];

    int start = 0;
    int globalStart = start;
    int globalEnd = -1;
    // int maxLen = len;
    
	for (int i = 1 ; i < n ; i++) {

        // new subarray start
        if (sum + a[i] < a[i]) {
            
            sum = a[i];
            start = i;
        }
        else {
            sum += a[i];
        }
        
        if (maxSum < sum) {
            maxSum = sum;
            globalStart = start;
            globalEnd = i;
        }
	}
    
    cout << " => ";
    for (int i = globalStart ; i <= globalEnd ; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";

	// cout << "maxLen: " << maxLen << ", maxSum: " << maxSum << "\n";

	return maxSum;
}

vector<int> getMaxSubarrayIndexes(vector<int> &a) {

	// number, (index, sum);
	unordered_map<int, vector<pair<int, int>>> m;

	int n = a.size();
	int sum = 0;

	int maxSum = INT_MIN;
	int startIndex = -1;
	int endIndex = -1;

	for (int i = 0 ; i < n ; i++) {

		sum += a[i];

		if (m.find(a[i]) != m.end()) {

			for (pair<int, int> f: m[a[i]]) {
                
                cout << i << " -- " << a[i] << " = " << f.first << " , " << f.second << "\n";
                
				int currSubarraySum = sum - f.second + a[f.first];

				if (currSubarraySum > maxSum) {

					maxSum = currSubarraySum;
					startIndex = f.first;
					endIndex = i;
				}
			}
		}

		m[a[i]].push_back({ i, sum });
	}

	return { startIndex, endIndex, maxSum };
}


int main() {

	// vector<int> a = { 1, 2, 3, -7, 8 };
	// int mssa = maxSumSubarray(a);

	// cout << "a: " << mssa << "\n";
    
    // vector<int> b = { -1, -2, -3, -6, -8 };
	// int mssb = maxSumSubarray(b);

	// cout << "b: " << mssb << "\n";








	// follow up 
	// find subarray with first and last same element
	// and max sum

	vector<int> v = { 1, 3, 5, 6, 3, -6, 3 };
    // print index
    for (int i = 0 ; i < v.size() ; i++) {
        cout << setw(2) << i << " ";
    }
    cout << "\n";
    // print value
    for (int x: v) {
        cout << setw(2) << x << " ";
    }
    cout << "\n";
    // print prefix sum
    int sum = 0;
    for (int x: v) {
        sum += x;
        cout << setw(2) << sum << " ";
    }
    
    cout << "\n\n";
    
	vector<int> ans = getMaxSubarrayIndexes(v);

	cout << ans[0] << ", " << ans[1] << " = " << ans[2] << "\n";
    
    return 0;

}