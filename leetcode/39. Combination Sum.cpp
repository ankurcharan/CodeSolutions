// 39. Combination Sum
// https://leetcode.com/problems/combination-sum/description/

class Solution {
public:
	void backtrackPossibles(vector<int> &candidates, const int& target, int i, vector<int> &curr, int sum, vector<vector<int>>& ans) {

		if (sum > target)
			return;

		if (sum == target) {
			ans.push_back(curr);
			return;
		}

		int n = candidates.size();
		for (int x = i ; x < n ; x++) {
			curr.push_back(candidates[x]);
			backtrackPossibles(candidates, target, x, curr, sum + candidates[x], ans);
			curr.pop_back();
		}
	}

	vector<vector<int>> backtracking(vector<int>& candidates, int target) {

		vector<vector<int>> ans;
		vector<int> curr;

		backtrackPossibles(candidates, target, 0, curr, 0, ans);

		return ans;
	}

    vector<vector<int>> iterativeDP(vector<int>& candidates, int target) {
	
    	vector<vector<vector<int>>> dp(target + 1);

    	dp[0].push_back({});		// you can make 0 with no elements

    	for (int i = 1 ; i <= target ; i++) {

    		for (int candidate: candidates) {

    			if (candidate <= i) {

    				for (auto& prev: dp[i - candidate]) {	// get ans without curr element

    					vector<int> temp(prev);

    					temp.push_back(candidate);
    					sort(temp.begin(), temp.end());
    					
    					if (find(dp[i].begin(), dp[i].end(), temp) == dp[i].end()) {
    						dp[i].push_back(temp);
    					}
    				}
    			}
    		}
    	}

    	return dp[target];
	}

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        // return backtracking(candidates, target);

        return iterativeDP(candidates, target);
    }
};
