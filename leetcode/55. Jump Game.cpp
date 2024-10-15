// 55. Jump Game
// https://leetcode.com/problems/jump-game/description/

class Solution {

	int jumpMemo(vector<int>& a, int l, int n, vector<int>& dp) {

		if (l == n)
			return 0;		// reached

		if (a[l] == 0)		// no moves possible
			return INT_MAX;

		int minJumps = INT_MAX;

		for (int j = a[l] ; j >= 1 ; j--) {

			// out of bound check
			if (l + j <= n) {
                // number of jumps from (l+j) to n
                int moves = jumpMemo(a, l + j, n, dp);
                if (moves != INT_MAX)
                    minJumps = min(minJumps, 1 + moves);
			}
		}

		return dp[l] = minJumps;
	}


	bool memoization(vector<int>& a) {

		// number of jumps
		vector<int> dp(a.size(), -1);
	
		return jumpMemo(a, 0, a.size() - 1, dp) != INT_MAX;
	}

	bool bottomUp(vector<int>& a) {

		int n = a.size();

        // if (n == 1 && a[0] == 0)
        //     return true;

		vector<int> jumps(n, INT_MAX);

		// if (n == 0 || a[0] == 0)
		// 	return false;	// not possible moves

		jumps[0] = 0;
		for (int i = 1 ; i < n ; i++) {

			for (int j = 0 ; j < i ; j++) {

				if (i <= j + a[j] && jumps[j] != INT_MAX)
					jumps[i] = min(jumps[i], 1 + jumps[j]);
			}
		}

        // // print jumps
        // for (int i = 0 ; i < n ; i++) {
        //     cout << setw(3) << jumps[i] << " ";
        // }
        // cout << "\n";

		return jumps[n - 1] != INT_MAX;
	}

public:
    bool canJump(vector<int>& nums) {
  		
  		// return memoization(nums);    	// TLE

  		return bottomUp(nums);  
    }
};