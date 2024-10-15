// 322. Coin Change
// https://leetcode.com/problems/coin-change/description/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        
        int n = coins.size();

        // no of way to build amount
        vector<int> dp(amount + 1, INT_MAX);
    	
    	// sum == 0, 0 coins to build that value
    	dp[0] = 0;

    	for (int i = 1 ; i <= amount ; i++) {

    		for (int j = 0 ; j < n ; j++) {
    			if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
    				dp[i] = min(dp[i], dp[i - coins[j]] + 1);
    			}
    		}
    	}

        // for (int i = 0 ; i <= amount ; i++)
        //     cout << setw(3) << i << " ";
        // cout << "\n";
        // for (int i = 0 ; i <= amount ; i++)
        //     cout << setw(3) << dp[i] << " ";
        // cout << "\n";

    	if (dp[amount] == INT_MAX)
    		return -1;
    	return dp[amount];
    }
};