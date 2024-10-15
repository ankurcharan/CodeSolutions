// 300. Longest Increasing Subsequence
// https://leetcode.com/problems/longest-increasing-subsequence/description/

class Solution {

	int dynamicProgramming(vector<int>& a) {

		int n = a.size();
		vector<int> dp(n, 1);

		for (int i = 1 ; i < n ; i++) {
			for (int j = 0 ; j < i ; j++) {

				if (a[j] < a[i])
					dp[i] = max(dp[i], dp[j] + 1);
			}
		}

		vector<int>::iterator it = max_element(dp.begin(), dp.end());
		return *it;
	}

public:
    int lengthOfLIS(vector<int>& nums) {
  
  		return dynamicProgramming(nums);      
    }
};