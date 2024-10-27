// int-2-buy-sell-stock.cpp
// https://leetcode.com/discuss/interview-question/5898854/L5-Google-or-Interview-Exp.-or-Rejected


/**
 * 
 * 
Mock Interview 3:
Question: Stock prices are given for each day in an array. 
You can make any number of transactions, 
but at any time you can either buy or sell (no two buys or sells consecutively).

Solution: Solved using DP.
Feedback: Strong hire.


*/

#include <bits/stdc++.h>
using namespace std;

int maxProfitWhenOnlyBuySellOnAnyDay(vector<int> prices) {

	int n = prices.size();

	vector<int> profit(n, 0);

	profit[0] = 0;
	profit[1] = (prices[1] - prices[0]) > 0 ? prices[1] - prices[0] : 0; 

	for (int i = 2 ; i < n ; i++) {

		if (prices[i] > prices[i - 1]) {
			profit[i] = (prices[i] - prices[i - 1]) + profit[i - 2];
		}
		else 
			profit[i] = profit[i - 1];
	}

	for (int i = 0 ; i < n ; i++) {
		cout << setw(2) << i << " ";
	}
	cout << "\n";
	for (int i = 0 ; i < n ; i++) {
		cout << setw(2) << prices[i] << " ";
	}
	cout << "\n";
	for (int i = 0 ; i < n ; i++) {
		cout << setw(2) << profit[i] << " ";
	}
	cout << "\n";
	

	return profit[n - 1];
}

int main() {

	// vector<int> prices = { 7, 1, 5, 3, 6, 4 };
	vector<int> prices = { 1, 2, 3, 4, 5, 6 };

	int ans = maxProfitWhenOnlyBuySellOnAnyDay(prices);
	cout << "maxProfitWhenOnlyBuySellOnAnyDay: " << ans << endl;

	return 0;
}