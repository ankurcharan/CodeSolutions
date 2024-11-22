// relative-sort
// https://leetcode.com/discuss/interview-question/397156/

/**
 *

Google Singapore OA
Summer 2020 Internship
Interview on CoCubes


Previous Question: Greatest Common Divisor


Question #2: https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/


Relative sorting is defined as sorting two arrays (both in strictly ascending order) 
such that the only operation allowed is swapping i'th element of one array with the i'th elementh of the other array

An array is said to be in strictly ascending order if i'th element of the array is smaller than (i+1)'th element of the array.
You are given two arrays of size N. print the minimum number of swaps required to make both arrays relatively sorted.


Note:
If the arrays are already relatively sorted, then print '0'
If the arrays cannot be relatively sorted, then print '-1'.
Input Format:
The input consist of 3 lines:


First line consist of the size of each array, i.e. N
The next two lines contain N elements each seperated by a space
Output Format:
The output will be an integer i.e., the minimum number of swaps required to make both arrays relatively sorted.


Constraints:
0 < N < 11000
0 < Elements in array <= 10^9
Example 1:


Input:
4
1 4 4 9
2 3 5 10

Output: 1
Explanation: To make both arrays strictly increasing we can swap 4 and 3 or 4 and 5.


 * 
 * 
 * 
 */


#include <bits/stdc++.h>
using namespace std;

bool isIncreasing(vector<int>& v){

	for (int i = 1; i < v.size(); i++) {
		if (v[i] <= v[i - 1]) return false;
	}

	return true;
}

int ans = 0;
void print(vector<int>& a) {

	for (int i = 0 ; i < a.size() ; i++) {
		cout << setw(2) << a[i] << " ";
	}
	cout << " ---- " << boolalpha << isIncreasing(a);
	cout << "\n";
}

int recursive(vector<int>& a, vector<int>& b, int pos, int n, vector<int>& dp) {

	if (pos == a.size()) {

		print(a);
		print(b);
		cout << endl;

		ans++;

		return isIncreasing(a) && isIncreasing(b) ? 0 : -1;
	}

	if (dp[pos] != -1)
		return dp[pos];

	int notSwapped = recursive(a, b, pos + 1, n, dp);
	
	swap(a[pos], b[pos]);
	int swapped = recursive(a, b, pos + 1, n, dp);
	swap(a[pos], b[pos]);
	
	int ans = -1;

	if (swapped == -1 && notSwapped == -1) 
		ans = -1;
	else if (swapped == -1) 
		ans = notSwapped;
	else if (notSwapped == -1) 
		ans = swapped + 1;
	else 
		ans = min(swapped + 1, notSwapped);

	return dp[pos] = ans;
}

int dynamicProgramming(vector<int> a, vector<int> b, int n) {

	vector<vector<int>> dp(n, vector<int>(2, INT_MAX));

	// 0 - for swap
	// 1 - for not swap

	dp[0][0] = 1;		// only one swap
	dp[0][1] = 0;		// no swap

	for (int i = 1 ; i < n ; i++) {

		cout << a[i - 1] << " " << a[i] << " " << b[i - 1] << " " << b[i] << " " << endl;

		// continuing the same series
		if (a[i] > a[i - 1] && b[i] > b[i - 1]) {

			// last time swapped, this time swap again
			dp[i][0] = min(dp[i][0], 1 + dp[i - 1][0]);

			// last time no swap, this time no swap
			dp[i][1] = min(dp[i][0], dp[i - 1][1]);
		}


		// if you can swap the numbers between two series
		if (a[i] > b[i - 1] && b[i] > a[i - 1]) {

			// last time not swapped, this time swap
			dp[i][0] = min(dp[i][0], 1 + dp[i - 1][1]);
		
			// last time swapped, this time not swap
			dp[i][1] = min(dp[i][1], dp[i - 1][0]);
		}

		if (min(dp[i][0], dp[i][1]) == INT_MAX)
			return -1;			// not possible to arrange
	}

	cout << "dp: ";
	for (int i = 0 ; i < n ; i++) {
		cout << "[" << dp[i][0] << ", " << dp[i][1] << "] ";
	}
	cout << "\n";

	return min(dp[n - 1][0], dp[n - 1][1]);
}


int getMinSwaps(vector<int> a, vector<int> b, int n) {

	ans = 0;

	// vector<int> dp(n, -1);
	// return recursive(a, b, 0, n, dp);

	return dynamicProgramming(a, b, n);
}

int main() {
	
	// int n = 4;
	// vector<int> a = { 9, 4, 6, 9 };
	// vector<int> b = { 0, 10, 11, 12 };

	// vector<int> a = { 1, 4, 4, 9 };
	// vector<int> b = { 2, 3, 5, 10 };

	// vector<int> a = { 1, 4, 4, 9 };
	// vector<int> b = { 2, 3, 1, 10 };

	int n = 5;
	// vector<int> a = { 1, 3, 6, 5 };
	// vector<int> b = { 2, 5, 4, 7 };

	vector<int> a = { 0, 4, 4, 5, 9 };
	vector<int> b = { 0, 1, 6, 8, 10 };

	int minSwaps = getMinSwaps(a, b, n);
	cout << "minSwaps: " << minSwaps << "\n";

	return 0;
}




















/**


import math
# https://leetcode.com/discuss/interview-question/397156/google-oa-summer-intern-2020-relative-sort

def relativeSort1(n, A, B):
    # swap, not swap
    dp = [1, 0]
    for a0, a1, b0, b1 in zip(A, A[1:], B, B[1:]):
        
        dp_new = [math.inf, math.inf]
        
        if a1 > a0 and b1 > b0:
            # last time swapped, this time swap again
            dp_new[0] = min(dp_new[0], 1 + dp[0])
            # last time not swapped, this time not swap again
            dp_new[1] = min(dp_new[1], dp[1])
        
        
        if a1 > b0 and b1 > a0:
            # last time not swapped, this time swap
            dp_new[0] = min(dp_new[0], 1 + dp[1])
            # last time swapped, this time not swap
            dp_new[1] = min(dp_new[1], dp[0])
        
        
        dp = dp_new
        
        print(dp)
        
        if min(dp) == math.inf: 
            return -1
        
        
    return min(dp)

def relativeSort(n, A, B):
    # swap, not swap
    dp = [[1, 0]] + [[math.inf, math.inf] for _ in range(n - 1)]
    
    print('dp: ', dp)
    
    for i, (a0, a1, b0, b1) in enumerate(zip(A, A[1:], B, B[1:]), 1):
        
        print (i, ' -- ', a0, a1, b0, b1, end = ' ')
        
        if a1 > a0 and b1 > b0:
        
            print("first ", end = '')
            
            # last time swapped, this time swap again
            dp[i][0] = min(dp[i][0], 1 + dp[i - 1][0])
            # last time not swapped, this time not swap again
            dp[i][1] = min(dp[i][1], dp[i - 1][1])
        
        
        if a1 > b0 and b1 > a0:
            
            print("second ", end = '')
            
            # last time not swapped, this time swap
            dp[i][0] = min(dp[i][0], 1 + dp[i - 1][1])
            # last time swapped, this time not swap
            dp[i][1] = min(dp[i][1], dp[i - 1][0])
            
            
        if min(dp[i]) == math.inf: 
            return -1
        
        print()
        
    print(dp)
        
    return min(dp[-1])


# n = 4
# A = [1, 4, 4, 9]
# B = [2, 3, 5, 10]
# print(relativeSort(n, A[:], B[:]))
# print('\n\nnext\n\n') 
# print(relativeSort1(n, A[:], B[:]))

# n = 4
# A = [1, 4, 4, 9]
# B = [2, 3, 1, 10]
# print(relativeSort(n, A[:], B[:]))
# print(relativeSort1(n, A[:], B[:]))

# n = 4
# A = [1, 3, 6, 5]
# B = [2, 5, 4, 7]
# print(relativeSort(n, A[:], B[:]))
# print(relativeSort1(n, A[:], B[:]))

n =5
A = [0,4,4,5,9] 
B = [0,1,6,8,10]
print(relativeSort(n, A[:], B[:]))
print(relativeSort1(n, A[:], B[:]))





*/