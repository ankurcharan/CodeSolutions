// 416. Partition Equal Subset Sum
// https://leetcode.com/problems/partition-equal-subset-sum/description/

class Solution {

	bool isSubsetSum(vector<int>& a, int n, int sum, vector<vector<int>> dp) {

		// sum is done
		if (sum == 0) {
			return true;
		}

		// no numbers left but sum left
		if (n == 0 && sum != 0)
			return false;
	
		if (dp[n][sum] != -1)
			return dp[n][sum];

		// not including number
		dp[n][sum] = isSubsetSum(a, n - 1, sum, dp);

		// number smaller then only include
		if (a[n - 1] <= sum)
			dp[n][sum] = dp[n][sum] || isSubsetSum(a, n - 1, sum - a[n - 1], dp);
	
		return dp[n][sum];
	}

	bool memoization(vector<int>& nums) {

		int arraySum = accumulate(nums.begin(), nums.end(), 0);

  		if (arraySum & 1)
  			return false;	// no possible to divide odd sum into two

  		int n = nums.size();
  		vector<vector<int>> dp(n + 1, vector<int>(arraySum + 1, -1));

  		return isSubsetSum(nums, n, arraySum / 2, dp);  
	}

	bool dynamicProgramming(vector<int> &a) {

		int n = a.size();
		int arraySum = accumulate(a.begin(), a.end(), 0);

		if (arraySum & 1)
			return false;		// odd cannot be divided

		vector<vector<bool>> dp(arraySum / 2 + 1, vector<bool>(n + 1, false));

		for (int i = 0 ; i <= n ; i++) {
			dp[0][i] = true;		// zero sum is possible
		}

		for (int i = 1 ; i <= arraySum / 2 ; i++) {

			for (int j = 1 ; j <= n ; j++) {

				// not include
				dp[i][j] = dp[i][j - 1];
				if (a[j - 1] <= i) {
					dp[i][j] = dp[i][j] || dp[i - a[j - 1]][j - 1];
				}
			}
		}

		return dp[arraySum / 2][n];
	}

public:
    bool canPartition(vector<int>& nums) {
  		
  		// return memoization(nums);    	// Memory Limit Execced
    
    	return dynamicProgramming(nums);
    }
};