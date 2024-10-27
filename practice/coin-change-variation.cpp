// https://leetcode.com/discuss/interview-question/4422524/Google-Onsite-interview/2174916

/*

Variation of coin change.
we are given dp array that we created while finding number of ways to make the target sum. We need to find the coins array, using which this dp array is created.
Example:

target = 10
number of ways to make 10: 3
Input: [1, 0, 1, 0, 1, 1, 2, 1, 2, 1, 3]
Output: [2, 5, 6]

*/


#include<bits/stdc++.h>
using namespace std;

int findNumberOfWays(vector<int>& coins, int sum, vector<int>& dp) {

	int n = coins.size();

	dp[0] = 1;	// 1 way to make zero sum

	// for all sum
	for (int c = 0 ; c < n ; c++) {
		
		// traverse for all coins
		for (int s = coins[c] ; s <= sum ; s++) {

				// add coin to the sum sum
				dp[s] += dp[s - coins[c]];
		}
	}

	return dp[sum];
}

void print(vector<int>& dp) {
    
    int n = dp.size();
    for (int i = 0 ; i < n ; i++)
        cout << dp[i] << " ";
    cout << "\n";
}

vector<int> constructOriginalArray(vector<int> &dp) {
    
    int sum = dp.size() - 1;        // sum value
    int n = dp.size();      // size of dp array = sum + 1
    
    vector<int> originalArr;
    
    for(int s = 1 ; s < n ; s++) {
        if (dp[s] == 1) {
            
            cout << s << " -- ";
            
            for(int j = n - 1 ; j >= s ; j--) {
                dp[j] -= dp[j - s];
            }
            
            print(dp);
            
            originalArr.push_back(s);
        }
    }
    
    return originalArr;
}

int main() {

	vector<int> coins = { 1, 2, 3, 4, 5 };
	int sum = 24;

	// no of way array
	vector<int> dp(sum + 1, 0);

	int numberOfWays = findNumberOfWays(coins, sum, dp);

	cout << "numberOfWays: " << numberOfWays << "\n";
	for (int i = 0 ; i <= sum ; i++)
		cout << dp[i] << " ";
	cout << "\n";
    
    
    vector<int> originalArr = constructOriginalArray(dp);
    
    cout << "coins\n";
	for (int i = 0 ; i < originalArr.size() ; i++)
		cout << originalArr[i] << " ";
	cout << "\n";

	return 0;
}