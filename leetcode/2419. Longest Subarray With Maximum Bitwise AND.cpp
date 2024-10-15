// 2419. Longest Subarray With Maximum Bitwise AND
// https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/description

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        
        int n = nums.size();
        if (n == 0)	return -1;

        int maxValue = nums[0];
        int currentStreak = 0;
        int ans = 0;;

        for (int i = 0 ; i < n ; i++) {

        	if (nums[i] > maxValue) {

        		maxValue = nums[i];
        		ans = currentStreak = 0;
        	}

        	if (nums[i] == maxValue) 
        		currentStreak++;
        	else
        		currentStreak = 0;

        	ans = max(ans, currentStreak);
        }

        return ans;
    }
};