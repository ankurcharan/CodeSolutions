// 191. Number of 1 Bits
// https://leetcode.com/problems/number-of-1-bits/description/

class Solution {
public:
    int hammingWeight(int n) {
  	
  		int ans = 0;
  		while (n) {

  			ans++;
  			n = n & (n - 1);
  		}      

  		return ans;
    }
};