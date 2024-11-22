// build-max-num-with-cost
// https://leetcode.com/discuss/interview-question/4878435/Google-Telephonic-PhoneScreen-Interview-question



/*

Hi ,


I gave my first Technical Phone Screening round on 6th March 2024,
Can't reveal the exact questions,


Question is about a frog which can go left or right with with maximum possible step be l for left and r for right, i.e. frog can move right 0 or 1, or 2 or ... r times, given start and destination, find minimum steps to reach.
Something related to making maximum number using digits(1 to 9) where using a digit has some associated cost(can be different for dif digits), and we have fixed money we can use.
But I don't know why my recruiter is taking too long to respond. Not even replying ? Is it normal, it's my first time giving Interview out of college,
Exp: 8 Months in SWE


UPD: Just got the mail for next round of interviews. (alwasys use google-candidate-feedback in case of delay from any side, thank me later)

*/


//////////////////////////////////////
//////////////////////////////////////
///// QUESTION 2 //////////
//////////////////////////////////////
//////////////////////////////////////


#include<bits/stdc++.h>
using namespace std;

int getMaxNumberRecursive(vector<int>& digits, vector<int>& cost, int budget, unordered_map<int, int>& dp) {

    // cout << "call budget: " << budget << "\n";
    
	if (budget <= 0) {
		return 0;
	}
    
    if (dp.find(budget) != dp.end()) {
        return dp[budget];
    }

	int result = 0;

	for (int i = 9 ; i >= 0 ; i--) {

		// can use that digit
		if (budget >= cost[i]) {

            // cout << "match cost: " << cost[i] << ", digit: " << digits[i] << "\n";
            
			int future = getMaxNumberRecursive(digits, cost, budget - cost[i], dp);
			cout << future << " " << digits[i] << " " << cost[i] << endl;
            
			// cout << "budget: " << budget << ", future: " <<  future << "\n";
			result = max(result, future * 10 + digits[i]);
		}
	}

	return dp[budget] = result;
}

int getMaxNumberIterative(vector<int>& digits, vector<int>& cost, int budget) {

	int n = cost.size();

	vector<vector<int>> dp (n + 1, vector<int> (budget + 1, 0));

	for (int i = 1 ; i <= n ; i++) {

		for (int j = 1 ; j <= budget ; j++) {

			// cost for current digit
			int currCost = cost[i - 1];

			// digits considered from 1 to 9
			dp[i][j] = dp[i - 1][j];

			if (j >= currCost) {

                
                cout << "m: j: " <<  j << ", cost: " << currCost << "\n";
                
                cout << "ij: " << dp[i][j] << ", i-1j: " << dp[i - 1][j] << "\n";
                
				dp[i][j] = max(dp[i][j], dp[i - 1][j] * 10 + digits[i - 1]);				
			}
		}
	}

	return dp[n][budget];
}

int main() {

	vector<int> digits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> cost   = { 11, 40, 40, 40, 40, 40, 40, 40, 4, 6 };

	int budget = 10;
    
    unordered_map<int, int> dp;

    // this is running
	int ansRecursive = getMaxNumberRecursive(digits, cost, budget, dp);
	cout << "ansRecursive: " << ansRecursive << "\n";

	cout << "\n\n";

	// this isn't 
    int ansIterative = getMaxNumberIterative(digits, cost, budget);
    cout << "ansIterative: " << ansIterative << "\n";

	return 0;
}