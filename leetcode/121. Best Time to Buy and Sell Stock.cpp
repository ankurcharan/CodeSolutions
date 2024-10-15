// 121. Best Time to Buy and Sell Stock
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/


class Solution {
public:
	int maxProfit(vector<int>& prices) {

		int n = prices.size();
		
		int ans = 0;
		int maxPrice = prices[n - 1];
		for (int i = n - 2; i >= 0 ; i--) {
			
			if (maxPrice > prices[i]) {
				ans = max(ans, maxPrice - prices[i]);
			}
			maxPrice = max(maxPrice, prices[i]);
		}

		return ans;
	}
};
